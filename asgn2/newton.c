#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int counter = 0;

double sqrt_newton(double x) {
    double z = 0.0;
    double y = 1.0;
    int terms = 0;
    while (absolute(y - z) > EPSILON) {
        terms++;
        z = y;
        y = 0.5 * (z + x / z);
    }
    counter = terms;
    return y;
}

int sqrt_newton_iters(void) {
    return counter;
}
