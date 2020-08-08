from sys import argv, exit
from cs50 import SQL

db = SQL("sqlite:///students.db")

if (len(argv) != 2):
    print("Usage: python roster.py Name_Of_House")
    exit(1)

students = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last ASC, first ASC", argv[1])

for student in students:
    if (student['middle'] is None or student['middle'] == 'NULL'):
        print(f"{student['first']} {student['last']}, born {student['birth']}")
        continue
    else:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")
        continue

db.execute("DELETE FROM students")