#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define max(a, b) (((a) > (b)) ? (a) : (b))     // This macros might be problematic. Since the macros variables are substituted literally, double evaluation might occur.
#define min(a, b) (((a) < (b)) ? (a) : (b))     // Example: min(x++, y++) translates to (((x++) > (y++)) ? (x++) : (y++)) so the increment in these variables would be 2 instead of 1.

/* Basic integer binary search tree (BST) creation and manipulatiion functions created by Byzthr. */

typedef struct binaryTreeNode {
    /* Structure corresponding to the node of a binary tree. Includes: 
        - [int data] integer value in the node.
        - [struct binaryTreeNode *left, struct searchTreeNode *right] pointers to both left and right children.
    It can be referred as STNode. */
    int data;
    struct binaryTreeNode *left;
    struct binaryTreeNode *right;
} BTNode;

BTNode *newNode(int data) {
    /* Function to create an STNode.
    Arguments:
        - [int data] value the node will keep.
    Returns:
        - Pointer to the created node allocated in the heap. */
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));
    node -> data = data;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

void insertBSTnode(BTNode **proot, int data) {
    /* Insert a node into a BST.
    Arguments:
        - [STNode **proot] address of the pointer to SBT's root.
        - [int data] integer value to keep in the node.
    Returns: void */
    BTNode *node = *proot;
    if (!node) {
        *proot = newNode(data);
        return ;
    }
    if (data <= node -> data) insertBSTnode(&(node -> left), data);
    else insertBSTnode(&(node -> right), data);
}

BTNode *BSTsearch(BTNode *node, int data) {
    /* Searches for specified value in the BST.
    Arguments:
        - [STNode *node] pointer to BST's root.
        - [int data] integer value to look for.
    Returns:
        - NULL if the value was not found.
        - Pointer to node if it was found. */
    if (!node) return NULL;
    if (node -> data == data) return node;
    if (data <= node -> data) BSTsearch(node -> left, data);
    else BSTsearch(node -> right, data);
}

BTNode *BSTmax(BTNode *node) {
    /* Finds the biggest value in the BST.
    Arguments:
        - [STNode *node] pointer to BST's root.
    Returns:
        - Biggest integer value in the BST. */
    if (!node) return NULL;
    if (!(node -> right)) return node;
    return BSTmax(node -> right);
}

BTNode *BSTmin(BTNode *node) {
    /* Finds the biggest value in the BST.
    Arguments:
        - [STNode *node] pointer to BST's root.
    Returns:
        - Biggest integer value in the BST. */
    if (!node) return NULL;
    if (!(node -> left)) return node;
    return BSTmin(node -> left);
}

int findHeight(BTNode *node) {
    /* Finds height (depth of the lowest leave) of the BST.
    Arguments:
        - [STNode *node] pointer to BST's root.
    Returns:
        - Height of the BST. */
    if (!node) return -1;
    int left, right;
    return max(findHeight(node -> left), findHeight(node -> right)) + 1;
}

void BT_DFT_pre(BTNode *node) {
    /* Depth first traversal function for binary trees (preorder traversal <root><left subtree><right subtree>[DLR]).
    Arguments:
        - [BTNode *node] pointer to BST's root.
    Returns: void */
    if (!node) return ;
    printf("%d\n", node -> data);
    BT_DFT_pre(node -> left);
    BT_DFT_pre(node -> right);
}

void BT_DFT_in(BTNode *node) {
    /* Depth first traversal function for binary trees (inorder traversal [LDR].
    Arguments:
        - [BTNode *node] pointer to BST's root.
    Returns: void. */
    if (!node) return ;
    BT_DFT_in(node -> left);
    printf("%d\n", node -> data);
    BT_DFT_in(node -> right);
}

void BT_DFT_post(BTNode *node) {
    /* Depth first traversal function for binary trees (postorder trasversal [RLD]).
    Arguments:
        - [BTNode *node] pointer to BST's root.
    Returns: void */
    if (!node) return ;
    BT_DFT_post(node -> left);
    BT_DFT_post(node -> right);
    printf("%d\n", node -> data);
}

// Queue structures and functions definition for BFS.

typedef struct BTQueueNode {
    /* Structure coresponding to the node of a linked list queue that stores BST node pointers.
        - [BTNode *btnode] pointer to binary tree node.
        - [struct linkQueueNode *next] pointer to the next item in the queue.
    Can be referred as QNode. */
    BTNode *data;
    struct BTQueueNode *next;
} QNode;

typedef struct BTQueue {
    /* Structure representing a linked list queue.
        - [QNode *front] pointer to the front of the queue.
        - [QNode *rear] pointer to the rear of the queue.
    Can be referred as LQueue. */
    QNode *front;
    QNode *rear;
} BTQueue;

BTQueue *newQueue(void) {
    /* Creates a new binary tree node queue.
    Arguments: void.
    Returns:
        - Pointer stored in the heap to queue structure with NULL values on rear and front. */
    BTQueue *q = (BTQueue *) malloc(sizeof(BTQueue));
    q -> front = NULL;
    q -> rear = NULL;
}

int qisempty(BTQueue *q) {
    /* Evaluates if a queue is empty.
    Arguments:
        - [BTQueue *q] Pointer to queue.
    Returns:
        - TRUE if the queue is empty.
        - FALSE if the queue is not empty. */
    if (q -> front == NULL && q -> rear == NULL) return TRUE;
    return FALSE;
}

void enqueue(BTQueue **pq, BTNode *btnode) {
    /* Pushes a BTNode to the rear of the queue.
    Arguments:
        - [BTQueue *pq] Adress of queue's pointer.
        - [BTNode *btnode] Pointer to binary tree node to enqueue.
    Returns: void */
    QNode *newn = (QNode *) malloc(sizeof(QNode));
    newn -> data = btnode;
    newn -> next = NULL;
    if (qisempty(*pq)) (*pq) -> front = newn;
    else ((*pq) -> rear) -> next = newn;
    (*pq) -> rear = newn;
}

BTNode *dequeue(BTQueue **pq) {
    /* Pops BTNode from the front of the queue.
    Arguments:
        - [BTQueue *pq] Adress of queue's pointer.
    Returns:
        - Pointer to binary tree node at the front of the queue.
    Raises error if the queue is empty. */
    if (qisempty(*pq)) {
        printf("Cannot dequeue from empty queue\n");
        return (BTNode *) NULL;
    }
    BTNode *btnode = ((*pq) -> front) -> data;
    QNode *newf = ((*pq) -> front) -> next;
    free((*pq) -> front);
    (*pq) -> front = newf;
    if (newf == NULL) (*pq) -> rear = NULL;
    return btnode;
}

void BT_BFT(BTNode *root) {
    /* Breadth first traversal function for binary trees (level order traversal).
    Arguments:
        - [BTNode *node] pointer to BST's root.
    Returns: void */
    if (!root) return ;
    BTQueue *q = newQueue();
    enqueue(&q, root);
    while (!qisempty(q)) {
        BTNode *node = dequeue(&q);
        if (!node) continue;
        enqueue(&q, node -> left);
        enqueue(&q, node -> right);
        printf("%d\n", node -> data);
    }
}

int isBSTutil(BTNode *node, int min_val, int max_val) {
    /* Checks if all of the nodes froma a tree are in an especific interval.
    Arguments:
        - [BTNode *node] Pointer to the root of the BT.
        - [int min_val] Minimum interval integer.
        - [int max_val] Maximum interval integer.
    Returns:
        - TRUE if is a BST.
        - FALSE if is not a BST. */
    if (!node) return TRUE;
    if (node -> data > min_val &&
        node -> data < max_val &&
        isBSTutil(node -> left, min_val, node -> data) &&
        isBSTutil(node -> right, node -> data, max_val)
        ) return TRUE;
    else return FALSE;
}

int isBST(BTNode *root) {
    /* Checks if a binary tree is a BST using isBTSutil().
    Arguments:
        - [BTNode *node] Pointer to the root of the BT.
    Returns:
        - TRUE if is a BST.
        - FALSE if is not a BST. */
    return isBSTutil(root, INT_MIN, INT_MAX);
}

BTNode *deleteBSTNode(BTNode *node, int value) {
    /* Deletes node with specified value if it exists (the root cannot be deleted).
    Arguments:
        - [BTNode *node] pointer to BST's root.
        - [int value] value of the deleted node.
    Returns:
        - Pointer to deleted node. */
    if (!node) {
        printf("Value %d is not in the BST.\n", value);
        return node;
    }
    else if (node -> data > value) node -> left = deleteBSTNode(node -> left, value);
    else if (node -> data < value) node -> right = deleteBSTNode(node -> right, value);
    else {
        if (!node -> right && !node -> left) {
            free(node);
            node = NULL;
        }
        else if (!node -> right) {
            BTNode *temp = node;
            node = node -> left;
            free(temp);
        }
        else if (!node -> left) {
            BTNode *temp = node;
            node = node -> right;
            free(temp);
        }
        else {
            BTNode *temp = BSTsearch(node, BSTmin(node -> right) -> data);
            node -> data = temp -> data;
            free(temp);
            temp = NULL;
        }
    }
    return node;
}
