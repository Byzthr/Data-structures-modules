#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*

Linked list library created for academic purpouses by Byzthr (Victor Garcia).

Includes basic functions to create, update, modify, traverse and reverse integer
linked lists.
A linked list is referred as a pointer to its first Node.
An empty linked list can be created by initializing a NULL Node pointer.

*/


/* Structure representing a linked list node. Node type is defined for clarity. */
typedef struct intLinkedListNode {
    int val;
    struct intLinkedListNode *next;
} Node;

/* Function to create linked list from array of integers (int *values). Length (int len) of the array must be greater than 0. */
Node *linkList(int *values, int len) {

    Node *headp = (Node *) malloc(sizeof(Node *));
    Node *np = headp;
    Node *bufp;

    for (int i = 0; i < len; i++) {
        np -> val = *(values + i);
        np -> next = (Node *) malloc(sizeof(Node));
        bufp = np;
        np = np -> next;
    }
    bufp -> next = NULL;
    return headp;
}

/* Given an pointer to the head, returns length of the linked list. */
int linkListLen(Node *lp) {
    int len;
    for (len = 0 ; lp; lp = lp -> next, ++len) ;
    return len;
}

/* Insert integer value (int value) into the specified position (int pos). The linked list argument must be a pointer to the heads pointer (Node **hpp). Prints an error if index is larger than linked list length. */
void insertNode(Node **hpp, int value, int pos) {

    int len = linkListLen(*hpp);
    if (pos > len) {
        printf("\nInsert error: Index specified (%d) out of linked list with length (%d).\n\n", pos, len);
        return ;
    }

    Node *np = *hpp;
    Node *newnode = (Node *) malloc(sizeof(Node));
    newnode -> val = value;

    if (pos == 0) {
        newnode -> next = np;
        *hpp = newnode;
        return ;
    }

    for (int i = 0; i < pos-1; i++) np = np -> next;
    newnode -> next = np -> next;
    np -> next = newnode;
}


