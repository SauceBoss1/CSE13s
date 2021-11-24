#include "bv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_UNIT 8

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length){
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if(v){
        uint32_t bytes = length / BITS_PER_UNIT + (length % BITS_PER_UNIT ? 1 : 0);
        v->length = length;
        v->vector = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        return v; 
    } else {
        v = NULL;
        return v;
    }
}

void bv_delete(BitVector **bv){
    if ((*bv) && (*bv)->vector){
        free((*bv)->vector);
        (*bv)->vector = NULL;
    }

    if(*bv){
        free(*bv);
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv){
    return bv ? bv->length : 0;
}

bool bv_set_bit(BitVector *bv, uint32_t i){
    return bv ? bv->vector[i / BITS_PER_UNIT] |= (0x1 << i % BITS_PER_UNIT) : 0;
}

bool bv_clr_bit(BitVector *bv, uint32_t i){
    return bv ? bv->vector[i / BITS_PER_UNIT] &= ~(0x1 << i % BITS_PER_UNIT) : 0;
}

bool bv_get_bit(BitVector *bv, uint32_t i){
    return (bv->vector[i / BITS_PER_UNIT] >> i % BITS_PER_UNIT) & 0x1;
}

void bv_print(BitVector *bv){
    for (uint32_t i = 0; i < bv_length(bv); ++i){
        if ( (i) % BITS_PER_UNIT == 0 && i != 0){
            printf("\n");
        }
        printf("%"PRIu8, bv_get_bit(bv, i));
    }
    printf("\n");
}
/*
int main(void){
    BitVector *v = bv_create(16);
    printf("size: %"PRIu32"\n", bv_length(v));
    bv_set_bit(v, 3);
    bv_set_bit(v, 10);
    bv_set_bit(v, 15);
    bv_set_bit(v, 0);
    bv_print(v);
    bv_delete(&v);
    return 0;
}*/
