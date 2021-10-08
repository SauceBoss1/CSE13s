#include "mathlib.h"

#include <math.h> //NOTE: this library was not used in any calculations
          //This is only here to help me graph the terms

#include <stdio.h>
#include <stdlib.h>

static int terms;

double pi_madhava(void) {
    double sum = 0;
    double k = 0;
    double term = 1;
    while (absolute(term) > EPSILON) {

        double power = 1;

        for (int i = 0; i < k; i++) {
            power *= -3;
        }

        double numerator = 1 / power;
        double denominator = (2 * k) + 1;
        term = (numerator / denominator);
        sum += term;

        //printf("pi_madhava(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n", k, term, k, absolute(M_PI - term));

        k++;
    }

    terms = k;
    return sqrt_newton(12) * sum;
}

int pi_madhava_terms(void) {
    return terms;
}
