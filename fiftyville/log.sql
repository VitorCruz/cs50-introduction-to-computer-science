-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year =  2021 and month = 7 and day = 28 and street = 'Humphrey Street' and description like '%CS50 duck%';
SELECT * FROM interviews WHERE  year =  2021 and month = 7 and day = 28 and transcript like '%bakery%';
SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25;
SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street';
SELECT * FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street');
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street'))
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street')) and license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25);
SELECT * FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60;
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street')) and license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25) and phone_number in (SELECT caller FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60);
SELECT * FROM airports WHERE city = 'Fiftyville';
SELECT * FROM flights WHERE origin_airport_id in (SELECT id FROM airports WHERE city = 'Fiftyville') AND year =  2021 and month = 7 and day = 29  and hour < 12 ORDER BY hour, minute;
SELECT * FROM passengers WHERE flight_id in (SELECT id FROM flights WHERE origin_airport_id in (SELECT id FROM airports WHERE city = 'Fiftyville') AND year =  2021 and month = 7 and day = 29  and hour < 12);
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street')) and license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25) and phone_number in (SELECT caller FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60) and passport_number in (SELECT passport_number FROM passengers WHERE flight_id in (SELECT id FROM flights WHERE origin_airport_id in (SELECT id FROM airports WHERE city = 'Fiftyville') AND year =  2021 and month = 7 and day = 29  and hour < 12));
SELECT * FROM airports WHERE id in (SELECT destination_airport_id FROM flights WHERE id in (SELECT flight_id FROM passengers WHERE passport_number in (SELECT passport_number FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street')) and license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25) and phone_number in (SELECT caller FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60) and passport_number in (SELECT passport_number FROM passengers WHERE flight_id in (SELECT id FROM flights WHERE origin_airport_id in (SELECT id FROM airports WHERE city = 'Fiftyville') AND year =  2021 and month = 7 and day = 29  and hour < 12)))));
SELECT * FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60 AND caller in (SELECT phone_number FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street')) and license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25) and phone_number in (SELECT caller FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60) and passport_number in (SELECT passport_number FROM passengers WHERE flight_id in (SELECT id FROM flights WHERE origin_airport_id in (SELECT id FROM airports WHERE city = 'Fiftyville') AND year =  2021 and month = 7 and day = 29  and hour < 12)));
SELECT * FROM people where phone_number in (SELECT receiver FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60 AND caller in (SELECT phone_number FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year =  2021 and month = 7 and day = 28 and transaction_type = 'withdraw' and atm_location = 'Leggett Street')) and license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year =  2021 and month = 7 and day = 28 and hour = 10 and minute between 15 and 25) and phone_number in (SELECT caller FROM phone_calls WHERE year =  2021 and month = 7 and day = 28 and duration < 60) and passport_number in (SELECT passport_number FROM passengers WHERE flight_id in (SELECT id FROM flights WHERE origin_airport_id in (SELECT id FROM airports WHERE city = 'Fiftyville') AND year =  2021 and month = 7 and day = 29  and hour < 12))));