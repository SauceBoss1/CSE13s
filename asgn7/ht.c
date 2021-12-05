#include "ht.h"
#include "bst.h"
#include "node.h"
#include "salts.h"
#include "speck.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

uint64_t lookups = 0;

//NOTE: Some of the code is based off of Eric's pseudocode

//Creates a hashtable and returns the pointer to the newly create hashtable
//Returns a HashTable or NULL if unable to allocate memory
//
//size: the size of the hash table you want to create
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        //sets the salt
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;

        //set the size of the hash table
        ht->size = size;

        //create an array of nodes
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        if (!ht->trees) {
            free(ht->trees);
            ht->trees = NULL;
        }

        return ht;
    }
    free(ht);
    ht = NULL;
    return ht;
}

//Deletes the Hash table
//Returns void
//
//ht: hash table to delete
//NOTE: pseudocode provided by Eric
void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->trees) {
        for (uint32_t i = 0; i < (*ht)->size; ++i) {
            if ((*ht)->trees[i] != NULL) {
                bst_delete(&(*ht)->trees[i]);
            }
        }

        free((*ht)->trees);
        free(*ht);
        *ht = NULL;
    }

    return;
}

//Returns the size of the hash table as a uint32_t
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

//Looks up oldspeak in the Hash Table
//Returns the node that contains the oldspeak
//
//ht: hash table to look through
//oldspeak: the key to lookup
//NOTE: Pseudocode was provided by Eric
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups++;

    //hash oldspeak
    uint32_t hash_index = hash(ht->salt, oldspeak) % ht_size(ht);
    return bst_find(ht->trees[hash_index], oldspeak);
}

//Inserts oldspeak and its corresponding newspeak into hash table
//Returns void
//
//ht: hash table to insert oldspeak into
//oldspeak: key of hash table
//newspeak: the value of oldspeak
//NOTE: pseudocode provided by Eric
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups++;

    //hash oldspeak
    uint32_t hash_index = hash(ht->salt, oldspeak) % ht_size(ht);
    ht->trees[hash_index] = bst_insert(ht->trees[hash_index], oldspeak, newspeak);
    return;
}

//Counts and returns the number of non-null trees in hash table as a uint32_t
//
//ht: the hashtable to count
//NOTE: pseudocode provided by Eric
uint32_t ht_count(HashTable *ht) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        if (ht->trees[i] != NULL) {
            counter++;
        }
    }
    return counter;
}

//Calculates and returns the average bst size in the hash table as a double
//
//ht: hash table
//NOTE: pseudocode provided by Eric
double ht_avg_bst_size(HashTable *ht) {
    uint32_t sizes = 0;
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        sizes += bst_size(ht->trees[i]);
    }

    return (double) sizes / (double) ht_count(ht);
}

//Calculates and returns the average bst height of the hash table
//
//ht: hashtable
//NOTE: pseudocode provided by Eric
double ht_avg_bst_height(HashTable *ht) {
    uint32_t heights = 0;
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        heights += bst_height(ht->trees[i]);
    }
    return (double) heights / (double) ht_count(ht);
}

//Debug function that prints the hash table and its trees
//Returns void
//
//ht: hash table
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        if (ht->trees[i] != NULL) {
            printf("INDEX: %" PRIu32 "\n", i);
            bst_print(ht->trees[i]);
        }
    }
    return;
}
