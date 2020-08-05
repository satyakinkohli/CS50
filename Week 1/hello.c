# include <stdio.h>
# include <cs50.h>

int main(void)
{
    string answer = get_string("Namaste! What is your name?\n");
    printf("Hello, %s\n", answer);
}
