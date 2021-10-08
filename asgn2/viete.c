#include "mathlib.h"

#include <math.h> //used only for graph plotting
#include <stdio.h>
#include <stdlib.h>

static int terms;

double pi_viete(void) {
    double a = sqrt_newton(2), term = 1, result = 1, counter = 0;
    double previous_term, cur_term;

    do {
        previous_term = term;
        term = a / 2;
        cur_term = term;
        result *= term;
        a = sqrt_newton(2 + a);
        counter++;

        //printf("pi_viete(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n", counter, result, counter, absolute(M_PI - result));
    } while (absolute(previous_term - cur_term) > EPSILON);

    terms = counter;

    return 2 / result;
}

int pi_viete_factors(void) {
    return terms;
}
