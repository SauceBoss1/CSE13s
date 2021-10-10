#include "mathlib.h"

#include <math.h> //used only for plotting
#include <stdio.h>
#include <stdlib.h>

static int terms; //a global var that keeps tracks of the # of terms calculated

//code taken from 10/4/21 lecture
//Prof. Darrell Long is the original author of this code
//
//
//Calculates pi using the bbp formaula
//Returns a double of the number pi
//
//no input is allowed
double pi_bbp(void) {
    int counter = 0;
    double sum = 0.0, sixteen = 1.0, k = 0, term = 1;
    while (absolute(term) > EPSILON) { //make sure our calculation is still bigger than the
        //floating point margin
        term = (4.0 / (8.0 * k + 1.0) - 2.0 / (8 * k + 4.0) - 1.0 / (8 * k + 5.0)
                   - 1.0 / (8.0 * k + 6.0))
               * sixteen;
        sum += term;
        sixteen /= 16.0; //a way of 16^-k
        k++;
        counter++;

        //this deals with printing out each term for the graph
        //printf("pi_bbp(%lf) = %16.15lf, M_PI(%lf) = %16.15lf\n", k, sum, k, absolute(M_PI - sum));
    }
    terms = counter;
    return sum;
}

//returns the number of terms calculated
//Returns the number of terms calculated in pi_bbp()
int pi_bbp_terms(void) {
    return terms;
}
