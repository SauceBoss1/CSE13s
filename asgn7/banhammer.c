#include "bf.h"
#include "bv.h"
#include "speck.h"
#include "ht.h"
#include "node.h"
#include "bst.h"
#include "parser.h"
#include "messages.h"

#include <regex.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define OPTIONS         "ht:f:s"
#define WORD            "[a-zA-Z0-9_'-]+"
#define TWO_EXP_SIXTEEN 65536
#define TWO_EXP_TWENTY  1048576

const char *goodpeak_message;
const char *mixspeak_message;
const char *badspeak_message;

void read_badspeak(BloomFilter *bf, HashTable *ht) {
    FILE *badspeak = fopen("./badspeak.txt", "r");

    int input = 0;

    if (badspeak == NULL) {
        fprintf(stderr, "Couldn't open badspeak.txt!\n");
        exit(1);
    }

    char buff[1024];
    while ((input = fscanf(badspeak, "%s\n", buff)) != EOF) {
        if (input <= 0) {
            fprintf(stderr, "A problem has occurred while reading badspeak.txt!\n");
            exit(1);
        }

        bf_insert(bf, buff);
        ht_insert(ht, buff, NULL);
    }

    fclose(badspeak);
    return;
}

void read_newspeak(BloomFilter *bf, HashTable *ht) {
    FILE *newspeak = fopen("./newspeak.txt", "r");

    int input = 0;

    if (newspeak == NULL) {
        fprintf(stderr, "Couldn't open newspeak.txt!\n");
        exit(1);
    }

    char newWord[1024]; //newspeak buffer
    char oldWord[1024]; //oldspeak buffer
    while ((input = fscanf(newspeak, "%s %s\n", oldWord, newWord)) != EOF) {
        if (input <= 0) {
            fprintf(stderr, "An error has occurred while reading newspeak.txt!\n");
        }
        bf_insert(bf, oldWord);
        ht_insert(ht, oldWord, newWord);
    }
    fclose(newspeak);
    return;
}

char *conv_to_lowercase(char *word) {
    char *temp_string = (char *) calloc(strlen(word) + 1, sizeof(char));

    for (uint32_t i = 0; i < strlen(word); ++i) {
        temp_string[i] = tolower((char) word[i]);
    }

    return temp_string;
}

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t ht_def_size = TWO_EXP_SIXTEEN;
    uint32_t bf_def_size = TWO_EXP_TWENTY;
    bool suppress = false;

    branches = 0;
    lookups = 0;

    regex_t re;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': ht_def_size = strtol(optarg, NULL, 10); break;
        case 'f': bf_def_size = strtol(optarg, NULL, 10); break;
        case 's': suppress = true; break;
        }
    }

    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        exit(1);
    }

    BloomFilter *bf = bf_create(bf_def_size);
    HashTable *ht = ht_create(ht_def_size);

    read_badspeak(bf, ht);
    read_newspeak(bf, ht);

    //bf_print(bf);
    //ht_print(ht);

    char *raw_word = NULL;

    Node *user_badspeak = bst_create();
    Node *user_mixspeak = bst_create();

    //NOTE: Regex examples of how to use parser.c was provided by Eugene
    //In assignment doc
    while ((raw_word = next_word(stdin, &re)) != NULL) {
        //The input may have capital letters, so make them all lowercase
        char *word = raw_word != NULL ? conv_to_lowercase(raw_word) : NULL;

        if (bf_probe(bf, word)) {
            Node *look_up = ht_lookup(ht, word);
            if (look_up->oldspeak != NULL && look_up->newspeak == NULL) {
                user_badspeak = bst_insert(user_badspeak, look_up->oldspeak, look_up->newspeak);
            }

            if (look_up->oldspeak != NULL && look_up->newspeak != NULL) {
                user_mixspeak = bst_insert(user_mixspeak, look_up->oldspeak, look_up->newspeak);
            }
        }

        free(word);
    }

    if (suppress) {
        double avg_bst_size = ht_avg_bst_size(ht);
        double avg_bst_height = ht_avg_bst_height(ht);
        double avg_branches = (double) branches / (double) lookups;
        double ht_load = 100 * ((double) ht_count(ht) / (double) ht_size(ht));
        double bf_load = 100 * ((double) bf_count(bf) / (double) bf_size(bf));

        printf("Average BST size: %.6f\n", avg_bst_size);
        printf("Average BST height: %.6f\n", avg_bst_height);
        printf("Average branches traversed: %.6f\n", avg_branches);
        printf("Hash table load: %.6f%%\n", ht_load);
        printf("Bloom filter load: %.6f%%\n", bf_load);
    } else {

        if (user_badspeak != NULL && user_mixspeak != NULL) {
            printf("%s", mixspeak_message);
            bst_print(user_badspeak);
            bst_print(user_mixspeak);
        }

        if (user_badspeak != NULL && user_mixspeak == NULL) {
            printf("%s", badspeak_message);
            bst_print(user_badspeak);
        }

        if (user_badspeak == NULL && user_mixspeak != NULL) {
            printf("%s", goodspeak_message);
            bst_print(user_mixspeak);
        }
    }

    bst_delete(&user_mixspeak);
    bst_delete(&user_badspeak);
    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
    return 0;
}
