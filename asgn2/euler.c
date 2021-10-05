#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int terms;

double pi_euler(void) {
    double sum = 0, k = 1, term = 1, counter = 0;
    while (term > EPSILON) {
        term = 1.0 / (k * k);
        sum += term;
        k++;
        counter++;
    }

    terms = counter;

    return sqrt_newton(6 * sum);
}

int pi_euler_terms(void) {
    return terms;
}
