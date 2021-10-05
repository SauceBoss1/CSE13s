#include "mathlib.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int terms = 0;

double e(void) {
    double factorial = 1, k = 1, sum = 0, term = 0;
    do {
        factorial = 1;
        for (double i = 1; i < k; ++i) {
            factorial *= 1 / i;
        }
        k++;
        sum += factorial;
        term++;
    } while (factorial > EPSILON);

    terms = term;
    return sum;
}

int e_terms(void) {
    return terms;
}
