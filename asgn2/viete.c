#include "mathlib.h"

#include <math.h> //used only for graph plotting
#include <stdio.h>
#include <stdlib.h>

static int terms; //keeps track of the number of terms calculated

//Calculates the value of pi
//Returns the value of pi as a double
//
//No inputs are allowed
double pi_viete(void) {
    double a = sqrt_newton(2), term = 1, result = 1, counter = 0; // our inital 'a' must be sqrt(2)
    double previous_term, cur_term;

    do {
        previous_term = term; //keep track of the previous term
        term = a / 2;
        cur_term = term; //keep track of the newly calculated term
        result *= term;
        a = sqrt_newton(2 + a); //change the value of a while using the previous value of a
        counter++;

        //printf("pi_viete(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n", counter, 2/result, counter, absolute(M_PI - (2/result)));
    } while (absolute(previous_term - cur_term)
             > EPSILON); // since the formula only gets bigger we must take
        // difference between the current calculated term and the
        // previous term and compare that to epsilon

    terms = counter;

    return 2 / result;
}

//Handles the number of terms calculated
//Returns the number of terms calculated as an int
//
//No input is allowed
int pi_viete_factors(void) {
    return terms;
}
