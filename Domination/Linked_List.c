//
// Created by Draum on 07/04/2020.
//


#include "Linked_List.h"


//*********************************
//****LINKED LIST FUNCTIONS*****
//*******************************

//push_front: Add at item at the begining of the linked list
void push_front(struct Node **head, int data) {
    //Create a new node, and allocate the necesary space
    Node *new_node = malloc(sizeof(Node));
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
    if (head == NULL) {
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
Node* removeLast(struct Node* head) {
    //If the head is NULL, return the head ( a NULL list)
    if (head == NULL) {
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
    while (temp->next->next != NULL) {
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
        if (n->data == RED) {
            //Print "R" in red color
            printf("\033[1;31mR\033[0m");
        }
            //If the data is GREEN
        else if (n->data == GREEN) {
            //Print "G" in red color
            printf("\033[1;32mG\033[0m");
        }
            //Else, print an empty space
        else {
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
    if (n->data == RED) {
        //Print "R" in red color
        printf("\033[1;31mR\033[0m");
    }
        //If the data is GREEN
    else if (n->data == GREEN) {
        //Print "G" in red color
        printf("\033[1;32mG\033[0m");
    }
        //Else, print an empty space
    else {
        printf(" ");
    }
    //Move to the next node
    n = n->next;
    printf(")");
}

//printLast: Prints the Last element from the list
void printLast(struct Node* n) {
    if (n == NULL) {
        printf("   ");
    }
    else if (n->next == NULL) {
        printf("( )");
    }
    else {
        // Find the second last node
        Node* temp = n;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }

        printf("(");
        if (temp->data == RED) {
            printf("\033[1;31mR\033[0m");
        }
        else if (temp->data == GREEN) {
            printf("\033[1;32mG\033[0m");
        }
        else {
            printf(" ");
        }
        printf(")");
    }
}

//getTop: Get the value of the top element from the list
int getTop(struct Node* n) {
    int Top;
    //Store the value of the current node in Top
    Top = n->data;
    n = n->next;
    //return Top
    return Top;
}

//getLast: Get the value of the last element from the list
int getLast(struct Node* n) {
    //if the list is empty (n==NULL) or the list has only one node (n->next==NULL)
    if (n == NULL || n->next == NULL) {
        //return 0
        return 0;
    }
    // Find the second last node
    Node* temp = n;
    //While the next node of the next nde to the current is not null
    while (temp->next->next != NULL) {
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
Node* copyList(struct Node *n) {
    //if n is null, return null
    if (n == NULL) {
        return NULL;
    }
    //allocate space for a new node
    Node *temp = malloc(sizeof(Node));
    //Copy the data from n to temp
    temp->data = n->data;
    //copy the next element
    temp->next = copyList(n->next);
    //return temp
    return temp;
}
