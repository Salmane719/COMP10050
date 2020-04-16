
//Turn.h contains Linked_List.h that contains Struct_Definitions.h, that has all libraries used
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <ctype.h>
//
//and the definitions of the structs
//Is only necessary to define once this file, otherwise, this will return errors
#include "Turn.h"
#include "SetBoard.h"


//--------------------------------
// MAIN FUNCTION
//--------------------------------
int main() {
    //declare the two players
    Player P1, P2;


    //Display header
    header();
    printf("Press enter to start the game\n");
    system("pause");

    //Clean console
    system("cls");//IN LINUX CHANGE TO system("clean");

    //Set the values of the intial board
    Initial_Board(&P1, &P2);
    //display header
    header();
    //print board
    Print_Board();

    bool Winner;
    Winner=false;

    //This is just for play 2 turns
    while (!Winner) {
        //Turn of player 1
        Turn(&P1);//call turn
        //check if the current player is the winner
        Winner=CheckWinner(P2);
        if(Winner) {
            //Then the player 1 is the winner, display the info and captured pieces
            printf("\033[1;31m PLAYER %d IS THE WINNER!!\033[0m\n", P1.number);
            //break the while loop
            break;
        }

        Print_Board();//print board

        printf("Press enter to continue...\n");
        getchar();
        getchar();

        system("cls");//IN LINUX CHANGE TO system("clean");
        header();//display header
        Print_Board();//print board

        //Turn of player 2
        Turn(&P2);
        //check if the current player is the winner,
        //Call CheckWinner to see if the other player does not have any more moves
        Winner=CheckWinner(P1);
        if(Winner){
            //Then the player 1 is the winner, display the info and captured pieces
            printf("\033[1;32m PLAYER %d IS THE WINNER!!\033[0m\n",P2.number);
            //break the while loop

            break;
         }
        Print_Board();//print board

        printf("Press enter to continue...\n");
        getchar();
        getchar();
        system("cls");//IN LINUX CHANGE TO system("clean");
        header();//display header
        Print_Board();//print board
    }

    printf("Player 1\nCaptured pieces %d\n",P1.captured);
    printf("Player 2\nCaptured pieces %d\n",P2.captured);

    return 0;

}

