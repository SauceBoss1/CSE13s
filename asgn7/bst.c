#include "bst.h"
#include "node.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>

#define max(x, y) (x > y ? x : y)

uint64_t branches = 0;

//NOTE: Psuedocode was provided by Eric
Node *bst_create(void) {
    return NULL;
}

void bst_delete(Node **root) {
    //Post-order traversal
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
    return;
}

//NOTE: code taken from bst lecture slides. Originally written by Prof. Long
uint32_t bst_height(Node *root) {
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

uint32_t bst_size(Node *root) {
    if (root != NULL) {
        return bst_size(root->left) + bst_size(root->right) + 1;
    }
    return 0;
}

//NOTE: code was based on Eric's pseudocode
Node *bst_find(Node *root, char *oldspeak) {

    Node *curr = root;

    if (root != NULL && oldspeak != NULL) {
        while (curr != NULL && strcmp(curr->oldspeak, oldspeak) != 0) {
            if (strcmp(curr->oldspeak, oldspeak) > 0) {
                branches++;
                curr = curr->left;
            } else {
                branches++;
                curr = curr->right;
            }
        }
    }
    return curr;
}

//code based from eric's pseudocode
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches++;
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else if (strcmp(root->oldspeak, oldspeak) != 0) {
            branches++;
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        return root;
    }

    return node_create(oldspeak, newspeak);
}

void bst_print(Node *root) {
    if (root->left) {
        bst_print(root->left);
    }

    if (root) {
        node_print(root);
    }

    if (root->right) {
        bst_print(root->right);
    }
    return;
}

/*
int main(void){
    Node *tree = bst_create();
    
    tree = bst_insert(tree, "Joe", "Mama");
    tree = bst_insert(tree, "Deez", NULL);
    tree = bst_insert(tree, "NUTZ", "GOTEEM");
    tree = bst_insert(tree, "Sugma", "Balls");
    tree = bst_insert(tree, "Sugma", "Balls");
    
    printf("height: %"PRIu32" size: %"PRIu32"\n", bst_height(tree), bst_size(tree));

    bst_print(tree);
    
    bst_delete(&tree);
    return 0;
}*/
