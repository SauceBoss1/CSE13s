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

    while (pq_size(q) > 1) {
        Node *left, *right;
        dequeue(q, &left);
        dequeue(q, &right);

        //node_print(left);
        //node_print(right);

        enqueue(q, node_join(left, right));
    }
    Node *root;
    dequeue(q, &root);

    pq_delete(&q);
    //node_print(root);

    return root;
}

void build_code(Node *root, Code table[static ALPHABET], Code c) {
    uint8_t bit = 0;
    if (root != NULL) {
        //puts("if root != NULL");
        if (root->left == NULL && root->right == NULL) {
            //puts("build_code: left and right == null");
            table[root->symbol] = c;
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
        }
    }
    return;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    build_code(root, table, c);
    return;
}

void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!root->left && !root->right) {
            uint8_t buffer[] = { 'L', root->symbol };
            write_bytes(outfile, buffer, 2);
        } else {
            uint8_t buffer[] = { 'I' };
            write_bytes(outfile, buffer, 1);
        }
    }
}

Node *rebuild_tree(uint16_t bytes, uint8_t tree_dump[static bytes]) {
    Stack *s = stack_create(bytes);

    Node *n = node_create('\0', 0);
    Node *left, *right, *join, *root;
    for (uint16_t i = 0; i < bytes; ++i) {
        if (tree_dump[i] == 'L') {
            n->symbol = tree_dump[i + 1];
            stack_push(s, n);
            i++;
        }

        if (tree_dump[i] == 'I') {
            stack_pop(s, &right);
            stack_pop(s, &left);

            join = node_join(left, right);
            stack_push(s, join);
        }
    }

    stack_pop(s, &root);
    stack_delete(&s);

    return root;
}

void delete_tree(Node **root) {
    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
}
/*
int main(void) {
    return 0;
}*/
