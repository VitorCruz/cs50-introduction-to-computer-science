// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"



// Defines struct for a node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const int N = 15000;
int size_of_dictionary = 0;
node *table[N];

// NEW FUNCTION
bool freeLinkedList(node *element);


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
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
    unsigned int result = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        result += pow(word[i], 3);
    }
    return result % N;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char c[LENGTH + 1];
    while (fscanf(file, "%s", c) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            unload();
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
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_of_dictionary;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        freeLinkedList(table[i]);
    }

    return true;
}

// RECURSIVE FREE LINKED LIST
bool freeLinkedList(node *element)
{
    if (element == NULL)
    {
        return true;
    }
    else if (element->next == NULL)
    {
        free(element);
        return true;
    }
    else
    {
        freeLinkedList(element->next);
    }

    free(element);
    return true;
}


