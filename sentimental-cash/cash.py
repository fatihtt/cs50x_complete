# TODO
from cs50 import get_float

amount = -1.00

# take proper change

while amount < 0:
    amount = get_float("Change owed: ")

# print(f"Your change: {amount}")

# calculate minimum amount

# quarters
quarters = int(amount / 0.25)

amount = (amount * 100 - quarters * 25) / 100

# print(quarters, "quarters", "remaining", amount)

# dimes
dimes = int(amount / 0.10)

amount = float(amount * 100 - dimes * 10) / 100

# print(quarters, "quarters", dimes, "dimes", "remaining", amount)

# nickels

nickels = int(amount / 0.05)

amount = (amount * 100 - nickels * 5) / 100

# print(quarters, "quarters", dimes, "dimes", nickels, "nickels", "remaining", amount)

# pennies
pennies = int(amount / 0.01)

# print(quarters, "quarters", dimes, "dimes", nickels, "nickels", pennies, "pennies")

print(quarters + dimes + nickels + pennies)