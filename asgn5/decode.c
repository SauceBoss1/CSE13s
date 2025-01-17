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

void help_msg(void) {
    fprintf(stderr, "SYNOPSIS\n");
    fprintf(stderr, "  A Huffman decoder.\n");
    fprintf(stderr, "  Uncompresses a file using the Huffman coding algorithm.\n\n");
    fprintf(stderr, "USAGE\n");
    fprintf(stderr, "  ./decode [-h] [-i infile] [-o outfile]\n\n");
    fprintf(stderr, "OPTIONS\n");
    fprintf(stderr, "  -h             Program usage and help.\n");
    fprintf(stderr, "  -v             Print compression statistics.\n");
    fprintf(stderr, "  -i infile      Input file to decompress.\n");
    fprintf(stderr, "  -o outfile     Output of decompressed data.\n");
}

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
        }
    }
    ////////////////////////////

    //NOTE: This implementation was taken very literally from the assignment doc
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));

    //verify magic number
    if (h.magic != MAGIC) {
        fprintf(stderr, "Incorrect magic number!\n");
        exit(1);
    }

    //match file perms
    struct stat inbuffer;
    fstat(infile, &inbuffer);
    fchmod(outfile, h.permissions);

    //dump the tree
    uint8_t tree_dump[h.tree_size];
    read_bytes(infile, tree_dump, h.tree_size);
    Node *dump_node = rebuild_tree(h.tree_size, tree_dump);

    //going through the reconstructed tree
    uint64_t bytes_wrote = 0; //keeps track of the bytes that was written
    uint8_t bit = 0;
    uint8_t output_buff[BLOCK]; //this is the buffer used for the final output
    uint32_t buff_index = 0; //index used for output buffer
    Node *root = dump_node; //we need to set our dump_tree to another pointer
        //so that we can iterativley traverse to the left or right node
    while ((bytes_wrote < h.file_size) && read_bit(infile, &bit)) {
        if (bit == 1) {
            root = root->right; //if our bit is 1, then traverse to the left node
        } else {
            root = root->left; //else traverse to the right node
        }

        if (root->left == NULL && root->right == NULL) { //we will use this to find the leaf
            output_buff[buff_index++] = root->symbol;
            root = dump_node; //go back to the top of the tree
            bytes_wrote++;

            if (buff_index == BLOCK) { //reset or buffer if it is full
                write_bytes(outfile, output_buff, BLOCK);
                buff_index = 0;
            }
        }
    }
    //equivalent of using flush_codes
    write_bytes(outfile, output_buff, buff_index); //write out the remaining bytes

    ////////////////////////
    //exiting procedures
    delete_tree(&dump_node);
    if (verbose) {
        fprintf(stderr, "Compressed file size: %" PRIu64 "\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %" PRIu64 "\n", bytes_written);
        double space_saving = 100 * (1 - ((double) bytes_read / (double) bytes_written));
        fprintf(stderr, "Space Saving: %.2lf%% \n", space_saving);
    }
    close(infile);
    close(outfile);
    return 0;
}
