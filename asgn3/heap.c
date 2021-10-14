#include "heap.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last);
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last);
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last);

void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1, last = n;
    build_heap(stats, A, first, last);

    for (uint32_t leaf = last; leaf > first; --leaf) {
        swap(stats, &A[first - 1], &A[leaf - 1]);

        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}

uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    if ((right <= last) && (cmp(stats, A[right - 1], A[left - 1]) > 0)) {
        return right;
    }
    return left;
}

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first, great = max_child(stats, A, mother, last);

    while ((mother <= floor(last / 2)) && !found) {
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

void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > (first - 1); --father) {
        fix_heap(stats, A, father, last);
    }
    return;
}
