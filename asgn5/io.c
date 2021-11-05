#include "io.h"
#include "code.h"
#include "defines.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//NOTE: code was inspired from Christian
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    if (nbytes == 0) {
        return 0;
    }

    int bytes_read = 0;
    int bytes_currently_read = -1;

    while ((bytes_currently_read = read(infile, buf + bytes_read, nbytes - bytes_read)) > 0) {
        //printf("bytes currently read: %d\n", bytes_currently_read);
        bytes_read += bytes_currently_read;
        if (bytes_read == 0) {
            break;
        }
    }
    return bytes_read;
}

//NOTE: code was inspired from Christian
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    if (nbytes == 0) {
        return 0;
    }

    int bytes_written = 0;
    int bytes_currently_written = 0;

    while ((bytes_currently_written = write(outfile, buf + bytes_written, nbytes)) > 0) {
        //printf("bytes currently writte: %d\n", bytes_currently_written);
        bytes_written += bytes_currently_written;
        if (bytes_written == nbytes || bytes_currently_written == 0) {
            break;
        }
    }
    return bytes_written;
}

/////////////////////////////////////////////////////////////////////////
//Dealing with codes below

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

        //Return a bit out of buffer
        *bit = (buffer[index / 8] >> index % 8); //<= TODO
        index += 1;

        if (index == BLOCK * 8) {
            index = 0;
        }
    }

    return index != end;
}
/////////////////////////////////////////////////////////////////////
//write code & flush code buffer and index below

static uint8_t buffer[BLOCK];
static int index = 0; //tracks position of buffer

void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); ++i) {
        uint8_t bit = code_get_bit(c, i);

        if (bit == 1) {
            buffer[index / 8] |= (1 << index % 8);
            //code_set_bit(c, index);
        } else {
            buffer[index / 8] &= ~(1 << index % 8);
            //code_clear_bit(c, index);
        }
        index++;

        if (index >= BLOCK * 8) {
            flush_codes(outfile);
        }
    }
}

void flush_codes(int outfile) { //would this use write bytes?
    int bytes_to_write = (index % 8) == 0 ? (index / 8) : (index / 8) + 1;
    //suggested by eric
    write_bytes(outfile, buffer, bytes_to_write);
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
