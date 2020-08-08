change = input("Change owed: ")

while (change == '' or change.isupper() is True or change.islower() is True):
    print("\nPlease enter a value greater than 0")
    change = (input("Change owed: "))

change = float(change)
change = change * 100
change = int(round(change))

while (change < 0):
    print("\nPlease enter a value greater than 0")
    change = float(input("Change owed: "))

if (change % 25 == 0):
    k = (change / 25)
    print(f"The minimum number of coins I will be giving you to complete this transaction is {k}")

elif (change % 25 != 0):
    a = (change / 25)
    a = int(a)

    m = (change % 25)

    p = (m / 10)
    p = int(p)

    q = (m % 10)

    r = (q / 5)
    r = int(r)

    s = (q % 5)

    t = (s / 1)
    t = int(t)

    z = (a + p + r + t)

    print(f"The minimum number of coins I will be giving you to complete this transaction is {z}")
