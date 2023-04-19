#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool is_letter(char c);
bool is_space_char(char c);
bool is_point(char c);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_index(int letter_count, int word_count, int sentence_count);

int ascii_space = 32;

int main(void)
{
    // GET TEXT FROM USER
    string text = get_string("Text: ");

    // GIVE LETTERS
    int letter_count = count_letters(text);
    //printf("%i letters\n", letter_count);

    // GIVE WORD COUNT
    int word_count = count_words(text);
    //printf("%i words\n", word_count);

    // GIVE SENTENCE COUNT
    int sentence_count = count_sentences(text);
    //printf("%i sentences\n", sentence_count);

    // GIVE INDEX
    int index = coleman_index(letter_count, word_count, sentence_count);
    //printf("Index: %i\n", index);

    // PRINT RESULT
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// COUNT LETTERS
bool is_letter(char c)
{
    if ((((int) c > 64) && ((int) c < 91)) || (((int) c > 96) && ((int) c < 123)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_letters(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        if (is_letter(c))
        {
            count++;
        }
    }

    return count;
}

// COUNT WORDS
bool is_space_char(char c)
{
    if ((int) c == 32)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool is_multiple(char c)
{
    if ((int) c == 39)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool is_point(char c)
{
    if ((int) c == 46)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_words(string text)
{
    // lets try to count simply spaces
    int space_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (is_space_char(text[i]))
        {
            space_count++;
        }
        if (is_multiple(text[i]))
        {
            if (i + 1 < strlen(text) && (int) text[i + 1] != 115)
            {
                space_count++;
            }
        }
    }
    return space_count + 1;
}


// COUNT SENTENCES
bool is_end_of_sentence(char c)
{
    if ((int) c == 46 || (int) c == 33 || (int) c == 63)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_sentences(string text)
{
    int sentence_count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (is_end_of_sentence(text[i]))
        {
            sentence_count++;
        }
    }
    return sentence_count;
}


// COUNT INDEX
int coleman_index(int letter_count, int word_count, int sentence_count)
{
    int index = 0;

    // L -> average number of letters per 100 words in the text
    // S -> average number of sentences per 100 words in the text

    float L = 100 * letter_count / word_count;
    float S = 100 * sentence_count / word_count;

    index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}