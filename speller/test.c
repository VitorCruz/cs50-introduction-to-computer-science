

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// ANOTHER FUNC
// bool freeLinkedList(node *element);

// TODO: Choose number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// KEEP TRACK OF SIZE OF DICTIONARY, STARTS AT 0 WHEN NOT LOADED
int size_of_dictionary = 0;

#define DICTIONARY "dictionaries/small"


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int result = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        result += word[i];
    }

    return (result % N);
}


bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            //fclose(file);
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        size_of_dictionary ++;
        free(n);
    }

    fclose(file);
    return true;

}

int main(int argc, char *argv[])
{
    char *dictionary = DICTIONARY;
    bool loaded = load(dictionary);


    printf("%s\n", table[0]->next->word);
}