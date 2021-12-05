#include "bst.h"
#include "node.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>

#define max(x, y) (x > y ? x : y) //function provided in lecture 18

uint64_t branches = 0;

//Creates an empty tree
//Returns a pointer that points to NULL
//
//NOTE: Psuedocode was provided by Eric
Node *bst_create(void) {
    return NULL;
}

//Deletes a tree using post-order traversal
//Returns void
//
//root: the tree to delete
void bst_delete(Node **root) {
    //Post-order traversal
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
    return;
}

//Returns the height of the bst as a uint32_t
//
//NOTE: code taken from bst lecture slides. Originally written by Prof. Long
uint32_t bst_height(Node *root) {
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

//Returns the # of nodes in the tree as a uint32_t
//
//NOTE: pseudo code was provided by Eric
uint32_t bst_size(Node *root) {
    if (root != NULL) {
        return bst_size(root->left) + bst_size(root->right) + 1;
    }
    return 0;
}

//Finds the node with the corresponding oldspeak
//Returns a null tree if nothing was found
//else it returns the found node
//
//root: the tree to search
//oldspeak: the key to base our search on
//
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

//Inserts a node into the bst
//Returns the newly the tree with the newly inserted node.
//
//root: tree to update
//oldspeak: the node key
//newspeak: the node value
//
//NOTE: code based from lecture 18. Originally written by either Eugene or Prof. Long
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches++;
            root->left = bst_insert(root->left, oldspeak, newspeak); //update left child
        } else if (strcmp(root->oldspeak, oldspeak) != 0) {
            branches++;
            root->right = bst_insert(root->right, oldspeak, newspeak); //update right child
        }
        return root;
    }

    return node_create(oldspeak, newspeak);
}

//Prints the tree in a inorder traversal fashion
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
