#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    if (score1 > score2)
    {
        printf("Player 1 Wins with %i x %i points\n", score1, score2);
    }
    else if (score2 > score1)
    {
        printf("Player 2 Wins with %i x %i points\n", score2, score1);
    }
    else
    {
        printf("IT'S A TIE: %i x %i points\n", score2, score1);
    }
}

int compute_score(string word)
{
    int count_letters = strlen(word);
    int sum_points = 0;

    for (int i = 0; i < count_letters; i++)
    {
        if (tolower(word[i]) >= 97 && tolower(word[i]) <= 122)
        {
            int letter_number = tolower(word[i]) - 97;
            sum_points += POINTS[letter_number];
        }
    }
    return sum_points;
}
