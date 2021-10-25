# Assginment 4: The Perambulations of Denver Long
### By Derfel Terciano

## Synopisis

This program finds the shortest hamiltonian path between given cities or verticies. 

The program represents a person traveling from place to place and our objective is to find the most optimal path
for the person to do a round trip. This program can be very useful since it tells us what is the most efficent way
to drive from city to city and then back to our starting destination.

## Building the program

Once all the files are in the local directory, just type `make` in the terminal and the executable will be built. 

(NOTE: It is important that the Makefile is in the same directory as the other files as well.)

Once you are finished with the program, type `make clean` in the terminal then the exectuable and all the other obejct files will be deleted.

## How to run the program

Once you have made the executable, you can then type `./tsp -h` to see all the run the program.

Since this program takes in files as the input, you can use `stdin` and `stdout` to input and output your files. Below is an example of how the
program can be used:

- `./tsp -arg1 -arg2 <infile >outfile`

Here are the avaliable command line options at the user's disposal:

- -h:           Displays the help message.
- -u:           Sets the program to use an undirected graph. (A directed graph is used by default.)
- -v:           Prints all verbose hamiltonian paths found
- -i: infile    inputs in a user's graph file. (stdin is used by default)
- -o: outfile   Outputs the program's results to a file. (stdout is used by default)
