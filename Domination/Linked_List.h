
#ifndef DOMINATION_LINKED_LIST_H
#define DOMINATION_LINKED_LIST_H
#include "Struct_Definitions.h"

//***Linked List Functions***//
void push_front(struct Node **head, int data);
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

#endif //DOMINATION_LINKED_LIST_H
