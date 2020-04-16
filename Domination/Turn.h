//
// Created by Draum on 07/04/2020.
//

#ifndef DOMINATION_TURN_H
#define DOMINATION_TURN_H
#include "Linked_List.h"
//****Turn Functions***///
void Turn(Player *P);
int Menu();
void InfoAboutAnSpace();
int PossibleMoves(int color, bool print);
//Movement functions
void MoveAPiece(Player *P);
bool PieceIntoBoard(int *suply, int color);
void move(int x1, int y1, int x2, int y2, int N);
void CheckFor5Rule(int x, int y, int *suply, int *captured, int color);
//Check winning condition
bool CheckWinner(Player next);
int isNumber(char str[10]);
#endif //DOMINATION_TURN_H
