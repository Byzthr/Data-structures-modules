#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*

Linked list library created for academic purpouses by Byzthr (Victor Garcia).

Includes basic functions to create, update, modify, traverse and reverse integer
linked lists.
A linked list is referred as a pointer to its first Node.
An empty linked list can be created by initializing a NULL Node pointer.
Nodes of the linked lists will be saved in the heap.

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

/* Deletes the Node at the specified position (int pos). The linked list argument must be a pointer to the heads pointer (Node **hpp). Prints an error if index is larger than linked list length minus one. It also frees the allocadted Node in the heap. */
void deleteNode(Node **hpp, int pos) {

    int len = linkListLen(*hpp);
    if (pos > len-1) {
        printf("\nDelete error: Index specified (%d, corresponding to %dth element) out of linked list with length (%d).\n\n", pos, pos+1, len);
        return ;
    }

    Node *np = *hpp;

    if (pos == 0) {
        *hpp = np -> next;
        free(np);
        return ;
    }
    for (int i = 0; i < pos-1; i++) np = np -> next;
    Node *afternode = np -> next -> next;
    free(np -> next);
    np -> next = afternode;
}

/* Modifies the Node at the specified position (int pos) with the specified value (int value) in the specified linked list (Node *hp). Prints an error if index is larger than linked list length minus one. */
void updateNode(Node *hp, int value, int pos) {

    int len = linkListLen(hp);
    if (pos > len-1) {
        printf("\nUpdate error: Index specified (%d, corresponding to %dth element) out of linked list with length (%d).\n\n", pos, pos+1, len);
        return ;
    }

    int i = 0;
    while (i < pos - 1) {
        hp = hp -> next;
    }
    hp -> val = value;
}

/* Appends a node to the end of the specified linked list (Node *hp) with the specified value (int value). Prints an error if the linked list is empty. */
void appendNode(Node *hp, int value) {

    int i = 0;
    if (!hp) {
        printf("\nAdd error: Adding items to empty linked list is illegal.\n\tFirst node must be inserted [insertNode(Node **nodePointerPointer, int val, int pos = 0]).\n\n");
        return ;
    }
    while (hp -> next) {
        hp = hp -> next;
    }
    Node *temp = (Node *) malloc(sizeof(Node));
    temp -> val = value;
    temp -> next = NULL;
    hp -> next = temp;
}

/* Reverses the linked list specifiying a pointer to the head's pointer (Node **hpp). */
void reverseLinkList(Node **hpp) {

    if (!*hpp) return ;

    Node *prev = *hpp;
    Node *np = prev -> next;
    Node *next;

    prev -> next = NULL;
    while (np) {
        next = np -> next;
        np -> next = prev;
        prev = np;
        np = next;
    }
    *hpp = prev;
}

/* Prints the nodes of the specified likes list (Node *hp) values in an array format [a, b, c...]. Uses iterative method. */
void printLinkList(Node *hp) {
    int i = 0;
    printf("Length: %d\n", linkListLen(hp));
    printf("Linked list: [");
    if (!hp) {
        printf("]\n");
        return;
    }
    while (hp) {
        printf("%d, ", hp -> val);
        hp = hp -> next;
    }
    printf("\b\b]\n");
    
}

