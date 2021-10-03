#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mathlib.h"

//static double terms;

int main(void){
    long double factorial = 1;
    long double k = 1;
    long double sum = 0;
    do{
	factorial = 1;
        for (long double i = 1; i < k; ++i){
            factorial *= 1/i;
        }
	k++;
        sum += factorial;

    } while ( factorial > EPSILON);

    printf("%0.15Lf\n", sum);
    return 0;
}

