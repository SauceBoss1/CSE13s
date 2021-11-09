#include "randstate.h"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    gmp_randseed_ui(state, seed);
    gmp_randinit_mt(state);
    return;
}

void randstate_clear(void) {
    gmp_randclear(state);
    return;
}
