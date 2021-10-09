#include "mathlib.h"

#include <math.h> //not used in actual calculation
#include <stdio.h>
#include <stdlib.h>

static int terms; //keeps track of the numbers of terms calculated

//calculates pi using Euler's solution
//Returns the value of pi as a double type
//
//no input is allowed
double pi_euler(void) {
    double sum = 0, k = 1, term = 1, counter = 0;
    while (term > EPSILON) {
        term = 1.0 / (k * k);
        sum += term;
        k++;
        counter++;

        //if( k < 100){
        //    printf("pi_euler(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n", k, sqrt_newton(6*sum), k, absolute(sqrt_newton(6*sum) - M_PI));
        //}
    }

    terms = counter;

    return sqrt_newton(6 * sum);
}

//Handles returning the number of terms calculated
//Returns the number of terms calculated
//
//no inputs are allowed
int pi_euler_terms(void) {
    return terms;
}
