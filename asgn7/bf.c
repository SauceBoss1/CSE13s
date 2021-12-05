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

//Initializes the bloom filter
//Returns the created bloom filter
//
//size: the size of the bloom filter
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        //set primary salt
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;

        //set secondary salt
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;

        //set tertiary salt
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;

        //create the bit vector
        bf->filter = bv_create(size);

        return bf;
    } else {
        free(bf);
        bf = NULL;
        return bf;
    }
}

//Deletes the inputted bloomfilter
//Returns void
//
//bf: the bloom filter to delete
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);

        free(*bf);
        *bf = NULL;
    }
    return;
}

//Returns the size of the bloom filter as a uint32_t
//
//bf: bloom filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

//Inserts oldspeak into the bloom filter
//Returns void
//
//bf: the bloom filter to update
//oldspeak: the oldspeak to insert into the bloom filter
//
//NOTE: I used the bloom filter lecture in order to normalize hash values
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

//Probes the bloom filter to check if the oldspeak may be in the filter
//Returns true if the oldspeak is maybe in the filter
//Returns false if the oldspeak is not in the filter
//
//bf: the bloomfilter to check
//oldspeak: the word to check if its in the bloom filter
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

//Counts how many bits are set to 1 in the bloomfilter
//Returns a uint32_t type
//
//bf: the bloom filter to check
uint32_t bf_count(BloomFilter *bf) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < bf_size(bf); ++i) {
        if (bv_get_bit(bf->filter, i)) {
            counter++;
        }
    }
    return counter;
}

//Debug function that prints underlying bitvector
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
