#include "quick.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi);
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi);

//Sorts an inputted array using quick sort
//Returns nothing but it manipulate a referenced array instead
//
//*stats: takes in a Stats struct that keeps track of moves and compares used in the algorithm
//*A: takes in a referenced array that is to be manipulated and sorted
//n: takes in the size of the manipulated array
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
    return;
}

//Creates a partition for the quick sort algorithm
//Returns a 32 bit integer that is used for determining the pivot element
//
//*stats: takes in the Stats struct that is used ot keep track of moves and compares
//*A : takes in an array of uint32_t that will be manipulated and sorted
//lo : takes in the lowest specified index
//hi : takes in the highest specified index
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;

    for (uint32_t j = lo; j < hi; ++j) {
        if (cmp(stats, A[j - 1], A[hi - 1])
            < 0) { //this is going to choose a pivot point when the current element
            //is less than the biggest element
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }

    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

//Handles the recursive aspect of the quick sort
//Returns nothing but it manipulates the referenced array instead
//
//*stats : takes in a Stats struct that keeps track of the moves and compares
//*A : takes in a referenced array that will be manipulated and sorted
//lo : takes in the specified first index as a uint32_t
//hi : takes in the specified second index as a uint32_t
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        uint32_t p = partition(stats, A, lo, hi); //finds the pivot element
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
    return;
}
