# include <stdio.h>
# include <cs50.h>
# include <math.h>

float get_positive_val(string prompt);

int main(void)
{
    float n = get_positive_val("How many dollars change do I owe you, sir?: ");
    n = round(n * 100);
    printf("Alright sir! I will return you %f cents.\n", n);

    if ((int)n % (int)25 == 0)
    {
        int k = (n / 25);
        printf("The minimum number of coins I will be giving you to complete this transaction is %d\n", k);
    }

    else if ((int)n % (int)25 != 0)
    {
        int a = (n / 25);
        a = round(a * 1);

        int m = ((int)n % (int)25);

        int p = (m / 10);
        p = round(p * 1);

        int q = (m % 10);

        int r = (q / 5);
        r = round(r * 1);

        int s = (q % 5);

        int t = (s / 1);
        t = round(t * 1);

        int z = (a + p + r + t);

        printf("The minimum number of coins I will be giving you to complete this transaction is %d\n", z);
    }
}

float get_positive_val(string prompt)
{
    float n;

    do
    {
        n = get_float("%s", prompt);
    }
    while (n < 0);
    return n;
}
