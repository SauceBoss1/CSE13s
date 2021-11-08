#include "io.h"
#include "code.h"
#include "defines.h"

#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

//read nbytes of data and store it into a buffer
//returns number of bytes read
//infile: the input file
//buf: buffer to store data in
//nbytes: number of bytes to read
//
//NOTE: code was inspired from Christian
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    if (nbytes == 0) {
        return 0;
    }

    int total_bytes_read = 0;
    int bytes_currently_read = -1;

    while ((bytes_currently_read = read(infile, buf + total_bytes_read, nbytes - total_bytes_read))
           > 0) {
        total_bytes_read += bytes_currently_read;
        if (total_bytes_read == nbytes) {
            break;
        }
    }

    bytes_read += total_bytes_read; //used for stats
    return total_bytes_read;
}

//Same as read_bytes but we write to a file instead
//NOTE: code was inspired from Christian
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    if (nbytes == 0) {
        return 0;
    }

    int total_bytes_written = 0;
    int bytes_currently_written = 0;

    while ((bytes_currently_written
               = write(outfile, buf + total_bytes_written, nbytes - total_bytes_written))
           > 0) {
        total_bytes_written += bytes_currently_written;
        if (total_bytes_written == nbytes || bytes_currently_written == 0) {
            break;
        }
    }
    bytes_written += total_bytes_written; //used for stats
    return total_bytes_written;
}

/////////////////////////////////////////////////////////////////////////
//Dealing with codes below

//"returns" each bit in the huffman code
//infile: input file
//bit: the bit to return
//psuedocode was provided by eugene
bool read_bit(int infile, uint8_t *bit) {
    static uint8_t buffer[BLOCK];
    static int index = 0; //track index of bit
    static int end = -1; //track index

    if (index == 0) {
        int bytes = read_bytes(infile, buffer, BLOCK);
        if (bytes < BLOCK) {
            //set the end
            //End is marked as 1 after the last valid bit
            end = (bytes * 8) + 1;
        }
    }

    //Return a bit out of buffer
    *bit = (buffer[index / 8] >> index % 8) & 0x1; //<= TODO
    index++;

    if (index == BLOCK * 8) { //reset index if we pass
        index = 0;
    }

    return index != end;
}
/////////////////////////////////////////////////////////////////////
//write code & flush code buffer and index below

static uint8_t buffer[BLOCK]; //stores the code in this buffer
static int buf_index = 0; //tracks position of buffer

//Write the huffman codes to the outfile
//outfile: output to write to
//c: the code to write
//NOTE: pseudo code was provided by Eugene
void write_code(int outfile, Code *c) {

    for (uint32_t i = 0; i < code_size(c); ++i) {
        uint8_t bit = code_get_bit(c, i);
        if (bit == 1) {
            buffer[buf_index / 8] |= (1 << buf_index % 8);
        } else {
            buffer[buf_index / 8] &= ~(0 << buf_index % 8);
        }
        buf_index++;

        if (buf_index == BLOCK * 8) {
            flush_codes(outfile);
            buf_index = 0;
        }
    }
    return;
}

//Flushes and left over bits to the output
//outfile: output file
//NOTE: Pseudocode provided by Eric (tutor)
void flush_codes(int outfile) {
    int bytes_to_write = 0;
    //this determines how many left over bytes to write
    bytes_to_write = (buf_index % 8) == 0 ? (buf_index / 8) : (buf_index / 8) + 1;
    write_bytes(outfile, buffer, bytes_to_write);
    return;
}

///////////////////////////////////////////////////////////////////
//Some example usage below
/*
int main(void) {
    uint8_t bytes;
    int bytes_read = read_bytes(STDIN_FILENO, &bytes, BLOCK);
    write_bytes(STDOUT_FILENO, &bytes, bytes_read);
    return 0;
}*/
