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

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint64_t i = 0; i < ALPHABET; ++i) {
        if (hist[i] > 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
            //node_print(n);
        }
    }

    Node *left, *right, *parent;
    while (pq_size(q) > 1) {
        //pq_print(q);
        dequeue(q, &left);
        dequeue(q, &right);

        /*
		printf("LEFT\n");
		node_print(left);
		printf("RIGHT\n");
		node_print(right);
		puts("");
        //node_print(left);
        //node_print(right);
		*/
        parent = node_join(left, right);
        enqueue(q, parent);
    }
    Node *root;
    dequeue(q, &root);

    pq_delete(&q);
    //node_print(root);

    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    static Code c = { 0, { 0 } };
    uint8_t bit = 0;
    //printf("bit: %"PRIu8"\n", bit);
    if (root != NULL) {
        //puts("if root != NULL");
        if (root->left == NULL && root->right == NULL) {
            //puts("build_code: left and right == null");
            table[root->symbol] = c;
            //printf("%c ", root->symbol);
            //code_print(&table[root->symbol]);
        } else {
            if (root->left != NULL) {
                code_push_bit(&c, 0);
                build_codes(root->left, table);
                code_pop_bit(&c, &bit);
            }

            if (root->right != NULL) {
                code_push_bit(&c, 1);
                build_codes(root->right, table);
                code_pop_bit(&c, &bit);
            }

            //code_print(table);
        }
    }
    return;
}

void dump_tree(int outfile, Node *root) {
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!root->left && !root->right) {
            //uint8_t buffer[] = { 'L', root->symbol };
            //write_bytes(outfile, buffer, 2);

            //LEAF
            uint8_t L = 'L';
            write_bytes(outfile, &L, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            //INTERIOR
            uint8_t I = 'I';
            write_bytes(outfile, &I, 1);
        }
    }
}

Node *rebuild_tree(uint16_t bytes, uint8_t tree_dump[static bytes]) {
    Stack *s = stack_create(bytes);

    Node *root;
    for (uint16_t i = 0; i < bytes; ++i) {
        if (tree_dump[i] == 'I') {
            Node *left, *right, *join;
            stack_pop(s, &right);
            stack_pop(s, &left);

            join = node_join(left, right);
            stack_push(s, join);
        }
        if (tree_dump[i] == 'L') {
            Node *n = node_create(tree_dump[i + 1], 0);
            stack_push(s, n);
            i++; //prevents iterating through the same symbol
        }
    }
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {
    if (*root && root) {
        if ((*root)->left) {
            delete_tree(&(*root)->left);
        }

        if ((*root)->right) {
            delete_tree(&(*root)->right);
        }
        node_delete(root);
    }
}

/*
int main(void) {
    return 0;
}*/
