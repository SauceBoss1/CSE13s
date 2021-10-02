# Assignment 1: Pass the Pig
### By Derfel Terciano

## Overview

This program plays Pass the Pig for you. You enter the number of players playing (you can play from 2 to 10 people inclusive) and a valid random seed (must be an unsigned integer).

The program then starts with player 0 and pseudorandomly rolls the "pig." If the pig lands on its side, then the player earns 0 points and their turn ends. If the pig lands on its back or upright, then player earns 10 points. If the pig lands on its snout then the player earns 15 points. Lastly, if the pig lands on its ears then the player earns 5 points. Once the player's pig lands on its side, then their turn ends and the pig is passed to the next player in the circle.

The game continues until someone reaches 100 points.

## Building the program

In the terminal make sure you have the Makefile downloaded in the same directory. When you have the Makefile in the same directory, then just type the "make" command and all of the executables will be built and compiled.

## How to run the program

Once you have built the program, type in "./pig" in the terminal and then the program will execute. Once executed, the program will ask you to input the number of players you want to be in the game and it will ask you to input a valid unsigned random seed. Once those two inputs have been satisfied, then the game will begin.

## Issues

So far, the only issue is when a mix of strings and numbers are iputted together. An example of this is "122asdf." When entered, the program would only recognize the "122" as the seed but all the other characters are ignored. This concept also applies when the user is prompted to enter a player number.
