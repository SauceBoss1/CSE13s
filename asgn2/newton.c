#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int counter = 0; //keeps track of the number of terms calculated

//NOTE: Psuedo code for this was given to us by Prof. Long
//Calculated the square root of a number using Newton's method
//Returns the the square root of a number as a double
//
//x: a double value that used to specifiy what number to use the method on
double sqrt_newton(double x) {
    double z = 0.0;
    double y = 1.0;
    int terms = 0;
    while (absolute(y - z) > EPSILON) { //make sure the calculation is bigger than EPSILON
        terms++;
        z = y;
        y = 0.5
            * (z + x / z); //this line of code was given to us by Prof. Long in the assignment pdf
    }
    counter = terms;
    return y;
}

//Handles the number of terms calculated
//Returns  the number of terms as an int
//
//No inputs are allowed
int sqrt_newton_iters(void) {
    return counter;
}
