-- Keep a log of any SQL queries you execute as you solve the mystery.

-- to find the report about theft
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

-- to find license plate of thief
SELECT activity, license_plate, hour, minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10;

-- to find a clue about events
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;

-- to find earliest flight on 29th and where is the destination
SELECT flights.*, airp1.full_name AS origin_airport, airp2.full_name AS dest_airport, airp1.city AS origin_city, airp2.city AS dest_city FROM flights JOIN airports AS airp1 ON airp1.id = origin_airport_id JOIN airports AS airp2 ON airp2.id = destination_airport_id WHERE flights.month = 7 AND flights.day=29;
--earliest flight here is New Your City flight'

-- to find atm transaction and with plate number, detection of thief
SELECT atm_transactions.*, people.name AS person, people.phone_number AS person_phone, people.license_plate AS people_plate FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number=atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE atm_location="Leggett Street" AND atm_transactions.month=7 AND atm_transactions.day=28;

-- to find with whom talked thief less then a minute
SELECT * FROM phone_calls WHERE (month=7 AND day=28) AND (caller="(367) 555-5533" OR receiver="(367) 555-5533");
--less than a minute call to => (375) 555-8161

-- to find whos is the number
SELECT * FROM people WHERE phone_number = "(375) 555-8161";
-- Robin

