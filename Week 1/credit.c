# include <cs50.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>

int countdigits = 0;
int sum = 0;
int addition = 0;
int move = 0;
int total = 0;

int invalid();
int countDigits(long n);
void check(long n);

int main(void)
{
    long n;
    do
    {
        n = get_long("What is your credit/debit card number?: ");
        countdigits = countDigits(n);
    }
    while (n < 0);

    if (countdigits != 13 && countdigits != 15 && countdigits != 16)
    {
        printf("INVALID\n");
    }

    check(n);
}

int countDigits(long n)
{
    while (n > 0)
    {
        n = (n / 10);
        countdigits++;
    }
    return countdigits;
}

void check(long n)
{
    int number[countdigits];

    for (int i = 0; i < countdigits; i++)
    {
        number[i] = n % 10;
        n = n / 10;
    }

    if (countdigits == 13 || countdigits == 15)
    {
        int digits[(countdigits - 1) / 2];
        for (int i = 1; i < countdigits; i = i + 2)
        {
            for (int j = i - ((i + 1) / 2); j < (countdigits + 1); j++)
            {
                int z = number[i] * 2;
                if (z > 9)
                {
                    int b = z;
                    while (b > 9)
                    {
                        b = (b % 10);
                        int f = b + 1;
                        digits[j] = f;
                    }
                }

                if (z <= 9)
                {
                    digits[j] = z;
                }
                break;
            }
        }

        for (int k = 0; k < ((countdigits - 1) / 2); k++)
        {
            sum = digits[k];
            addition += sum;
        }

        for (int m = 0; m < countdigits; m = m + 2)
        {
            int add = number[m];
            move += add;
        }

        total = addition + move;

        if (countdigits == 13)
        {
            if (total % 10 == 0)
            {
                if (number[countdigits - 1] == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }

        if (countdigits == 15)
        {
            if (total % 10 == 0)
            {
                if ((number[countdigits - 1] == 3) && ((number[countdigits - 2] == 4) || (number[countdigits - 2] == 7)))
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }

    if (countdigits == 16)
    {
        int digits[(countdigits) / 2];
        for (int i = 1; i < countdigits; i = i + 2)
        {
            for (int j = i - ((i + 1) / 2); j < (countdigits + 1); j++)
            {
                int z = number[i] * 2;
                if (z > 9)
                {
                    int b = z;
                    while (b > 9)
                    {
                        b = (b % 10);
                        int f = b + 1;
                        digits[j] = f;
                    }
                }

                if (z <= 9)
                {
                    digits[j] = z;
                }
                break;
            }
        }

        for (int k = 0; k < ((countdigits) / 2); k++)
        {
            sum = digits[k];
            addition += sum;
        }

        for (int i = 0; i < countdigits; i = i + 2)
        {
            int add = number[i];
            move += add;
        }

        total = addition + move;

        if ((number[countdigits - 1] == 5) && ((number[countdigits - 2] == 1) || (number[countdigits - 2] == 2) || (number[countdigits - 2] == 3) || (number[countdigits - 2] == 4) || (number[countdigits - 2] == 5)))
        {
            if (total % 10 == 0)
            {
                printf("MASTERCARD\n");
                exit(0);
            }
            else
            {
                printf("INVALID\n");
                exit(0);
            }
        }

        if (number[countdigits - 1] == 4)
        {
            if (total % 10 == 0)
            {
                printf("VISA\n");
                exit(0);
            }
            else
            {
                printf("INVALID\n");
                exit(0);
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
