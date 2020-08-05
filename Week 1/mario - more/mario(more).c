#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)
{
    int n = get_positive_int("Positive integer: ");

//        for (int j = n - 1; j > i; j--)
//          {
//             printf(" ");
//          }

    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
          printf(" ");
         }

         for (int k = i; k > -1; k--)
         {
         printf("#");
         }

         {
         printf("  ");
         }

         for (int m = i; m > -1; m--)
        {
            printf("#");
        }

        printf("\n");
    }
}

int get_positive_int(string prompt)
{
    int n;

    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}
