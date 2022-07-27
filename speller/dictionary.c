// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];

// Count the size of the dict
unsigned int dict_size = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dict_point = fopen(dictionary, "r");

    // check if dictionary returns NULL
    if (dictionary == NULL)
    {
        return 1;
    }

    char new_word[LENGTH + 1];

    while (fscanf(dict_point, "%s", new_word) != EOF)
    {
        // new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // copy word
        strcpy(n->word, new_word);

        // create hash
        n->next = table[hash(new_word)];
        table[hash(new_word)] = n;

        dict_size++;
    }
    fclose(dict_point);

    return true;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function taken from : https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
    unsigned int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;

    // long whash = 0;
    // // TODO: Improve this hash function
    // for (int i = 0; i < strlen(word); i++)
    // {
    //     whash += tolower(word[i]);
    // }
    // // printf("whash:%ld\n", whash);
    // return whash % N;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word
    unsigned int hashcheck = hash(word);
    node *cursor = table[hashcheck];

    // traverse linked list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // run through all buckets
    for (int i = 0; i < N; i++)
    {
        // set cursor and tmp pointers
        node *cursor = table[i];
        // until the cursor is NULL, keep chaing cursor to next and delete tmp
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        // if cursor is NULL and it is the last bucket then finish unloading
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
