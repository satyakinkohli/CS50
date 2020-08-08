from sys import argv, exit
from cs50 import SQL
from csv import reader

db = SQL("sqlite:///students.db")

if (len(argv) != 2):
    print("Usage: python dna.py characters.csv")
    exit(1)

with open(argv[1], newline='') as HogwartsCSV:
    characters = reader(HogwartsCSV)
    for character in characters:
        if (character[0] == "name"):
            continue

        fullName = character[0].split()
        if len(fullName) == 2:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       fullName[0], None, fullName[1], character[1], character[2])

        elif len(fullName) == 3:
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       fullName[0], fullName[1], fullName[2], character[1], character[2])