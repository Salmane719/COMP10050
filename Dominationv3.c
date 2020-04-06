#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 8

//Enum to control the different states of the board
enum color{EMPTY,RED,GREEN};

//-------------------------------- 
// Struct - START: 
//--------------------------------
//******LINKED LIST******
typedef struct Node {
    int data;			//Store data
    struct Node *next;	//Link to next node
} Node;

//*******BOARD***********
struct Board {
	Node *stack;		//Linked list
	bool block;			//set block for non valid positions (corners)
}Board[SIZE][SIZE];

//*******PLAYER********
typedef struct Player{
	int color;			//Color from enum
	char *c_color;		//string name of the color
	int suply;			//Current suply of pieces from the player
	int captured;		//Current nummber of pieces captured by the player
	int number;			//Number of player (1 or 2)
}Player;


//-------------------------------- 
// Declarations - START: 
//--------------------------------
//***Linked List Functions***//
void push_front(struct Node **head, int data );
Node* removeTop(struct Node* head);
Node* removeLast(struct Node* head);
void printList(struct Node* n);
void printTop(struct Node* n);
void printLast(struct Node* n);
int getTop(struct Node* n);
int getLast(struct Node* n);
int sizeList(struct Node* n);
Node* reverse(struct Node* n);
Node* copyList(struct Node *n);

//**Funtion to initialize the game**//
void header();
void Print_Board();
void Initial_Board(Player *P1, Player *P2);

//****Turn Functions***///
void Turn(Player *P);
int Menu();
void InfoAboutAnSpace();
int PosibleMoves(int color,bool print);

//Movement functions
void MoveAPiece(Player *P);
bool PieceIntoBoard(int *suply,int color);
void move(int x1,int y1,int x2,int y2,int N);
void CheckFor5Rule(int x, int y, int *suply,int *captured, int color);

//-------------------------------- 
// MAIN FUNCTION
//--------------------------------
int main(void) {
	//declare the two players
	Player P1,P2;
	
	
	//Display header
	header();
	printf("Press enter to start the game\n");
	system("pause");
	
	//Clean console
	system("cls");//IN LINUX CHANGE TO system("clean");
	
	//Set number of turns (since there are no wining condition so far)
	int turns, i;
	printf("\nSelect the number of turns to play: ");
	scanf("%d",&turns);
	
	//Set the values of the intial board
	Initial_Board(&P1,&P2);
	//display header
	header();
	//print board
	Print_Board();
	
	i=0;
	//This is just for play 2 turns
	while(i<turns){
		//display the turn number
		printf("Turn %d \n",i+1);
		
		//Turn of player 1
		Turn(&P1);//call turn
		Print_Board();//print board
		
		printf("Press enter to continue...\n");
		getchar();
		getchar();
		
		system("cls");//IN LINUX CHANGE TO system("clean");
		header();//display header
		Print_Board();//print board
		printf("Turn %d \n",i+1);
		
		//Turn of player 2
		Turn(&P2);
		Print_Board();//print board
		
		printf("Press enter to continue...\n");
		getchar();
		getchar();
		system("cls");//IN LINUX CHANGE TO system("clean");
		header();//display header
		Print_Board();//print board
		i++;
	}
	
	
	return 0; 
}
    

//-------------------------------- 
// Definitions - START: 
//-------------------------------- 

//*********************************
//****LINKED LIST FUNCTIONS*****
//*******************************

//push_front: Add at item at the begining of the linked list
void push_front(struct Node **head, int data ){
	//Create a new node, and allocate the necesary space
    Node *new_node = malloc( sizeof( Node ) );
    //Make data (from parameters) the data for this node
    new_node->data = data;
    //Set the next node to head
    new_node->next = *head;
    //The head is now the new_node
    *head = new_node;

}


//removeTop: Remove the Top node from the list
Node* removeTop(struct Node* head) {
	//If the head is NULL, return the head ( a NULL list) 
    if (head == NULL){
    	return head; 
	} 

    //Create a temp node pointing to head
    Node* temp = head;
    //move head to the next node
    head = head->next;
    // Clears the memory occupied by first node
    free(temp);  
    
    //returns the list withut the first node
	return head; 
} 

//removeLast: Remove the last element form the list (before NULL)
Node* removeLast(struct Node* head){
	//If the head is NULL, return the head ( a NULL list) 
	if (head == NULL){
    	return head; 
	} 
  	//If the node next to head is NULL, clear head and return  a NULL list
    if (head->next == NULL) { 
        free(head); 
        return NULL; 
    } 
  
    // Find the second last node 
    Node* temp = head; 
    //iterate until the second last node is found
    while (temp->next->next != NULL){
    	temp = temp->next; 
	} 
  	
    // Delete last node 
    free(temp->next); 
  
    // Change next of second last 
    temp->next = NULL; 
  
    return head; 
    
}

//printList: Prints the values linked list (in the stack)
void printList(struct Node* n) { 	
	printf("|");
	//while the current node is not null
    while (n != NULL) { 
    	//If the data is RED
    	if(n->data==RED){
    		//Print "R" in red color
    		printf("\033[1;31mR\033[0m");
		}
		//If the data is GREEN
		else if(n->data==GREEN){
			//Print "G" in red color
			printf("\033[1;32mG\033[0m");
		}
		//Else, print an empty space
		else{
			printf(" ");
		}
		//move to the next node
        n = n->next; 
        //use | to separate elements on the list
        printf("|");
    } 
}

//printTop: Prints the Top element from the list
void printTop(struct Node* n) { 
	printf("(");	
    if(n->data==RED){
    	//Print "R" in red color
    	printf("\033[1;31mR\033[0m");
	}
	//If the data is GREEN
	else if(n->data==GREEN){
		//Print "G" in red color
		printf("\033[1;32mG\033[0m");
	}
	//Else, print an empty space
	else{
		printf(" ");
	}
	//Move to the next node
	n = n->next; 
    printf(")");
}

//printLast: Prints the Last element from the list
void printLast(struct Node* n) { 
	if (n == NULL){
    	printf("   ");
	} 
	else if (n->next == NULL) { 
        printf("( )");
    } 
  	else{
	    // Find the second last node 
	    Node* temp = n; 
	    while (temp->next->next != NULL){
	    	temp = temp->next; 
		} 
			
		printf("(");	
	    if(temp->data==RED){
	    	printf("\033[1;31mR\033[0m");
		}
		else if(temp->data==GREEN){
			printf("\033[1;32mG\033[0m");
		}
		else{
			printf(" ");
		}
	    printf(")");
	}	
}

//getTop: Get the value of the top element from the list
int getTop(struct Node* n) { 
	int Top;
	//Store the value of the current node in Top
	Top=n->data;
	n = n->next;
	//return Top 
    return Top;
}

//getLast: Get the value of the last element from the list
int getLast(struct Node* n){
	//if the list is empty (n==NULL) or the list has only one node (n->next==NULL)
	if (n == NULL||n->next == NULL ){
		//return 0
    	return 0; 
	} 
    // Find the second last node 
    Node* temp = n; 
    //While the next node of the next nde to the current is not null
    while (temp->next->next != NULL){
    	//keep moving throug the list
    	temp = temp->next; 
	} 
	//return the value
	return temp->data;
}

//sizeList: Obtains and returns the size of the list
int sizeList(struct Node* n) {  
    int count = 0; // Initialize count 
    //While current is not NULL, i.e. iterate through  the list
    while (n != NULL) { 
    	//increase count in 1 unit
	    count++;
	    //move to the next node
        n = n->next; 
    }
	//return count  
    return count;  
} 
   
//reverse: Reverse the order of the elements in the linked list
Node* reverse(struct Node* n) { 
    // Initialize current, previous and 
    // next pointers 
    Node* current = n; 
    
	Node *prev = NULL, *next = NULL; 
  
  	//while curent is not null
    while (current != NULL) { 
        // Store next 
        next = current->next; 
  
    	// Reverse current node's pointer 
        current->next = prev; 
  
        // Move pointers one position ahead. 
         prev = current; 
        current = next; 
	} 
    n = prev; 
    
    return n;
} 

//copylist: Make a copy of the list
Node* copyList(struct Node *n){
	//if n is null, return null
    if(n==NULL){
    	return NULL;
	}
	//allocate space for a new node
    Node *temp=malloc( sizeof( Node ) );
    //Copy the data from n to temp
    temp->data=n->data;
    //copy the next element
    temp->next=copyList(n->next);
    //return temp
    return temp;
}

//******************************************
//****FUNCTIONS TO INITIALICE THE GAME*****
//*****************************************
//header: prints the name of the game 
void header(){
	
	printf(" _____                  _             _   _             \n");
	printf("|  __ \\                (_)           | | (_)            \n");
	printf("| |  | | ___  _ __ ___  _ _ __   __ _| |_ _  ___  _ __  \n");
	printf("| |  | |/ _ \\| '_ ` _ \\| | '_ \\ / _` | __| |/ _ \\| '_ \\ \n");
	printf("| |__| | (_) | | | | | | | | | | (_| | |_| | (_) | | | |\n");
	printf("|_____/ \\___/|_| |_| |_|_|_| |_|\\__,_|\\__|_|\\___/|_| |_|\n");
	printf("\n\n");
}

//Initial_Board: Intialice the players and the board
void Initial_Board(Player *P1, Player *P2){
	//Set values for player 1
	P1->color=RED;
	P1->number=1;
	P1->c_color="RED";
	P1->suply=0;
	P1->captured=0;
	//Set values for player 2
	P2->color=GREEN;
	P2->number=2;
	P2->c_color="GREEN";
	P2->suply=0;
	P2->captured=0;
	
	int i,j,k;
	//Set all linked list nodes to null
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			Board[i][j].stack=NULL;
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
	Board[0][0].block=true;
	Board[0][1].block=true;
	Board[1][0].block=true;
	Board[0][6].block=true;
	Board[0][7].block=true;
	Board[1][7].block=true;
	Board[6][0].block=true;
	Board[7][0].block=true;
	Board[7][1].block=true;
	Board[6][7].block=true;
	Board[7][6].block=true;
	Board[7][7].block=true;
	
}

//Print_Board: Prints the board of the game, with axis and colors
void Print_Board(){
	int i,j;
	//in a double loop
	for(i=0;i<SIZE;i++){
		printf(" %d|",i);
		for(j=0;j<SIZE;j++){
			//If the cell is not blocked
			if(!Board[i][j].block){
				printTop(Board[i][j].stack);
			}
			else{
				printf("   ");
			}
		}
		printf("\n");
	}
	printf("   --------------------------\n   ");
	for(i=0;i<8;i++){
		printf(" %d ",i);
	}
	printf("\n");
}

//******************************************
//****TURN FUNCTIONS*****
//*****************************************
//Turn
//Turn: shows the options for the player, including moving a piece
void Turn(Player *P){
	//declare variables to use
	int option;//store the option from the player menu
	bool exit;//bool to validate information
	//set exit to false
	exit=false;
	//This will print the message red or green
	if(P->c_color=="RED"){
		printf("\033[1;31m");
	}
	else{
		printf("\033[1;32m");
	}
	//display message informing the color of the player
	printf("\nPLAYER %d TURN - \nAVAILABLE PIECES: %d\nCAPTURED PIECES: %d\n",P->number,P->suply,P->captured);
	//this will return the console to the default color
	printf("\033[0m");
	
	//While exit is false
	while(!exit){
		//Present the menu and validate the option (must be: 0, 1 or 2)
		option=Menu();
		
		switch(option){
			case 0: InfoAboutAnSpace(); break;
			case 1: PosibleMoves(P->color,true); break;
			case 2: if(PieceIntoBoard(&P->suply,P->color)) exit=true; break;		
			case 3: MoveAPiece(P);	exit=true; break;
			case 4: exit=true;  break;
		}	
	
	}//END WHILE
	
}

int Menu(){
	int option;
	//Present the menu and validate the option (must be: 0, 1 or 2)
	do{
		printf("\nSelect an option: \n");
		printf("[0] - Info about an space \n");
		printf("[1] - Posible pieces to move \n");
		printf("[2] - Place a piece into the board \n");
		printf("[3] - Move a piece \n");
		printf("[4] - Pass Turn \nOption: ");
		scanf("%d",&option);
	}while(option>4 || option<0);
	return option;
}

void InfoAboutAnSpace(){
	int x,y;
	//select a piece
	printf("Select an space to get info about the stack (vertical horizontal): ");
	scanf("%d",&x);
	scanf("%d",&y);
	//If it's blocked, display in message
	if(Board[x][y].block){
		printf("That space is blocked \n");
	}
	//If it's out of range, display message
	else if(x>7||x<0||y>7||y<0){
		printf("That space is out of range \n");
	}
	//Else
	else{
		//Display, postition and relevant information.
		printf("[%d,%d] ",x,y);
		printList(Board[x][y].stack);
		printf(" TOP is : ");
		printTop(Board[x][y].stack);
		printf( " Size is: %d \n",sizeList(Board[x][y].stack));
	}
}

int PosibleMoves(int color,bool print){
	int i,j,moves;
	moves=0;
	//iterate through the board
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
		//For the pieces taht are not blocked
			if(!Board[i][j].block){
				//If the piece match the color of the player
				if( getTop(Board[i][j].stack)==color){
					if(print){
						//Display info
						printf("[%d,%d] ",i,j);
						printList(Board[i][j].stack);
						printf(" TOP is : ");
						printTop(Board[i][j].stack);
						printf( " Size is: %d \n",sizeList(Board[i][j].stack));
					}
					moves++;
				}
			}
		}
	}
	return moves;
}


bool PieceIntoBoard(int *suply,int color){
	int x,y;
	int i;
	bool valid;
	
	if(PosibleMoves(color,false)==0){
		printf("You have possible moves in the board\n");
	}
	else if(*suply==0){
		printf("You do not have a piece available to move\n");
	}
	else{
		//Ask for the position of the piece to move 
		do{
			//select a piece
			printf("Select a position to put the piece (vertical horizontal): ");
			scanf("%d",&x);
			scanf("%d",&y);
			if(!Board[x][y].block&&x<=7&&x>=0&&y<=7&&y>=0){
				valid=true;
			}
			else{
				printf("Invalid direction: ");
				valid=false;
			}
			
		}while(!valid);
		
		
		push_front(&Board[x][y].stack, color);
		*suply=*suply-1;
	}
}

//Ask for piece or stack on the board to move
void MoveAPiece(Player *P){
	int x1,y1,x2,y2,i,j; //To store the coordenates of start and end
	int stack;//to store the size of the stack
	int tomove;//to store the number of pieces the player wants to move
	char direction;//to pick the direction to move 
	bool valid, valid_dir;//bool to validate information
	//Ask for the position of the piece to move 
	do{
		//select a piece
		printf("Select a piece to move (vertical horizontal): ");
		scanf("%d",&x1);
		scanf("%d",&y1);
		//***
		printf("%d:%d\n",getTop(Board[x1][y1].stack),P->color);
		
	}while(Board[x1][y1].block || getTop(Board[x1][y1].stack)!=P->color);
				
	//Store the size of the stack in stack
	stack=sizeList(Board[x1][y1].stack);
	//If it's bigger than 1, ask the player how many pieces s/he wants to move
	if(stack>1){
		valid=false;
		do{
			printf("How many pieces do you want to move? You can move up to (%d) : ",stack);
			scanf("%d",&tomove);
		}while(tomove>stack);
	}
	//else, tomove is 1
	else{
		tomove=1;
	}
		
	//In a loop from 0 to tomove, that is, move the stack one space at a time
	for(i=0;i<tomove;i++){
		//Ask for the position at which the piece will be moved
		valid=false;
		while(!valid){
			//select a piece, use a do-while loop to validate that the input is a char
			do{
				getchar();
				printf("Move piece UP(u,U) RIGHT(r,R) DOWN(d,D) LEFT(l,L): ");
				scanf("%c",&direction);
			}while(!isalpha(direction));
							
			//set valid_dir to false, this will be true if the direction is UP, RIGHT, DOWN or LEFT
			valid_dir=false;
			//use swtch case to act accoring to the direction selected
			switch(direction){
				//CASE UP: move up (x value), set valid_dir=true
				case 'u':x2=x1-1; y2=y1; valid_dir=true; break;
				case 'U':x2=x1-1; y2=y1; valid_dir=true; break;
				//CASE RIGHT: move right (y value), set valid_dir=true
				case 'r':x2=x1; y2=y1+1; valid_dir=true; break;
				case 'R':x2=x1; y2=y1+1; valid_dir=true; break;
				//CASE DOWN: move down (x value), set valid_dir=true
				case 'd':x2=x1+1; y2=y1; valid_dir=true; break;
				case 'D':x2=x1+1; y2=y1; valid_dir=true; break; 
				//CASE LEFT: move left (y value), set valid_dir=true
				case 'l':x2=x1; y2=y1-1; valid_dir=true; break;
				case 'L':x2=x1; y2=y1-1; valid_dir=true; break;
				//any other letter, 
				default : printf("Invalid direction: "); break;
			}
			//only if the direction was valid
			if(valid_dir){
				//check  it's allowed: if the space is not blocked and the new direction is not out of range
				if(!Board[x2][y2].block&&x2<=7&&x2>=0&&y2<=7&&y2>=0){
					valid=true;
				}
				else{
					printf("Invalid direction: ");
				}	
			}
			//to exit this loop both valid and valid_dir must be true
					
		}
						
		//call move to move the piece
		move(x1,y1,x2,y2,tomove);
		CheckFor5Rule(x2,y2,&P->suply,&P->captured,P->color);
		//The new x1,y1 values are the new position
		x1=x2;
		y1=y2;
	}

}

//move: moves N pieces from x1,y1 to x2,y2
void move(int x1,int y1,int x2,int y2,int N){
	int i;
	//To do the movement, first, is necesary to copy the stack to a temp linked list
	Node* temp;
	temp=copyList(Board[x1][y1].stack);
	
	//The new linked list is created of the size of the stack to move N
	while(N<sizeList(temp)){
		temp=removeLast(temp);
	}
	
	//Now, we will use reverse, to reverse the order of the elements in temp
	temp=reverse(temp);
	
	//The program push_front the elements, and at the same time remove the top element from temp
	for(i=0;i<N;i++){
		push_front(&Board[x2][y2].stack, getTop(temp));
		temp=removeTop(temp);	
	}
	//The program then delete the elements from the old location, if all the elements were move then set the space to empty
	for(i=0;i<N;i++){
		Board[x1][y1].stack=removeTop(Board[x1][y1].stack);	
	}
	if(sizeList(Board[x1][y1].stack)==0){
		push_front(&Board[x1][y1].stack,EMPTY);
	}
}

void CheckFor5Rule(int x, int y, int *suply,int *captured, int color){
	//printf("S: %d  C: %d\n",*suply,*captured);
	while(sizeList(Board[x][y].stack)>5){
		if(getLast(Board[x][y].stack)==color){
			*suply=*suply+1;
			printf("The piece ");
			printLast(Board[x][y].stack);
			printf(" has been added to your supply...\n");
		}
		else{
			*captured=*captured+1;
			printf("The piece ");
			printLast(Board[x][y].stack);
			printf(" has been captured...\n");
		}
		removeLast(Board[x][y].stack);
	}
	//printf("S: %d  C: %d\n",*suply,*captured);
}


