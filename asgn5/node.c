#include "node.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
        n->left = NULL;
        n->right = NULL;
    } else {
        free(n);
        n = NULL;
    }

    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

Node *node_join(Node *left, Node *right) {
    Node *n = node_create('$', left->frequency + right->frequency);
    n->left = left;
    n->right = right;
    return n;
}

void node_print(Node *n) {
    if (n != NULL) {
        if (n->left != NULL) {
            node_print(n->left);
        }
        if (n->right != NULL) {
            node_print(n->right);
        }
        fprintf(stderr, "symbol: %c frequency: %" PRIu64 "\n", n->symbol, n->frequency);
    }
}

//Below is an example of how Node will be used

/*
int main(void) {
    Node *left = node_create('a', 3);
    Node *right = node_create('a', 2);
    Node *n = node_join(left, right);
    node_print(n);

    node_delete(&n);
    node_delete(&left);
    node_delete(&right);

    return 0;
}*/
