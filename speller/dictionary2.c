// Implements a dictionary's functionality

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
const unsigned int N = 26;

// Hash table
node *table[N];

// KEEP TRACK OF SIZE OF DICTIONARY, STARTS AT 0 WHEN NOT LOADED
int size_of_dictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *el = table[index];

    while (el != NULL)
    {
        if (strcasecmp(el->word, word) == 0)
        {
            return true;
        }
        el = el->next;
    }

    return false;
}

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

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    char c[LENGTH + 1];

    while ((fscanf(file, "%s", c)) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            //fclose(file);
            return false;
        }

        strcpy(n->word, c);
        n->next = NULL;

        int index = hash(c);

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

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_of_dictionary;
}


bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}





// Unloads dictionary from memory, returning true if successful, else false

/* bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        freeLinkedList(table[i]);
    }

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            return false;
        }
    }

    return true;
}


bool freeLinkedList(node *element)
{
    if (element->next == NULL)
    {
        free(element);
    }
    else
    {
        freeLinkedList(element->next);
    }

    free(element);
    return true;
}
*/