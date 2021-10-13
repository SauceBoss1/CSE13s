#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h" //given to us by Prof. Long
#include "shell.h"
#include "stats.h" //given to us by Prof. Long

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //this library is used for command line args

#define OPTIONS       "aeisqhr:n:p:"
#define SEED          13371453
#define ARRAY_SIZE    100
#define ELEMENTS      100
#define ARRAY_DISPLAY 100

typedef enum { INSERTION, HEAP, SHELL, QUICK } Sorts; //suggested by Eugene
const char *names[]
    = { "Insertion Sort", "Heap Sort", "Shell Sort", "Quick Sort" }; //suggested by Eugene

void make_array(uint32_t *A, uint32_t n);
void print_array(uint32_t *A, int arr_size, int arr_display);
void print_stats(Stats *s, uint32_t arr_size, const char algorithm[]);

int main(int argc, char **argv) {
    Set s = empty_set();
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    int opt = 0;
    uint32_t arr_size = ARRAY_SIZE;
    uint32_t seed = SEED;
    uint32_t arr_diplay = ARRAY_DISPLAY;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': s = insert_set(INSERTION, s); break;
        case 'n': arr_size = strtol(optarg, NULL, 10); break;
        case 'p': arr_diplay = strtol(optarg, NULL, 10); break;
        case 'r': seed = strtol(optarg, NULL, 10); break;
        }
    }

    srandom(seed);
    uint32_t *A = (uint32_t *) calloc(arr_size, sizeof(uint32_t)); //initialize array

    for (Sorts x = INSERTION; x < QUICK; x++) { //go through each enum and see which is in the set
        if (member_set(x, s)) {
            make_array(A, arr_size);

            switch (x) { //decides which algorithm to use
            case INSERTION: insertion_sort(&stats, A, arr_size); break;
            case HEAP: break;
            case SHELL: break;
            case QUICK: break;
            }

            print_stats(&stats, arr_size, names[x]);
            print_array(A, arr_size, arr_diplay);
            reset(&stats);
        }
    }

    free(A);
    return 0;
}

void make_array(uint32_t *A, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        A[i] = random() & 0x3FFFFFFF; //masked in 30 bits in hexadecimal
    }
    return;
}

void print_array(uint32_t *A, int arr_size, int arr_display) {
    if (arr_size < arr_display) { //set the display to the array length
        //if the user specified a bigger display output
        arr_display = arr_size;
    }

    for (int i = 0; i < arr_display; i++) {
        printf("%13" PRIu32 " ", A[i]);
        if (((i + 1) % 5) == 0) {
            printf("\n");
        }
    }
    return;
}

void print_stats(Stats *s, uint32_t arr_size, const char algorithm[]) {
    printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", algorithm,
        arr_size, s->moves, s->compares);
    return;
}
