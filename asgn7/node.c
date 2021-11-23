#include "node.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

Node *node_create(char *oldspeak, char *newspeak){
    Node *n = (Node * ) malloc(sizeof(Node));

    if (n){
        n->left = NULL;
        n->right = NULL;
        if (oldspeak != NULL){
            n->oldspeak = strdup(oldspeak);
        } else {
            n->oldspeak = NULL;
        }

        if (newspeak != NULL){
            n->newspeak = strdup(newspeak);
        } else {
            n->newspeak = NULL;
        }
    } else {
        free(n);
        n = NULL;
    }

    return n;
}

void node_delete(Node **n){
    if(*n->newspeak){
        free(*n->newspeak);
        *n->newspeak = NULL;
    }

    if (*n->oldspeak){
        free(*n->oldspeak);
        *n->oldspeak = NULL;
    }

    if (*n){
        free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n){
    if(n->left){
        node_print(n->left);
    }
    
    if( (n->oldspeak != NULL) && (n->newspeak != NULL) ){
        printf("%s -> %s\n", n->oldspeak , n->newspeak);
    }
    
    if ( (n->oldspeak != NULL) && (n->newspeak == NULL) ){
        printf("%s\n", n->oldspeak);
    }
    
    if (n->right){
        node_print(n->right);
    }
    return;
}
