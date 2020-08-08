height = input("What is the height of your pyramid?: ")

while (height.isdigit() is False or height is None):
    print("\nPlease enter a value between 1 and 9 (both inclusive).")
    height = (input("What is the height of your pyramid?: "))

height = (int)(height)
while (height < 1 or height > 8):
    print("\nPlease enter a value between 1 and 9 (both inclusive).")
    height = int(input("What is the height of your pyramid?: "))

for i in range(1, height + 1, 1):
    for j in range(height, i, -1):
        print(" ", end="")

    for k in range(0, i, 1):
        print("#", end="")

    print("  ", end="")

    for k in range(0, i, 1):
        print("#", end="")

    print("\n", end="")
