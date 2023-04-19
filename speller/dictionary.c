// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO did
    // GET HASH VALUE
    int hash_v = hash(word);

    node *word_n = table[hash_v];

    // CHECK WORD
    while (word_n != NULL)
    {
        if (strcasecmp(word, word_n->word) == 0)
        {
            return true;
        }
        word_n = word_n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: did Improve this hash function
    // RETURN ASCII VALUES OF CHARACHTERS IN THE WORD
    long total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
    // return toupper(word[0]) - 'A';
}

int dictionary_size = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO did
    FILE *dict_p = fopen(dictionary, "r");

    // CHECK DICTIONARY
    if (dictionary == NULL)
    {
        printf("Could not open dictionary");
        return false;
    }


    char word_next[LENGTH + 1];
    while (fscanf(dict_p, "%s", word_next) != EOF)
    {
        // ALLOCATE MEMORY FOR WORDS
        node *n_word = malloc(sizeof(node));

        if (n_word == NULL)
        {
            return false;
        }

        // WORD COPY TO NODE
        strcpy(n_word->word, word_next);

        // GET HASH VALUE
        int hash_value = hash(word_next);

        // INSERT VALUE TO TABLE
        n_word-> next = table[hash_value];
        table[hash_value] = n_word;

        dictionary_size++;
    }

    // CLOSE FILE
    fclose(dict_p);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO did
    // return 0;
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO did
    // FREE ALL NODES
    for (int i = 0; i < N; i++)
    {
        node *n_word = table[i];

        while (n_word != NULL)
        {
            node *temp = n_word;
            n_word = n_word->next;
            free(temp);
        }
    }
    return true;
}
