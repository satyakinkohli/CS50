# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <cs50.h>

int final_answer(string x, char s_alphabet[], char b_alphabet[], char alphabet[]);

int main(int argc, char *argv[])
{
    if (argc != 2 || (int)*argv[1] < 65 || (int)*argv[1] > 122 || (((int)*argv[1] > 90) && ((int)*argv[1] < 97)))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    char alphabet[26];

    for (int i = 0; i < 26; i++)
    {
        if (isalpha(argv[1][i]) != 0)
        {
            alphabet[i] = argv[1][i];
        }
        else
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    for (int z = 0; z < 26; z++)
    {
        for (int d = z + 1; d < 26; d++)
        {
            if (alphabet[z] == alphabet[d])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    char b_alphabet[26];

    for (int i = 0; i < 26; i++)
    {
        b_alphabet[i] = (char)(65 + i);
    }

    char s_alphabet[26];

    for (int i = 0; i < 26; i++)
    {
        s_alphabet[i] = (char)(97 + i);
    }

    string x = get_string("plaintext: ");

    final_answer(x, s_alphabet, b_alphabet, alphabet);
}

int final_answer(string x, char s_alphabet[], char b_alphabet[], char alphabet[])
{
    printf("ciphertext: ");

    for (int i = 0, n = strlen(x); i < n; i++)
    {
        int y = 0;

        if (x[i] >= 'a' && x[i] <= 'z')
        {
            for (int k = 0; k < 26; k++)
            {
                if (x[i] == s_alphabet[k])
                {
                    y = k;
                    break;
                }
            }

            if (alphabet[y] >= 'A' && alphabet[y] <= 'Z')
            {
                printf("%c", (char)(alphabet[y] + 32));
            }
            if (alphabet[y] >= 'a' && alphabet[y] <= 'z')
            {
                printf("%c", alphabet[y]);
            }
        }

        if (x[i] >= 'A' && x[i] <= 'Z')
        {
            for (int k = 0; k < 26; k++)
            {
                if (x[i] == b_alphabet[k])
                {
                    y = k;
                    break;
                }
            }

            if (alphabet[y] >= 'A' && alphabet[y] <= 'Z')
            {
                printf("%c", alphabet[y]);
            }
            if (alphabet[y] >= 'a' && alphabet[y] <= 'z')
            {
                printf("%c", (char)(alphabet[y] - 32));
            }
        }

        if ((x[i] < 'a' && x[i] > 'Z') || x[i] > 'z' || x[i] < 'A')
        {
            printf("%c", x[i]);
        }
    }
    printf("\n");
    return 0;
}
