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

//NOTE: Some of the code is based off of Eric's pseudocode

HashTable *
    ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;

        ht->size = size;

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
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t hash_index = hash(ht->salt, oldspeak) % ht_size(ht);
    return bst_find(ht->trees[hash_index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t hash_index = hash(ht->salt, oldspeak) % ht_size(ht);
    ht->trees[hash_index] = bst_insert(ht->trees[hash_index], oldspeak, newspeak);
    return;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        if (ht->trees[i] != NULL) {
            counter++;
        }
    }
    return counter;
}

double ht_avg_bst_size(HashTable *ht) {
    uint32_t sizes = 0;
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        sizes += bst_size(ht->trees[i]);
    }

    return sizes / ht_count(ht);
}

double ht_avg_bst_height(HashTable *ht) {
    uint32_t heights = 0;
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        heights += bst_height(ht->trees[i]);
    }
    return heights / ht_count(ht);
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); ++i) {
        printf("INDEX: %" PRIu32 "\n", i);
        bst_print(ht->trees[i]);
    }
    return;
}
