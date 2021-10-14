#include "shell.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = (uint32_t)(log(3 + 2 * n) / log(3)); i > 0; --i) { //gap for loop

        uint32_t gap = (uint32_t) floor((pow(3, i) - 1) / 2);

        for (uint32_t i = gap; i < n; ++i) {

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
