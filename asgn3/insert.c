#include "insert.h"

#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i++) {
        uint32_t j = i;
        uint32_t temp = A[i];
        move(stats, temp);

        while ((j > 0) && (cmp(stats, temp, A[j - 1]) == -1)) {
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }

        A[j] = temp;
        move(stats, temp);
    }
    return;
}
