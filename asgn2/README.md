# Assignment 2: A little slice of pi

### By Derfel Terciano

## Synopsis

This program runs a series of tests on my implemented functions for pi, e, and sqrt().

In this assignment pi was calculated in 4 different ways. I used:

1. Euler's Solution
2. Viete's Formula
3. BBP Formula
4. Madhava series

In additon, I calculated Euler's number using the Taylor Series, and I calculated the square roots of numbers using
Newton's method.

## Building the program

In the terminal,type `make` and the Makefile will build the correct executable. (NOTE: This only works if all the files have been downloaded)
Once you type `make` in the terminal, then Makefile will create all object files and the executable binary.

Once you are done with the program, you can type `make clean` in order to remove the executable and all object files.

## How to run the program

Once you have your executable, you can type `./mathlib-test -h` to view all commands line options avaliable and its usage.

Here are the command line options:
- -a : runs all thests
- -e : runs the e approximation test
- -b : runs the BBP pi tests
- -m : runs the Madhava pi test
- -r : runs Ruler's solution for pi test
- -v : runs the Viete pi test
- -n : runs newton's sqrt() approximation test
- -s : enables printing of statistics to see computed terms of each test
- -h : displays the help message

## Issues

So far there are no issues to the program.
