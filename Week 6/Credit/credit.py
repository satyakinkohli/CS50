import math


def check_legality(card):

    k = len(number)
    double_sum = 0
    basic_sum = 0

    for i in range(k - 2, -1, -2):
        if (int(card[i]) * 2 < 10):
            double_sum = double_sum + (int(card[i]) * 2)
        if (int(card[i]) * 2 >= 10):
            double_sum = double_sum + 1 + ((int(card[i]) * 2) - 10)

    for j in range(k - 1, -1, -2):
        basic_sum = basic_sum + int(card[j])

    total_sum = double_sum + basic_sum

    if (total_sum % 10 == 0):
        check_card(card)
    else:
        print("INVALID\n")


def check_card(card):
    if (len(card) == 15):
        print("AMEX\n")
    if (len(card) == 16 and int(card[0]) == 5):
        print("MASTERCARD\n")
    if ((len(card) == 13 or len(card) == 16) and int(card[0]) == 4):
        print("VISA\n")


number = input("Card number: ")

if (number == '' or number.isdigit() is False or (len(number) != 13 and len(number) != 15 and len(number) != 16)):
    print("INVALID\n")
    exit()

number = int(number)
if (number < 0):
    print("INVALID\n")
    exit()

number = str(number)

check_legality(number)
