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
    while ((input = fscanf(badspeak, "%s", buff)) != EOF) {
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
    while ((input = fscanf(newspeak, "%s %s", oldWord, newWord)) != EOF) {
        if (input <= 0) {
            fprintf(stderr, "An error has occurred while reading newspeak.txt!\n");
        }
        bf_insert(bf, oldWord);
        ht_insert(ht, oldWord, newWord);
    }

    fclose(newspeak);
    return;
}

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t ht_def_size = TWO_EXP_SIXTEEN;
    uint32_t bf_def_size = TWO_EXP_TWENTY;

    regex_t re;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': ht_def_size = strtol(optarg, NULL, 10); break;
        case 'f': bf_def_size = strtol(optarg, NULL, 10); break;
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

    char *word = NULL;

    Node *user_badspeak = bst_create();
    Node *user_mixspeak = bst_create();
    while ((word = next_word(stdin, &re)) != NULL) {
        puts("here!");
        if (bf_probe(bf, word)) {
            Node *look_up = ht_lookup(ht, word);

            if (look_up->oldspeak != NULL && look_up->newspeak == NULL) {
                bst_insert(user_badspeak, look_up->oldspeak, look_up->newspeak);
            }

            if (look_up->oldspeak != NULL && look_up->newspeak != NULL) {
                bst_insert(user_mixspeak, look_up->oldspeak, look_up->newspeak);
            }
        }
    }

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
        printf("%s", goodpeak_message);
        bst_print(user_mixspeak);
    }

    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
    return 0;
}
