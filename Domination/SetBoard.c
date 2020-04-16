//
// Created by Draum on 07/04/2020.
//


#include "SetBoard.h"
//******************************************
//****FUNCTIONS TO INITIALISE THE GAME*****
//*****************************************

//header: prints the name of the game
void header() {

    printf(" _____                  _             _   _             \n");
    printf("|  __ \\                (_)           | | (_)            \n");
    printf("| |  | | ___  _ __ ___  _ _ __   __ _| |_ _  ___  _ __  \n");
    printf("| |  | |/ _ \\| '_ ` _ \\| | '_ \\ / _` | __| |/ _ \\| '_ \\ \n");
    printf("| |__| | (_) | | | | | | | | | | (_| | |_| | (_) | | | |\n");
    printf("|_____/ \\___/|_| |_| |_|_|_| |_|\\__,_|\\__|_|\\___/|_| |_|\n");
    printf("\n\n");
}

//Initial_Board: Intialice the players and the board
void Initial_Board(Player *P1, Player *P2) {
    //Set values for player 1
    P1->color = RED;
    P1->number = 1;
    P1->c_color = "RED";
    P1->suply = 0;
    P1->captured = 0;
    //Set values for player 2
    P2->color = GREEN;
    P2->number = 2;
    P2->c_color = "GREEN";
    P2->suply = 0;
    P2->captured = 0;

    int i, j;
    //Set all linked list nodes to null
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            Board[i][j].stack = NULL;
        }
    }

    ////Set the Red Cells
    push_front(&Board[1][1].stack, RED);
    push_front(&Board[1][2].stack, RED);
    push_front(&Board[1][5].stack, RED);
    push_front(&Board[1][6].stack, RED);
    push_front(&Board[2][3].stack, RED);
    push_front(&Board[2][4].stack, RED);
    push_front(&Board[3][1].stack, RED);
    push_front(&Board[3][2].stack, RED);
    push_front(&Board[3][5].stack, RED);
    push_front(&Board[3][6].stack, RED);
    push_front(&Board[4][3].stack, RED);
    push_front(&Board[4][4].stack, RED);
    push_front(&Board[5][1].stack, RED);
    push_front(&Board[5][2].stack, RED);
    push_front(&Board[5][5].stack, RED);
    push_front(&Board[5][6].stack, RED);
    push_front(&Board[6][3].stack, RED);
    push_front(&Board[6][4].stack, RED);


    //Set the Green Cells
    push_front(&Board[1][3].stack, GREEN);
    push_front(&Board[1][4].stack, GREEN);
    push_front(&Board[2][1].stack, GREEN);
    push_front(&Board[2][2].stack, GREEN);
    push_front(&Board[2][5].stack, GREEN);
    push_front(&Board[2][6].stack, GREEN);
    push_front(&Board[3][3].stack, GREEN);
    push_front(&Board[3][4].stack, GREEN);
    push_front(&Board[4][1].stack, GREEN);
    push_front(&Board[4][2].stack, GREEN);
    push_front(&Board[4][5].stack, GREEN);
    push_front(&Board[4][6].stack, GREEN);
    push_front(&Board[5][3].stack, GREEN);
    push_front(&Board[5][4].stack, GREEN);
    push_front(&Board[6][1].stack, GREEN);
    push_front(&Board[6][2].stack, GREEN);
    push_front(&Board[6][5].stack, GREEN);
    push_front(&Board[6][6].stack, GREEN);


    //Set the Empty Cell
    push_front(&Board[0][2].stack, EMPTY);
    push_front(&Board[0][3].stack, EMPTY);
    push_front(&Board[0][4].stack, EMPTY);
    push_front(&Board[0][5].stack, EMPTY);
    push_front(&Board[2][0].stack, EMPTY);
    push_front(&Board[3][0].stack, EMPTY);
    push_front(&Board[4][0].stack, EMPTY);
    push_front(&Board[5][0].stack, EMPTY);

    push_front(&Board[7][2].stack, EMPTY);
    push_front(&Board[7][3].stack, EMPTY);
    push_front(&Board[7][4].stack, EMPTY);
    push_front(&Board[7][5].stack, EMPTY);
    push_front(&Board[2][7].stack, EMPTY);
    push_front(&Board[3][7].stack, EMPTY);
    push_front(&Board[4][7].stack, EMPTY);
    push_front(&Board[5][7].stack, EMPTY);


    //Block Cells
    Board[0][0].block = true;
    Board[0][1].block = true;
    Board[1][0].block = true;
    Board[0][6].block = true;
    Board[0][7].block = true;
    Board[1][7].block = true;
    Board[6][0].block = true;
    Board[7][0].block = true;
    Board[7][1].block = true;
    Board[6][7].block = true;
    Board[7][6].block = true;
    Board[7][7].block = true;

}

//Print_Board: Prints the board of the game, with axis and colors
void Print_Board() {
    int i, j;
    //in a double loop
    for (i = 0; i < SIZE; i++) {
        printf(" %d|", i);
        for (j = 0; j < SIZE; j++) {
            //If the cell is not blocked
            if (!Board[i][j].block) {
                printTop(Board[i][j].stack);
            }
            else {
                printf("   ");
            }
        }
        printf("\n");
    }
    printf("   --------------------------\n   ");
    for (i = 0; i < 8; i++) {
        printf(" %d ", i);
    }
    printf("\n");
}