#include "names.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = {
    SIDE, //0
    SIDE, //0
    RAZORBACK, //1
    TROTTER, //2
    SNOUTER, //3
    JOWLER, //4
    JOWLER, //4
};

int scores[10] = { 0 }; //initialize all the player's scores

int score_checker(int cur_player);
int points_updater(int cur_player);
int game_master(int numPlayers);

//Checks to see if a specified player has won the game.
//Returns the player's score if they have 100+ points
//Returns 0 if the specified player does not have 100+ points
//
//cur_player: an int that represents the player's number. Must be [0,9]
int score_checker(int cur_player) {
    if (scores[cur_player] >= 100) {
        return scores[cur_player];
    }
    return 0;
}

//Rolls the player's pig and updates their points to the scores array.
//Depending on the roll, a specific message get printed
//Returns 0 to signify the function was a success
//
//cur_player: an int that represents the player's number. Must be [0,9]
int points_updater(int cur_player) {
    printf("%s rolls the pig...", names[cur_player]);
    int breakLoop = 1;
    do {
        switch (pig[rand() % 7]) { //randomly roll the pig and determine where it lands
        case 1: {
            scores[cur_player] += 10;
            printf(" pig lands on back");
            break;
        }
        case 2: {
            scores[cur_player] += 10;
            printf(" pig lands upright");
            break;
        }
        case 3: {
            scores[cur_player] += 15;
            printf(" pig lands on snout");
            break;
        }
        case 4: {
            scores[cur_player] += 5;
            printf(" pig lands on ear");
            break;
        }
        default: {
            printf(" pig lands on side\n");
            breakLoop = 0; //this stops the pig from being rolled again.
            break;
        }
        }

        if (score_checker(cur_player) != 0) { //check if the current player has won
            break;
        }
    } while (breakLoop == 1);

    return 0;
}

//Oversees all game mechanics, increases player count in rotation
//and utilizes the main while loop.
//
//Returns a 0 for function success
//
//num_players: an integer that indicates how many people are playing.
//NOTE: num_players is [1,10].
int game_master(int num_players) {
    int cur_player = 0;
    while (1) {
        points_updater(cur_player); //rolls the pig and updates player's score

        if (score_checker(cur_player) != 0) { //breaks the while loop if a winner is found
            printf("\n%s wins with %d points!\n", names[cur_player], scores[cur_player]);
            break;
        }

        if (cur_player >= (num_players - 1)) { //deals with the player rotation of the game
            cur_player = 0;
        } else {
            cur_player += 1;
        }
    }

    //prints out all the scores
    //remember to remove or comment the code our later
    //
    // for (int i = 0; i <= 10; i++){
    //    printf("%d ", scores[i]);
    // }
    return 0;
}

//Calls the game_master function, asks for player #, and asks for a random seed.
//Returns 0 to indicate program success
int main(void) { // main function

    int players;
    unsigned int seed; //Must be unsigned since srandom() accepts only unsigned ints.

    printf("How many players? ");
    scanf("%d", &players);

    if ((players < 2)
        || (players > 10)) { //checks to see if the number of players is appropriatley inputted
        fprintf(stderr, "Invalid number of players. Using 2 instead. \n");
        players = 2;
    }

    printf("Random seed: ");
    scanf("%u", &seed);

    if (((unsigned) seed > UINT_MAX) || (seed < 0)) { //checks to see if the seed inputted is valid
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        seed = 2021;
    }

    srand(seed); //set the random seed

    game_master(players); //initiate and play the game

    return 0;
}
