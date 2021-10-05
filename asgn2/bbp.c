#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int terms;

//code taken from 10/4/21 lecture
//Prof. Darrell Long is the original author of this code
double pi_bbp(void) {
    int counter = 0;
    double sum = 0.0, sixteen = 1.0, k = 0, term = 1;
    while (absolute(term) > EPSILON) {
        term = (4.0 / (8.0 * k + 1.0) - 2.0 / (8 * k + 4.0) - 1.0 / (8 * k + 5.0)
                   - 1.0 / (8.0 * k + 6.0))
               * sixteen;
        sum += term;
        sixteen /= 16.0;
        k++;
        counter++;
    }
    terms = counter;
    return sum;
}

int pi_bbp_terms(void) {
    return terms;
}
