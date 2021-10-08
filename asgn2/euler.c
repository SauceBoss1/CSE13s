#include "mathlib.h"

#include <math.h> //not used in actual calculation
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

        //if( k < 100){
        //    printf("pi_euler(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n", k, term, k, absolute(sum - M_PI));
        //}
    }

    terms = counter;

    return sqrt_newton(6 * sum);
}

int pi_euler_terms(void) {
    return terms;
}
