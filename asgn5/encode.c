#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/stat.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {
    ////////////////////////////
    //COMMAND LINE HANDLING

    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    //bool verbose = false;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = open(optarg, O_RDONLY);

            if (infile < 0) {
                fprintf(stderr, "Error Reading File!\n");
                exit(1);
            }
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);

            if (outfile < 0) {
                fprintf(stderr, "Error Writing File!\n");
                exit(1);
            }
        }
    }
    ////////////////////////////

    //Inspired by eric's pseudocode
    uint64_t hist[ALPHABET] = { 0 };
    uint32_t unique_symbols = 0;
    hist[0]++, hist[ALPHABET - 1]++;

    uint8_t buff[BLOCK];
    int bytes_curr_read;
    while ((bytes_curr_read = read_bytes(infile, buff, BLOCK)) > 0) {
        for (int i = 0; i < bytes_curr_read; ++i) {
            if (hist[buff[i]] == 0) {
                unique_symbols++;
            }

            hist[buff[i]]++;
        }
    }

    Node *root = build_tree(hist);
    //node_print(root); //<= TODO REMOVE

    Code table[ALPHABET];
    build_codes(root, table);

    struct stat buffer;
    fstat(infile, &buffer);

    Header h;
    h.magic = MAGIC;
    h.permissions = buffer.st_mode;
    h.tree_size = (3 * unique_symbols) - 1;
    h.file_size = buffer.st_size;

    write_bytes(outfile, (uint8_t *) &h, sizeof(h));

    dump_tree(outfile, root);

    lseek(infile, 0, SEEK_SET);
    while ((bytes_curr_read = read_bytes(infile, buff, BLOCK)) > 0) {
        for (int i = 0; i < bytes_curr_read; ++i) {
            write_code(outfile, &table[buff[i]]);
        }
    }
    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
