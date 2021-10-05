#include "mathlib.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int terms;

double e(void) {
    double factorial = 1, k = 1, sum = 0;
    do {
        for (double i = 1; i < k; ++i) {
            factorial *= 1 / i;
        }
        k++;
        sum += factorial;
        terms++;
    } while (factorial > EPSILON);

    return sum;
}

int e_terms(void) {
    return terms;
}
