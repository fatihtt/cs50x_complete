#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // char c = 'A';
    // printf("ASCII code of %c is %d\n", c, c);



    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    //printf("Player 1: %i, Player 2: %i\n", score1, score2);

    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    int score = 0;

    // determine length
    int length = strlen(word);

    // for every charachter, find upper case equals of charachters and get index number
    for (int i = 0; i < length; i++)
    {
        char c = word[i];
        if (islower(c))
        {
            c = toupper(c);
        }

        if (((int) c) > 64 && ((int) c < 91))
        {
            int index_number = ((int) c) - 65;

            score = score + POINTS[index_number];
        }
    }


    return score;
}
