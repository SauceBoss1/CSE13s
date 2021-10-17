# Assignment 3: Sorting
### By Derfel Terciano

## Synopsis

This program runs a test harness that shows the results of different sorting algorithms.

In this assignment, we tested four of the following sorting algorithms:

-Insertion Sort
-Shell Sort (using Knuth's gap sequence)
-Heap Sort (specifically using Max Heap Sort)
-Recursive Quick Sort

## Building the program

Once you have all the files in the same local directory, type `make` in the terminal and the Makefile
will build the executable binary. (NOTE: it is important that the Makefile is present in the same directory
as all the other C files.)

Once you are done using the executable, type `make clean` in the terminal in order to delete all
object(.o) and executable files.

## How to run the program

Once you have created the executable, to run the program, type `./sorting` in order to begin.
You can use `./sorting -h` to print out all the command line options for the program.

Here are the command line options:

- -a : Runs all the sorting algorithms.
- -e : Enables Heap Sort.
- -i : Enables Insertion Sort.
- -s : Enables Shell Sort.
- -q : Enables Quicksort.
- -r *seed* : Set the random seed to *seed*. The **default** seed is 13371453.
- -n *size* : Set the array size to *size*. The **default** size should be 100.
- -p *elements* : Print out *elements* number of elements from the array.  The **default** number of elements to print out should be 100. 
- -h : Prints out program usage and help statments.

## Issues

There are not issues so far.
