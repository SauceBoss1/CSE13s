#include "bv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_UNIT 8

//NOTE: ALL THIS COMES FROM THE CODE COMMENTS REPO

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

//Constructor for the bitvector
//Returns the pointer to the newly create bit vector
//
//length: the length of the desried bit vector
//
//NOTE: code provided by Prof. Long
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) {
        uint32_t bytes = length / BITS_PER_UNIT + (length % BITS_PER_UNIT ? 1 : 0);
        v->length = length;
        v->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        return v;
    } else {
        v = NULL;
        return v;
    }
}

//Deletes a bivector
//Return void
//
//bv: bitvector to delete
//NOTE: code provided by Prof. Long
void bv_delete(BitVector **bv) {
    if ((*bv) && (*bv)->vector) {
        free((*bv)->vector);
        (*bv)->vector = NULL;
    }

    if (*bv) {
        free(*bv);
        *bv = NULL;
    }
    return;
}

//Returns the length of the bitvector as a uint32_t
//
//bv: bit vector
//NOTE: code provided by Prof. Long
uint32_t bv_length(BitVector *bv) {
    return bv ? bv->length : 0;
}

//Sets a bit to 1 at index i
//Returns false if i is out of range
//
//bv: the bit vector to set
//i: index of bit to set to 1
//
//NOTE: code provided by Prof. Long
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i > bv_length(bv)) {
        return false;
    }
    return bv ? bv->vector[i / BITS_PER_UNIT] |= (0x1 << i % BITS_PER_UNIT) : 0;
}

//Clears a bit at index i
//Returns false if the bit is out of range
//
//bv: bit vector
//i: index
//NOTE: code provided by Prof. Long
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i > bv_length(bv)) {
        return false;
    }
    bv->vector[i / BITS_PER_UNIT] &= ~(0x1 << i % BITS_PER_UNIT);
    return true;
}

//Gets the bit at index i
//Returns false if i is out of range
//
//bv: bit vector
//i: index
//NOTE: code provided by Prof. Long
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i > bv_length(bv)) {
        return false;
    }
    return (bv->vector[i / BITS_PER_UNIT] >> i % BITS_PER_UNIT) & 0x1;
}

//Debug function that prints out the bit vector
//Returns void
//
//bv: bitvector to print
void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv_length(bv); ++i) {
        if ((i) % BITS_PER_UNIT == 0 && i != 0) {
            printf("\n");
        }
        printf("%" PRIu8, bv_get_bit(bv, i));
    }
    printf("\n");
}
