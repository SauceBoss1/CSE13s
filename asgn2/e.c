#include "mathlib.h"

#include <math.h> //used only for plotting graph
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int terms = 0; //keeps tracks of how many terms were calculated

//calculates Euler's number
//returns the value of e as a double
//
//no inputs are allowed
double e(void) {
    double factorial = 1, k = 1, sum = 0, term = 0;
    do {
        factorial = 1;
        for (double i = 1; i < k; ++i) { //deals with calculating the factorial
            //without the use of a function or recursion
            factorial *= 1 / i;
        }
        k++;
        sum += factorial;
        term++; //keeps track of the number of iterations the loop has gone through

        //printf("e(%lf) = %16.15lf, M_E(%lf) = %16.15lf\n", k, sum, k, absolute(M_E - sum));
    } while (factorial > EPSILON); //make sure our calculation is still bigger than epsilon

    terms = term;
    return sum;
}

//Handles the number of terms calculated
//Returns the number of terms calculated as an int
//
//no input is allowed
int e_terms(void) {
    return terms;
}
