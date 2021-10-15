#include "insert.h"

#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//Sorts an inputted arry with an insertion sort algorithm
//Returns void but it edits a pointer array instead
//
//*stats: takes in a Stats struct that is used to keep track of moves and comparisons form algorithm
//*A: take in an array of a 32 bit integer type
//n: takes in the size of the array
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {

    for (uint32_t i = 1; i < n; i++) { //iterates through each element
        uint32_t j = i;
        uint32_t temp = A[i]; //temporarily keeps track of the current element
        move(stats, temp);

        while ((j > 0)
               && (cmp(stats, temp, A[j - 1])
                   == -1)) { //compares the A[i] element to the previous element
            A[j] = move(stats, A[j - 1]); //keep moving the element to the left
            j -= 1;
        }

        A[j] = temp;
        move(stats, temp);
    }
    return;
}
