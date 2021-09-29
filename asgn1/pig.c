#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "names.h"

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER} Position;
const Position pig[7] = {
    SIDE, //0
    SIDE, //0
    RAZORBACK, //1
    TROTTER, //2
    SNOUTER, //3
    JOWLER, //4
    JOWLER, //4
};


int scores[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int score_checker(int cur_player);
int score_checkAll(void);
int points_updater(int cur_player);
int game_master(int numPlayers);

int score_checker(int cur_player){
    if (scores[cur_player] >= 100) {
        printf("\n%s has won with %d!\n", names[cur_player], scores[cur_player]);
        return scores[cur_player];
    }
    return 0;
}

int points_updater(int cur_player){
    printf("%s rolls the pig... ", names[cur_player]);
    while (1){
        int pigPos = (random() % 7);
        if (pig[pigPos] == 1){
            scores[cur_player] += 10;
            printf("pig lands on back ");
        } else if (pig[pigPos] == 2){
	    scores[cur_player] += 10;
            printf("pig lands upright ");
        } else if (pig[pigPos] == 3){
            scores[cur_player] += 15;
            printf("pig lands on snout ");
        } else if(pig[pigPos] == 4){
            scores[cur_player] += 5;
            printf("pig lands on ear ");
        } else{
            printf("pig lands on its side\n");
            break;
        }
        if (score_checker(cur_player) != 0){
            break;
        } 
    }
    return 0;
}

int score_checkAll (void){
    for(int i = 0; i <=10; i++){
        if (scores[i] >= 100){
            return scores[i];
        }
    }
    return 0;
}

int game_master(int numPlayers){
    int cur_player = 0;
    while (score_checkAll() == 0){
        points_updater(cur_player);
        if (cur_player >= (numPlayers-1)){
            cur_player = 0;
        } else {
            cur_player += 1;
        }
    }

    //prints out all the scores
    //remember to remove this later on
    for (int i = 0; i <= 10; i++){
        printf("%d ", scores[i]);
    }
    return 0;
}

int main (void){ // main function

    int players;
    int seed;

    printf("How many players? ");
    scanf("%d", &players);

    if ((players < 2) || (players > 10)){
        fprintf(stderr, "Invalid number of players. Using 2 instead. \n");
        players = 2;
    }

    printf("Random seed: ");
    scanf("%d", &seed);

    srandom(seed);

    game_master(players);

    return 0;
}   
