#include "mathlib.h"

#include <math.h> //NOTE: this library was not used in any calculations
//This is only here to help me graph the terms

#include <stdio.h>
#include <stdlib.h>

static int terms; //keeps track of the number of terms calulated

//Calculates the value of pi
//Returns the number of pi as a double
//
//No inputs are allowed
double pi_madhava(void) {
    double sum = 0;
    double k = 0;
    double term = 1;
    while (absolute(term) > EPSILON) { //make sure the calculation is bigger than epsilon

        double power = 1;

        for (int i = 0; i < k; i++) { //this deals with the -3 exponent
            power *= -3;
        }

        double numerator = 1 / power;
        double denominator = (2 * k) + 1;
        term = (numerator / denominator);
        sum += term;

        //printf("pi_madhava(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n"
        //, k, (sqrt_newton(12)*sum), k, absolute(M_PI - (sqrt_newton(12)*sum)));

        k++;
    }

    terms = k;
    return sqrt_newton(12) * sum; //we must multiply sqrt(12) to the sum
}

//Handles the number of terms calcululated
//Returns the number of terms calculated as an int
//
//No inputs are allowed
int pi_madhava_terms(void) {
    return terms;
}
