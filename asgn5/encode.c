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

//prints the help message
void help_msg(void) {
    fprintf(stderr, "SYNOPSIS\n");
    fprintf(stderr, "  A Huffman encoder.\n");
    fprintf(stderr, "  Compresses a file using the Huffman coding algorithm.\n\n");
    fprintf(stderr, "USAGE\n");
    fprintf(stderr, "  ./encode [-h] [-i infile] [-o outfile]\n\n");
    fprintf(stderr, "OPTIONS\n");
    fprintf(stderr, "  -h             Program usage and help.\n");
    fprintf(stderr, "  -v             Print compression statistics.\n");
    fprintf(stderr, "  -i infile      Input file to compress.\n");
    fprintf(stderr, "  -o outfile     Output of compressed data.\n");
}

//MAIN
int main(int argc, char **argv) {
    ////////////////////////////
    //COMMAND LINE HANDLING

    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    bool verbose = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            help_msg();
            exit(1);
            break;
        case 'i':
            infile = open(optarg, O_RDONLY);

            if (infile < 0) {
                fprintf(stderr, "Error Reading File!\n");
                exit(1);
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT);

            if (outfile < 0) {
                fprintf(stderr, "Error Writing File!\n");
                exit(1);
            }
            break;

        case 'v': verbose = true; break;
        default: infile = STDIN_FILENO; outfile = STDOUT_FILENO;
        }
    }
    ////////////////////////////

    //Inspired by eric's pseudocode
    uint64_t hist[ALPHABET] = { 0 };
    uint32_t unique_symbols = 0;
    hist[0]++, hist[ALPHABET - 1]++;

    //create a histogram
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

    //build the huffman tree
    Node *root = build_tree(hist);

    //Find the codes for the tree
    Code table[ALPHABET] = { 0 };
    build_codes(root, table);

    //set file permissions
    struct stat buffer;
    fstat(infile, &buffer);
    fchmod(outfile, buffer.st_mode);

    //construct and output header
    Header h;
    h.magic = MAGIC;
    h.permissions = buffer.st_mode;
    h.tree_size = (3 * (unique_symbols + 2)) - 1;
    h.file_size = buffer.st_size;
    write_bytes(outfile, (uint8_t *) &h, sizeof(h));

    //write the dumped tree
    dump_tree(outfile, root);

    //emit the Huffman code
    lseek(infile, 0, SEEK_SET);
    while ((bytes_curr_read = read_bytes(infile, buff, BLOCK)) > 0) {
        for (int i = 0; i < bytes_curr_read; ++i) {
            write_code(outfile, &table[buff[i]]);
        }
    }
    flush_codes(outfile); //make sure any extra bits are flushed

    if (verbose) {
        fprintf(stderr, "Uncompressed size: %" PRIu64 "\n", h.file_size);
        fprintf(stderr, "Compressed size: %" PRIu64 "\n", bytes_written);
        double space_saving = 100 * (1 - ((double) bytes_written / (double) h.file_size));
        fprintf(stderr, "Space Saving: %.2lf%%\n", space_saving);
    }

    ///////////////////
    //EXIT PROCEDURES

    delete_tree(&root);

    close(infile);
    close(outfile);
    return 0;
}
