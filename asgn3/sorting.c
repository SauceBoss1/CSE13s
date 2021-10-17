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
void help_msg(void);

//Handles all command line options for the test harness
//Returns 0 to signify success
//
//argc, **argv: allows input from command line
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
        switch (opt) { //determines which sorting algorithm to use
        case 'a':
            for (Sorts x = INSERTION; x <= QUICK; ++x) { //adds all options to the set
                s = insert_set(x, s);
            }
        case 'i': s = insert_set(INSERTION, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'e': s = insert_set(HEAP, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'n': arr_size = strtol(optarg, NULL, 10); break;
        case 'p': arr_diplay = strtol(optarg, NULL, 10); break;
        case 'r': seed = strtol(optarg, NULL, 10); break;
        case 'h':
            help_msg();
            break; //no default cases needed since if_sorting_called variable will be the default option
        }
    }

    uint32_t *A = (uint32_t *) calloc(arr_size, sizeof(uint32_t)); //initialize array

    int if_sorting_called = 0;
    for (Sorts x = INSERTION; x <= QUICK; x++) { //go through each enum and see which is in the set
        srandom(seed);

        if (member_set(x, s)) {
            if_sorting_called++; //increment if the user has called at least one sorting option
            make_array(A, arr_size);

            switch (x) { //decides which algorithm to use
            case INSERTION: insertion_sort(&stats, A, arr_size); break;
            case HEAP: heap_sort(&stats, A, arr_size); break;
            case SHELL: shell_sort(&stats, A, arr_size); break;
            case QUICK: quick_sort(&stats, A, arr_size); break;
            }

            print_stats(&stats, arr_size, names[x]);
            print_array(A, arr_size, arr_diplay);
            reset(&stats);
        }
    }

    if (if_sorting_called == 0) { //checks if the user has called a sorting option
        help_msg();
    }

    free(A);
    return 0;
}

//Randomizes an array
//Returns nothing but it manipulates a referenced array
//
//*A: pass in an array to be randomized
//n: specifies the size of the array
void make_array(uint32_t *A, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        A[i] = random() & 0x3FFFFFFF; //masked in 30 bits in hexadecimal
    }
    return;
}

//Displays the array when called
//returns nothing but it uses printf as an output
//
//*A: pass in an array to be printed
//arr_size: takes in the true size of the array
//arr_display: takes in an uint32_t type that specified how many elements to be displayed
void print_array(uint32_t *A, int arr_size, int arr_display) {
    if (arr_size < arr_display) { //set the display to the array length
        //if the user specified a bigger display output
        arr_display = arr_size;
    }

    int x = 0;
    for (int i = 0; i < arr_display; i++, x++) {
        printf("%13" PRIu32 " ", A[i]);
        if (((i + 1) % 5) == 0) { //after 5 columns print onto the next line
            printf("\n");
        }
    }

    if (x % 5 != 0) {
        printf("\n");
    }
    return;
}

//Prints the move and compares statics of the sorting algorithm
//Returns nothing but outputs to printf
//
//*s: takes the Stats struct
//arr_size: takes in the number of elements in the array
//algorithm[]: takes in the name of the algorithm as a char
void print_stats(Stats *s, uint32_t arr_size, const char algorithm[]) {
    printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", algorithm,
        arr_size, s->moves, s->compares);
    return;
}

//Prints out the help message
//Returns nothing but outputs to the print
//
//No inputs are taken in
void help_msg(void) {
    puts("SYNOPSIS");
    puts("\tA collection of comparison-based sorting algorithms.\n");
    puts("USAGE");
    puts("\t./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n");
    puts("OPTIONS");
    puts("    -h          display program help and usage.");
    puts("    -a          enable all sorts.");
    puts("    -e          enable Heap Sort.");
    puts("    -i          enable Insertion Sort.");
    puts("    -s          enable Shell Sort.");
    puts("    -q          enable Quick Sort.");
    puts("    -n length   specify number of array elements (default: 100).");
    puts("    -p elements specify numebr of elements to print (default: 100).");
    puts("    -r seed     specify random seed (default: 13371453).");

    return;
}
