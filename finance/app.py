import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
os.environ["API_KEY"] = "pk_cf30a8833ae649d6baecde0727afe676"
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM shares WHERE user_id = ?", session["user_id"])
    user = (db.execute("SELECT * FROM users WHERE users.id = ?", session["user_id"]))[0]
    print(user)
    cash = user["cash"]
    username = user["username"]
    stockprices = []
    totals = []
    #for stock in stocks:
    for stock in stocks:
        price = lookup(stock["symbol"].upper())["price"]
        stockprices.append(usd(price))
        totals.append(usd(price*stock["amount"]))
    return render_template("index.html", stocks=stocks, username=username, cash=cash, stockprices=stockprices, totals=totals)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = 0

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be integer")

        if not symbol or not shares or shares < 1:
            return apology("fill the form correctly")

        # check affordability
        wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]

        if not wallet:
            return apology("user could not found")

        price = 0
        try:
            price = lookup(symbol.upper())["price"]
        except:
            return apology("invalid symbol")

        sum = price * shares

        if wallet["cash"] < sum:
            return apology("you can't afford this trade :(")

        # affordability Ok

        now = datetime.now()
        # NEW TRANSACTION INFO TO DB
        db.execute("INSERT INTO transactions (user_id, symbol, amount, price, datetime) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, shares, "{:.2f}".format(price), now)

        # UPDATE USERS CASH INFO
        newcash = wallet["cash"] - sum
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newcash, session["user_id"])

        # UPDATE SHARE TABLE
        symbol_query = db.execute("SELECT * FROM shares WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if len(symbol_query) > 1:
            return apology("db error")
        elif len(symbol_query) == 1:
            cur_amount = symbol_query[0]["amount"]
            new_amount = cur_amount + shares
            db.execute("UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?", new_amount, session["user_id"], symbol)
        else:
            db.execute("INSERT INTO shares (user_id, symbol, amount) VALUES(?, ?, ?)", session["user_id"], symbol, shares)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    tr_history = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", tr_history=tr_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("symbol not found")

        sym_dict = lookup(symbol.upper())

        print(sym_dict)
        if not sym_dict:
            return apology("error during lookup")

        return render_template("quoted.html", sym_dict=sym_dict)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password2 = request.form.get("confirmation")
        if len(username) < 1 or len(password) < 1 or password != password2:
            return apology("fill the form please")

        duplicate = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(duplicate) > 0:
            return apology("username already exist")

        passwordh = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, passwordh)
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if len(request.form.get("symbol")) < 1 or len(request.form.get("shares")) < 1:
            return apology("fill the form correctly")

        shares = 0
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("fill the form correctly i")

        if shares < 1:
            return apology("fill the form correctly")

        # check user has shares enough
        current_share = db.execute("SELECT * FROM shares WHERE user_id = ? AND symbol = ?;", session["user_id"], symbol)

        print((current_share[0]))
        if len(current_share) < 1 or (current_share[0])["amount"] < shares:
            return apology("you have not enough share")

        # take the price of share
        price = lookup(symbol.upper())["price"]
        sum = price * shares

        # add new transaction to db
        now = datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, amount, price, datetime) VALUES (?, ?, ?, ?, ?);", session["user_id"], symbol, (-1 * shares), "{:.2f}".format(price), now)

        # update shares table

        # if all selling, delete row
        if (current_share[0])["amount"] == shares:
            db.execute("DELETE FROM shares WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            remaining = (current_share[0])["amount"] - shares
            db.execute("UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?", remaining, session["user_id"], symbol)

        # update user's cash
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        new_cash = sum + user[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

        return redirect("/")

    else:
        stocks = db.execute("SELECT * FROM shares WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", stocks=stocks)