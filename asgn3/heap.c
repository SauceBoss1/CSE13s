#include "heap.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last);
static void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last);
static void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last);

//Sorts an array using the max heap sort algorithm
//Returns nothing but rather it manipulates an array that is passed in
//
//*stats: takes in a Stats struct that is used to keep track of moves and comparisons
//*A: takes in an array that will be sorted
//n: takes in the size of the array
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1, last = n; //we are using 1-based indexing rather than 0 based indexing
    build_heap(stats, A, first, last);

    for (uint32_t leaf = last; leaf > first; --leaf) {
        swap(stats, &A[first - 1],
            &A[leaf - 1]); //swap the first element and the last element in the array

        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}

//Finds the max child (or the biggest element) in the heap
//Returns either the right or the left child as an integer
//
//*stats: takes in a Stats struct that is used to keep track of moves and comparisons
//A* : takes in an array that will be manipulated
//first: takes in the first specified index
//last: takes in the last specified index
static uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    if ((right <= last)
        && (cmp(stats, A[right - 1], A[left - 1])
            > 0)) { //check to see if the right child is bigger than the left child
        return right;
    }
    return left;
}

//Fixes the heap in the algorithm
//Returns nothing but it instead manipulates the given array
//
//*stats: takes in a stats struct that keeps track of the number of moves and comparisons
//*A : takes in an array of a 32 bit integer type that will be sorted
//first: takes in the first specified index
//last: takes in the last specified index
static void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first, great = max_child(stats, A, mother, last);

    while ((mother <= floor(last / 2)) && !found) { //check if the mother is greated than the middle
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }

    return;
}

//Builds heap in heap sort
//Returns nothing but it manipulates the array instead
//
//*stats: takes in the Stats struct that keeps track of the number of moves and comparisons
//*A: takes in an uint32_t array that will be sorted
//first: takes in the first specified index as a 32 bit int
//last: takes in the last specified index as a 32 bit int
static void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > (first - 1);
         --father) { //starts in the middle and ends when we reach the beginning of the array
        fix_heap(stats, A, father, last);
    }
    return;
}
