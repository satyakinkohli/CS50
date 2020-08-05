# include <cs50.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

void count_letters(string text);
void count_words(string text);
void count_sentences(string text);
void give_grades(void);

int letters = 0;
int words = 1;
int sentences = 0;


int main(void)
{
    string text = get_string("Text: ");

    count_letters(text);
    count_words(text);
    count_sentences(text);

    give_grades();
}

void count_letters(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (((text[i] >= 'a') && (text[i] <= 'z')) || ((text[i] >= 'A') && (text[i] <= 'Z')))
        {
            letters++;
        }
    }
    printf("Letters: %d\n", letters);
}

void count_words(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    printf("Words: %d\n", words);
}

void count_sentences(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
    }
    printf("Sentences: %d\n", sentences);
}

void give_grades(void)
{
    float L = (((float)letters / words) * 100);
    printf("L = %.5f\n", L);

    float S = (((float)sentences / words) * 100);
    printf("S = %.5f\n", S);

    float index = ((0.0588 * L) - (0.296 * S) - 15.8);

    index = round(index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    if (index > 16)
    {
        printf("Grade 16+\n");
    }

    if ((index > 1) && (index < 16))
    {
        printf("Grade %d\n", (int)index);
    }
}
