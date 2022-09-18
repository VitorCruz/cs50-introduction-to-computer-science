import os
import string
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

### users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);
#api_key = 'pk_7eabe73ae2d341e0834e135547fa8667'
# export API_KEY=pk_7eabe73ae2d341e0834e135547fa8667

letters = list(string.ascii_letters)

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
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

    userId = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", userId)[0]["cash"]
    stocks = db.execute("SELECT * FROM users_stocks WHERE user_id = ?", userId)

    stock_prices = {}

    for i in stocks:
        try:
            result = lookup(i["stock_symbol"])
            stock_prices[i["stock_symbol"]] = round(float(result["price"]),2)
        except:
            return apology("Oops, something went wrong", 403)

    totalmoney = 0
    totalmoney += cash
    for i in stocks:
        totalmoney += float(i["shares_number"]) * float(stock_prices[i["stock_symbol"]])

    return render_template("index.html", cash=round(cash,2),stocks=stocks, stock_prices=stock_prices, totalmoney=round(totalmoney,2))


@app.route("/cash", methods = ["GET", "POST"])
@login_required
def cash():
    """Show portfolio of stocks"""
    if request.method == "POST":

        try:
            more_cash = float(request.form.get("cash"))
        except:
            more_cash = 0
            return apology("Input a number", 403)
        if more_cash == '':
            return apology("Input a number", 403)

        if more_cash <= 0:
            return apology("Cash needs to be a positive number", 403)

        userId = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", userId)[0]["cash"]
        new_cash = cash + more_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, userId)

        return redirect("/")

    return render_template("cash.html")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        try:
            symbol = request.form.get("symbol")
        except:
            return apology("Invalid Stock Name", 403)
        if symbol == '':
            return apology("Invalid Stock Name", 403)

        try:
            shares = float(request.form.get("shares"))
        except:
            shares = 0
            return apology("Input number of shares", 403)

        if shares <= 0:
            return apology("Shares must be > 0", 403)

        try:
            result = lookup(symbol)
            if result["symbol"] != symbol:
                return apology("Oops, something went wrong", 403)
        except:
            return apology("Oops, something went wrong", 403)

        date = datetime.datetime.now()
        userId = session["user_id"]
        transaction_type = 'buy'
        price = result["price"]
        final_price = shares * price

        rows = db.execute("SELECT * FROM users WHERE id = ?", userId)
        cash_amount = rows[0]["cash"]

        if final_price > cash_amount:
            return apology("Sorry, not enough money to buy selected stocks", 403)

        db.execute("INSERT INTO transactions (datetime,user_id,transaction_type,stock_symbol,stock_price,shares_number,final_price) values (?,?,?,?,?,?,?)", date,userId,transaction_type,symbol,price,shares,final_price)

        new_cash = cash_amount - final_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, userId)

        try:
            user_stocks = db.execute("SELECT * FROM users_stocks WHERE user_id = ? and stock_symbol = ?", userId, symbol)[0]
            if user_stocks["shares_number"] > 0:
                db.execute("UPDATE users_stocks SET shares_number = ? WHERE user_id = ? and stock_symbol = ?", user_stocks["shares_number"] + shares,userId,symbol)
        except:
            db.execute("INSERT INTO users_stocks (user_id,stock_symbol,shares_number) values (?,?,?)", userId,symbol,float(shares))

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():

    userId = session["user_id"]
    try:
        transactions = db.execute("SELECT transaction_id, datetime,user_id,transaction_type,stock_symbol,stock_price,shares_number,final_price FROM transactions WHERE user_id = ?", userId)
    except:
        return apology("You don't have any transaction history", 403)

    return render_template("history.html", transactions = transactions)

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

        try:
            symbol = request.form.get("symbol")
        except:
            return apology("Invalid Stock Name", 403)
        if symbol == '':
            return apology("Invalid Stock Name", 403)

        try:
            result = lookup(symbol)
            return render_template("quoted.html", name = result["name"], price = usd(result["price"]), symbol = result["symbol"])
        except:
            return apology("Oops, something went wrong", 403)


    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        try:
            username = request.form.get("username")
            password = request.form.get("password")
            confirmation = request.form.get("confirmation")
        except:
            print("erro")

        if not username:
            return apology("must provide username", 403)
        elif db.execute("SELECT username FROM users WHERE username = ?", username) == username:
            return apology("username already exists", 403)

        if not password:
            return apology("must provide password", 403)
        if password != confirmation:
            return apology("typed different passwords", 403)

        db.execute("INSERT INTO users (username, hash) values (?, ?)", username, generate_password_hash(password))
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        try:
            symbol = request.form.get("symbol")
        except:
            return apology("Invalid Stock Name", 403)
        if symbol == '':
            return apology("Invalid Stock Name", 403)

        try:
            shares = float(request.form.get("shares"))
        except:
            shares = 0
            return apology("Input number of shares", 403)

        if shares <= 0:
            return apology("Shares must be > 0", 403)

        try:
            result = lookup(symbol)
            if result["symbol"] != symbol:
                return apology("Oops, something went wrong", 403)
        except:
            return apology("Oops, something went wrong", 403)

        date = datetime.datetime.now()
        userId = session["user_id"]
        transaction_type = 'sell'
        price = result["price"]
        final_price = shares * price

        try:
            user_shares = db.execute("Select shares_number from users_stocks where user_id = ? and stock_symbol = ?", userId,symbol)[0]["shares_number"]
        except:
            user_shares = 0

        if shares > user_shares:
            return apology("You don't have that number of shares to sell", 403)

        db.execute("INSERT INTO transactions (datetime,user_id,transaction_type,stock_symbol,stock_price,shares_number,final_price) values (?,?,?,?,?,?,?)", date,userId,transaction_type,symbol,price,shares,final_price)

        cash_amount = db.execute("SELECT * FROM users WHERE id = ?", userId)[0]["cash"]
        new_user_shares = user_shares - shares
        new_cash = cash_amount + final_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, userId)
        db.execute("UPDATE users_stocks SET shares_number = ? WHERE user_id = ? and stock_symbol = ?", new_user_shares,userId,symbol)

        return redirect("/")

    return render_template("sell.html")