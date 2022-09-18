#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int getGrade(int sentences, int words, int letters);

int main(void)
{
    string texto = get_string("Text:\n");
    printf("%s\n", texto);

    int len_text = strlen(texto);

    // words starts at 1, becausa I'll count spaces and theres a final word + spaces = number of words
    int words = 1;
    int sentences = 0;
    int letters = 0;

    for (int i = 0; i < len_text; i++)
    {
        if (texto[i] == 32)
        {
            words += 1;
        }
        if (texto[i] == 46 || texto[i] == 33 || texto[i] == 63)
        {
            sentences += 1;
        }
        if ((texto[i] >= 65 && texto[i] <= 90) || (texto[i] >= 97 && texto[i] <= 122))
        {
            letters += 1;
        }
    }
    printf("Your text has %i phrases\n", sentences);
    printf("Your text has %i words\n", words);
    printf("Your text has %i letters\n\n", letters);

    int grade = getGrade(sentences, words, letters);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i: \n", grade);
    }
}

int getGrade(int sentences, int words, int letters)
{
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}