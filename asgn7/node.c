#include "node.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

//Creates and returns a pointer node with the corresponding oldspeak and newspeak
//
//oldspeak: the oldspeak word
//newspeak: the newspeak word
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));

    if (n) {
        //set children to NULL
        n->left = NULL;
        n->right = NULL;

        if (oldspeak != NULL) {
            n->oldspeak = strdup(oldspeak); //duplicate word
        } else {
            n->oldspeak = NULL;
        }

        if (newspeak != NULL) {
            n->newspeak = strdup(newspeak); //duplicate word
        } else {
            n->newspeak = NULL;
        }
    } else {
        free(n);
        n = NULL;
    }

    return n;
}

//Deletes the node n
//Returns void
//
//NOTE: DO NOT DELETE LEFT OR RIGHT CHILD
void node_delete(Node **n) {
    if ((*n)->newspeak) {
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
    }

    if ((*n)->oldspeak) {
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
    }

    if ((*n)) {
        free(*n);
        *n = NULL;
    }
    return;
}

//Print function that prints the oldspeak and newspeak fields of node
//NOTE: print statements was provided in assignment doc
void node_print(Node *n) {
    if ((n->oldspeak != NULL) && (n->newspeak != NULL)) { //if there is a translation
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }

    if ((n->oldspeak != NULL) && (n->newspeak == NULL)) { //if there is no translation
        printf("%s\n", n->oldspeak);
    }
    return;
}
