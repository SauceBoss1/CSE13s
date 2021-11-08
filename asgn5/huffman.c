#include "huffman.h"
#include "node.h"
#include "code.h"
#include "stack.h"
#include "io.h"
#include "defines.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

//Builds the huffman tree
//Returns a node
//hist: a histogram of ascii values
//
//NOTE: code taken from assignment doc
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint64_t i = 0; i < ALPHABET; ++i) { //go through histogram
        if (hist[i] > 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }

    Node *left, *right, *parent;
    while (pq_size(q) > 1) { //builds a huffman tree using the pqs
        dequeue(q, &left);
        dequeue(q, &right);

        parent = node_join(left, right);
        enqueue(q, parent);
    }
    Node *root;
    dequeue(q, &root);

    pq_delete(&q);

    return root;
}

//Builds huffman codes
//root: takes in a huffman tree
//table: takes in a code table
//NOTE: taken from assignment doc
void build_codes(Node *root, Code table[static ALPHABET]) {
    static Code c = { 0, { 0 } }; //recommended by eric (tutor)
    uint8_t bit = 0;
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) { // set the code for the character
            table[root->symbol] = c;
        } else {
            if (root->left != NULL) { //if we are on the left then push a 0
                code_push_bit(&c, 0);
                build_codes(root->left, table);
                code_pop_bit(&c, &bit);
            }

            if (root->right != NULL) { //right gets pushed a 1
                code_push_bit(&c, 1);
                build_codes(root->right, table);
                code_pop_bit(&c, &bit);
            }
        }
    }
    return;
}

//Dumps the tree to the outfile
//outfile: the file to write to
//root: the tree to dump
//NOTE: taken from assignment doc
void dump_tree(int outfile, Node *root) {
    if (root) {
        //uses post-order traversal
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!root->left && !root->right) {
            //we reached a leaf if the left and right nodes are NULL

            //WRITE OUT LEAF
            uint8_t L = 'L';
            write_bytes(outfile, &L, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            //WRITE OUT INTERIOR
            uint8_t I = 'I';
            write_bytes(outfile, &I, 1);
        }
    }
    return;
}

//Rebuilds the huffman tree when decoding
//Returns the tree node
//bytes: the size of the tree
//tree_dump: takes in a huffman tree dump
Node *rebuild_tree(uint16_t bytes, uint8_t tree_dump[static bytes]) {
    Stack *s = stack_create(bytes);

    Node *root;
    for (uint16_t i = 0; i < bytes; ++i) {
        if (tree_dump[i] == 'I') {
            //if we reach an interior node, then pop right, left, then join
            Node *left, *right, *join;
            stack_pop(s, &right);
            stack_pop(s, &left);

            join = node_join(left, right);
            stack_push(s, join);
        }
        if (tree_dump[i] == 'L') {
            //push a new node if we found a leaf
            Node *n = node_create(tree_dump[i + 1], 0);
            stack_push(s, n);
            i++; //prevents iterating through the same symbol
        }
    }
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}
//Deletes a huffman tree
//uses post order traversal to delete all nodes in tree
void delete_tree(Node **root) {
    if (*root && root) {
        if ((*root)->left) { //check to make sure a left node exists
            delete_tree(&(*root)->left);
        }

        if ((*root)->right) { //checl to make sure a right node exists
            delete_tree(&(*root)->right);
        }
        node_delete(root);
    }
    return;
}
