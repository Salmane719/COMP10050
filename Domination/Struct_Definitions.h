//
// Created by Draum on 07/04/2020.
//

#ifndef DOMINATION_STRUCT_DEFINITIONS_H
#define DOMINATION_STRUCT_DEFINITIONS_H

//Libraries to include
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

//Define size of the board
#define SIZE 8
enum color { EMPTY, RED, GREEN };

typedef struct Node {
    int data;			//Store data
    struct Node *next;	//Link to next node
} Node;

//******LINKED LIST******
struct Board {
    Node *stack;		//Linked list
    bool block;			//set block for non valid positions (corners)
}Board[SIZE][SIZE];

//*******PLAYER********
typedef struct Player {
    int color;			//Color from enum
    char *c_color;		//string name of the color
    int suply;			//Current suply of pieces from the player
    int captured;		//Current nummber of pieces captured by the player
    int number;			//Number of player (1 or 2)
}Player;

#endif //DOMINATION_STRUCT_DEFINITIONS_H
