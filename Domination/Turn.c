//
// Created by Draum on 07/04/2020.
//


#include "Turn.h"

//******************************************
//****TURN FUNCTIONS*****
//*****************************************

//Turn: shows the options for the player, including moving a piece
void Turn(Player *P) {
    //declare variables to use
    int option;//store the option from the player menu
    bool exit;//bool to validate information
    //set exit to false
    exit = false;
    //This will print the message red or green
    if (P->color == RED) {
        printf("\033[1;31m");
    }
    else {
        printf("\033[1;32m");
    }
    //display message informing the color of the player
    printf("\nPLAYER %d TURN - \nAVAILABLE PIECES: %d\nCAPTURED PIECES: %d\n", P->number, P->suply, P->captured);
    //this will return the console to the default color
    printf("\033[0m");

    //While exit is false
    while (!exit) {
        //Present the menu and validate the option (must be: 0, 1 or 2)
        option = Menu();

        switch (option) {
            case 0: InfoAboutAnSpace(); break;
            case 1:
                PossibleMoves(P->color, true); break;
            case 2: if (PieceIntoBoard(&P->suply, P->color)) exit = true; break;
            case 3: MoveAPiece(P);	exit = true; break;
            case 4: exit = true;  break;
        }

    }//END WHILE

}

int Menu() {
    char option[10];
    int op;
    printf("\nSelect an option: \n");
    printf("[0] - Info about an space \n");
    printf("[1] - Possible pieces to move \n");
    printf("[2] - Place a piece into the board \n");
    printf("[3] - Move a piece \n");
    printf("[4] - Pass Turn \nOption: ");
    scanf("%s", option);
    op=isNumber(option);
    //Present the menu and validate the option
    while (op > 4 || op < 0 ) {
        printf("Invalid input. \nOption: ");
        scanf("%s", option);
        op=isNumber(option);
    }
    return op;
}

void InfoAboutAnSpace() {
    int x, y;
    //select a piece
    printf("Select an space to get info about the stack (vertical horizontal): ");
    scanf("%d", &x);
    scanf("%d", &y);
    //If it's blocked, display in message
    if (Board[x][y].block) {
        printf("That space is blocked \n");
    }
        //If it's out of range, display message
    else if (x > 7 || x < 0 || y>7 || y < 0) {
        printf("That space is out of range \n");
    }
        //Else
    else {
        //Display, postition and relevant information.
        printf("[%d,%d] ", x, y);
        printList(Board[x][y].stack);
        printf(" TOP is : ");
        printTop(Board[x][y].stack);
        printf(" Size is: %d \n", sizeList(Board[x][y].stack));
    }
}

int PossibleMoves(int color, bool print) {
    int i, j, moves;
    moves = 0;
    //iterate through the board
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            //For the pieces that are not blocked
            if (!Board[i][j].block) {
                //If the piece match the color of the player
                if (getTop(Board[i][j].stack) == color) {
                    if (print) {
                        //Display info
                        printf("[%d,%d] ", i, j);
                        printList(Board[i][j].stack);
                        printf(" TOP is : ");
                        printTop(Board[i][j].stack);
                        printf(" Size is: %d \n", sizeList(Board[i][j].stack));
                    }
                    moves++;
                }
            }
        }
    }
    return moves;
}


bool PieceIntoBoard(int *suply, int color) {
    int x, y;
    bool valid;

    if (PossibleMoves(color, false) == 0) {
        printf("You have possible moves in the board\n");
        return false;
    }
    else if (*suply == 0) {
        printf("You do not have a piece available to move\n");
        return false;
    }
    else {
        //Ask for the position of the piece to move
        do {
            //select a piece
            printf("Select a position to put the piece (vertical horizontal): ");
            scanf("%d", &x);
            scanf("%d", &y);
            if (!Board[x][y].block&&x <= 7 && x >= 0 && y <= 7 && y >= 0) {
                valid = true;
            }
            else {
                printf("Invalid direction: ");
                valid = false;
            }

        } while (!valid);


        push_front(&Board[x][y].stack, color);
        *suply = *suply - 1;
        return true;
    }
}

//Ask for piece or stack on the board to move
void MoveAPiece(Player *P) {
    int x1, y1, x2, y2, i; //To store the coordenates of start and end
    int stack;//to store the size of the stack
    int tomove;//to store the number of pieces the player wants to move
    char direction;//to pick the direction to move
    char strTomove[5];
    bool valid, valid_dir;//bool to validate information
    //Ask for the position of the piece to move
    do {
        //select a piece
        printf("Select a piece to move (vertical horizontal): ");
        scanf("%d", &x1);
        scanf("%d", &y1);

    } while (Board[x1][y1].block || getTop(Board[x1][y1].stack) != P->color);

    //Store the size of the stack in stack
    stack = sizeList(Board[x1][y1].stack);
    //If it's bigger than 1, ask the player how many pieces s/he wants to move
    if (stack > 1) {
        valid = false;
        do {
            printf("How many pieces do you want to move? You can move up to (%d) : ", stack);
            scanf("%s", strTomove);
            tomove=isNumber(strTomove);
        } while (tomove > stack || tomove==-1);
    }
        //else, tomove is 1
    else {
        tomove = 1;
    }

    //In a loop from 0 to tomove, that is, move the stack one space at a time
    for (i = 0; i < tomove; i++) {
        //Ask for the position at which the piece will be moved
        valid = false;
        while (!valid) {
            //select a piece, use a do-while loop to validate that the input is a char
            do {
                getchar();
                printf("Move piece UP(u,U) RIGHT(r,R) DOWN(d,D) LEFT(l,L): ");
                scanf("%c", &direction);
            } while (!isalpha(direction));

            //set valid_dir to false, this will be true if the direction is UP, RIGHT, DOWN or LEFT
            valid_dir = false;
            //use swtch case to act accoring to the direction selected
            switch (direction) {
                //CASE UP: move up (x value), set valid_dir=true
                case 'u':x2 = x1 - 1; y2 = y1; valid_dir = true; break;
                case 'U':x2 = x1 - 1; y2 = y1; valid_dir = true; break;
                    //CASE RIGHT: move right (y value), set valid_dir=true
                case 'r':x2 = x1; y2 = y1 + 1; valid_dir = true; break;
                case 'R':x2 = x1; y2 = y1 + 1; valid_dir = true; break;
                    //CASE DOWN: move down (x value), set valid_dir=true
                case 'd':x2 = x1 + 1; y2 = y1; valid_dir = true; break;
                case 'D':x2 = x1 + 1; y2 = y1; valid_dir = true; break;
                    //CASE LEFT: move left (y value), set valid_dir=true
                case 'l':x2 = x1; y2 = y1 - 1; valid_dir = true; break;
                case 'L':x2 = x1; y2 = y1 - 1; valid_dir = true; break;
                    //any other letter,
                default: printf("Invalid direction: "); break;
            }
            //only if the direction was valid
            if (valid_dir) {
                //check  it's allowed: if the space is not blocked and the new direction is not out of range
                if (!Board[x2][y2].block&&x2 <= 7 && x2 >= 0 && y2 <= 7 && y2 >= 0) {
                    valid = true;
                }
                else {
                    printf("Invalid direction: ");
                }
            }
            //to exit this loop both valid and valid_dir must be true

        }

        //call move to move the piece
        move(x1, y1, x2, y2, tomove);
        CheckFor5Rule(x2, y2, &P->suply, &P->captured, P->color);
        //The new x1,y1 values are the new position
        x1 = x2;
        y1 = y2;
    }

}

//move: moves N pieces from x1,y1 to x2,y2
void move(int x1, int y1, int x2, int y2, int N) {
    int i;
    //To do the movement, first, is necesary to copy the stack to a temp linked list
    Node* temp;
    temp = copyList(Board[x1][y1].stack);

    //The new linked list is created of the size of the stack to move N
    while (N < sizeList(temp)) {
        temp = removeLast(temp);
    }

    //Now, we will use reverse, to reverse the order of the elements in temp
    temp = reverse(temp);

    //The program push_front the elements, and at the same time remove the top element from temp
    for (i = 0; i < N; i++) {
        push_front(&Board[x2][y2].stack, getTop(temp));
        temp = removeTop(temp);
    }
    //The program then delete the elements from the old location, if all the elements were move then set the space to empty
    for (i = 0; i < N; i++) {
        Board[x1][y1].stack = removeTop(Board[x1][y1].stack);
    }
    if (sizeList(Board[x1][y1].stack) == 0) {
        push_front(&Board[x1][y1].stack, EMPTY);
    }
}

void CheckFor5Rule(int x, int y, int *suply, int *captured, int color) {
    //printf("S: %d  C: %d\n",*suply,*captured);
    while (sizeList(Board[x][y].stack) > 5) {
        if (getLast(Board[x][y].stack) == color) {
            *suply = *suply + 1;
            printf("The piece ");
            printLast(Board[x][y].stack);
            printf(" has been added to your supply...\n");
        }
        else {
            *captured = *captured + 1;
            printf("The piece ");
            printLast(Board[x][y].stack);
            printf(" has been captured...\n");
        }
        removeLast(Board[x][y].stack);
    }
    //printf("S: %d  C: %d\n",*suply,*captured);
}

bool CheckWinner(Player next){
    //If the possible moves of the next player are 0
    if(PossibleMoves(next.color,false)==0) {
        //then, the current player is the winner
        return true;
    }
    //else, the return value is -1
    else{
        return false;
    }
}

int isNumber(char str[10]){
    int i,size;
    size=strlen(str);
    for(i=0;i<size;i++){
        if(isdigit(str[i])==0){
            return -1;
        }
    }
    return atoi(str);
}


