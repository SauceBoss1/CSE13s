#include "shell.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Sorts an array using shell wort and Knuth's gap sequence
//Returns nothing but instead manipulates an array pointer
//
//*stats: a pointer to a Stats struct that keeps track of moves and comparisons
//*A: takes in an array of a 32 bit integer type
//*n: takes in the size of the array
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = (uint32_t)(log(3 + 2 * n) / log(3)); i > 0;
         --i) { //main for loop for the gap sequence

        uint32_t gap
            = (uint32_t) floor((pow(3, i) - 1) / 2); //calculates the gap needed for shell sort

        for (uint32_t i = gap; i < n;
             ++i) { //uses the same algorithm as shell sort except using gaps

            uint32_t j = i, temp = move(stats, A[i]);
            while ((j >= gap) && (cmp(stats, temp, A[j - gap]) == -1)) {

                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }

            A[j] = move(stats, temp);
        }
    }
    return;
}
