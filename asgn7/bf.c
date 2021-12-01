#include "bf.h"
#include "salts.h"
#include "speck.h"
#include "bv.h"

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;

        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;

        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;

        bf->filter = bv_create(size);

        return bf;
    } else {
        free(bf);
        bf = NULL;
        return bf;
    }
}

void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);

        free(*bf);
        *bf = NULL;
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    if (bf && oldspeak) {
        uint32_t bv_len = bf_size(bf);

        //primary salt hash
        bv_set_bit(bf->filter,
            hash(bf->primary, oldspeak) % bv_len); //ensures hash is in range of bitvector size

        //secondary hash
        bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bv_len);

        //tertiary hash
        bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bv_len);
    }
    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    bool prim_hash, sec_hash, tert_hash;
    prim_hash = sec_hash = tert_hash = false;

    if (bf && oldspeak) {
        uint32_t bv_len = bf_size(bf);

        //primary hash
        if (bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bv_len) != 0) {
            prim_hash = true;
        }

        //secondary hash
        if (bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bv_len) != 0) {
            sec_hash = true;
        }

        //tertiary hash
        if (bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bv_len) != 0) {
            tert_hash = true;
        }

        //probe
        if (prim_hash && sec_hash && tert_hash) {
            return true;
        }
    }
    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < bf_size(bf); ++i) {
        if (bv_get_bit(bf->filter, i)) {
            counter++;
        }
    }
    return counter;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}

/*
int main(void){
    BloomFilter *bf = bf_create(16);
    bf_insert(bf, "Hello");
    bf_insert(bf, "World");
    bf_print(bf);
    
    char *word = "bruh";
    printf("Is %s in bf? %d\n", word, bf_probe(bf, word));

    bf_delete(&bf);
    return 0;
}*/
