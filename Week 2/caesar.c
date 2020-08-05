# include <cs50.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>

void count_letters(string x);

int k;

int main(int argc, char *argv[])
{

    if (((argc != 2) || (((int)*argv[1] < 47) || ((int)*argv[1] > 58))))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int g = strlen(argv[1]);

    for (int i = 0; i < g; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    printf("Success\nKey = %s\n", argv[1]);

    k = atoi(argv[1]);

    string x = get_string("Plaintext: ");

    count_letters(x);
}

void count_letters(string x)
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(x); i < n; i++)
    {
        if (x[i] >= 'a' && x[i] <= 'z')
        {
            printf("%c", (((x[i] - 97) + k) % 26) + 97); // print out lowercase with key
        }

        if (x[i] >= 'A' && x[i] <= 'Z')
        {
            printf("%c", (((x[i] - 65) + k) % 26) + 65); // print out uppercase with key
        }

        if ((x[i] < 'a' && x[i] > 'Z') || x[i] > 'z' || x[i] < 'A')
        {
            printf("%c", x[i]);
        }
    }
    printf("\n");
}
