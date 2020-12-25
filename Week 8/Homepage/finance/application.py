import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    rows = db.execute("SELECT * FROM stocks WHERE user_id = :user",
                          user=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user",
                          user=session["user_id"])[0]['cash']

    total = cash
    stocks = []
    for index, row in enumerate(rows):
        stock_info = lookup(row['symbol'])

        # create a list with all the info about the stock and append it to a list of every stock owned by the user
        stocks.append(list((stock_info['symbol'], stock_info['name'], row['amount'], stock_info['price'], round(stock_info['price'] * row['amount'], 2))))
        total += stocks[index][4]

    return render_template("index.html", stocks=stocks, cash=round(cash, 2), total=round(total, 2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == 'POST':
        symbol = request.form.get('symbol_buy')
        shares = request.form.get('shares_buy')
        stock_details = lookup(symbol)['price']
        cash = db.execute("SELECT cash FROM users WHERE id = :user", user=session["user_id"])[0]['cash']
        # cash = row[0]["cash"]
        paisa = float(shares) * stock_details
        if not stock_details:
            return apology("Could not find the stock")
        if (float(shares) < 0):
            return apology("You cannot buy negative shares")
        if cash < (paisa):
            return apology("You do not have enough cash")

        stock = db.execute("SELECT amount FROM stocks WHERE user_id = :user AND symbol = :symbol", user=session["user_id"], symbol=symbol)
        if not stock:
            db.execute("INSERT INTO stocks(user_id, symbol, amount) VALUES (:user, :symbol, :amount)", user=session["user_id"], symbol=symbol, amount=shares)
        else:
            amount_old = stock[0]["amount"]
            amount_new = amount_old + float(shares)
            db.execute("UPDATE stocks SET amount = :amount WHERE user_id = :user AND symbol = :symbol", user=session["user_id"], symbol=symbol, amount=amount_new)

        new_cash = cash - paisa
        db.execute("UPDATE users SET cash = :amount WHERE id = :user", amount=new_cash, user=session["user_id"])

        db.execute("INSERT INTO transactions(user_id, symbol, amount, paisa) VALUES (:user, :symbol, :amount, :paisa)", user=session["user_id"], symbol=symbol, amount=float(shares), paisa=round(paisa))

        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user", user=session["user_id"])

    transactions = []
    for row in rows:
        stock_info = lookup(row['symbol'])

        transactions.append(list((stock_info['symbol'], stock_info['name'], row['amount'], row['value'], row['date'])))

    # redirect user to index page
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        stock_details = lookup(symbol)
        if not stock_details:
            return apology("Could not find the stock")

        return render_template("quote_final.html", stock=stock_details)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()

    if request.method == 'POST':
        if db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("Username already taken", 403)

        # Insert user and hash of the password into the table
        db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)",
            username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
            username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        nos = int(request.form.get("shares_buy"))
        symbol=request.form.get("symbol")
        price = lookup(symbol)["price"]
        vos = round(price * float(nos))

        amount_before = db.execute("SELECT amount FROM stocks WHERE user_id = :user AND symbol = :symbol", symbol=symbol, user=session["user_id"])[0]['amount']
        amount_after = amount_before - nos

        if amount_after == 0:
            db.execute("DELETE FROM stocks WHERE user_id = :user AND symbol = :symbol", symbol=symbol, user=session["user_id"])
        elif amount_after < 0:
            return apology("That's more than the stocks you own")
        else:
            db.execute("UPDATE stocks SET amount = :amount WHERE user_id = :user AND symbol = :symbol", symbol=symbol, user=session["user_id"], amount=amount_after)

        cash = db.execute("SELECT cash FROM users WHERE id = :user", user=session["user_id"])[0]['cash']
        cash_after = cash + price * float(nos)

        db.execute("UPDATE users SET cash = :cash WHERE id = :user", cash=cash_after, user=session["user_id"])

        db.execute("INSERT INTO transactions(user_id, symbol, amount, value) VALUES (:user, :symbol, :amount, :value)",
        user=session["user_id"], symbol=symbol, amount=-nos, value=vos)

        flash("Sold!")
        return redirect("/")
    else:
        rows = db.execute("SELECT symbol, amount FROM stocks WHERE user_id = :user", user=session["user_id"])

        stocks = {}
        for row in rows:
            stocks[row['symbol']] = row['amount']

        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
