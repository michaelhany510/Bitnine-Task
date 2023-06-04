// Including needed libraries
#include "stdio.h"
#include <stdlib.h>



// Defining the datatype to hold types of operation
typedef enum TypeTag {
    ADD, SUB, MUL, DIV, FIBO
} TypeTag;

// Defining the node struct to be used
typedef struct Node {
    TypeTag type;
    int left_value;
    int right_value;
    long result;
} Node;

//defining the type of the function pointer
typedef Node *(*functionPointer)(int,int);


//this function encapsulate the common code between the 4 types of operations.
Node *makeNode(int left_value, int right_value){
    Node *node = (Node*)malloc(sizeof(Node));       // dynamically allocate memory for the Node struct
    node->left_value = left_value;
    node->right_value = right_value;
    return node;
}

// Those Functions Create a node, then assigns the chosen operation to the type of the node.
// The node also holds values of the 2 integer numbers that the operation will be applied on.
// Then the function returns the node to the main function or application
Node *makeAddNode(int left_value, int right_value){
    Node *node = makeNode(left_value,right_value); 
    node->type = ADD;
    return node;
}

Node *makeSubNode(int left_value, int right_value){
    Node *node = makeNode(left_value,right_value);
    node->type = SUB;
    return node;
}

Node *makeMulNode(int left_value, int right_value){
    Node *node = makeNode(left_value,right_value);
    node->type = MUL;
    return node;
}

Node *makeDivNode(int left_value, int right_value){
    Node *node = makeNode(left_value,right_value);
    node->type = DIV;
    return node;
}

Node *makeFiboNode(int n, int _){
    Node *node = makeNode(n,_);
    node->type = FIBO;
    return node;
}

// Here is a global array of pointers that holds the previous functions locations.
// This array shall be used by the makeFunc function to choose which operation to do.
// Declaration of the array outside the function to prevent multiple declarations of the exact same array at runtime.
functionPointer functions[5] = {&makeAddNode, &makeSubNode, &makeMulNode, &makeDivNode, &makeFiboNode};

// This function chooses which type of function to return to the main function.

functionPointer makeFunc(TypeTag type){
    return functions[type];
}

// This function calculates value of the node based on the type of operation it holds.
// Then returns the calculated value in a long datatype.
long calc(Node *node){
    // Choose the operation based on the node type
    switch (node->type) {
        case ADD:
            node->result = node->left_value + node->right_value;
            break;
        case SUB:
            node->result = node->left_value - node->right_value;
            break;
        case MUL:
            node->result = node->left_value * node->right_value;
            break;
        case DIV:
            node->result = node->left_value / node->right_value;
            break;
        case FIBO:
            if (node->left_value < 2){
                node->result = node->left_value;
                break;
            }
//          Creating array to calculate Fibonacci using dynamic programming
            long fibo_array[node->left_value + 1];
            for (int i = 0; i < 2; i++){
                fibo_array[i] = i;
            }
            for (int i = 2 ; i <= node->left_value; i++){
                fibo_array[i] = fibo_array[i-2] + fibo_array[i-1];
            }
            // Result of fibonacci is the value of last number in the array
            node->result = fibo_array[node->left_value];
            break;
    }
    return node->result;
}

int main() {
    Node *add = (*makeFunc(ADD))(10, 6);
    Node *mul = (*makeFunc(MUL))(5, 4);
    Node *sub = (*makeFunc(SUB))(calc(mul), calc(add));
    Node *fibo = (*makeFunc(FIBO))(calc(sub), 0);

    printf("add : %ld\n", calc(add));
    printf("mul : %ld\n", calc(mul));
    printf("sub : %ld\n", calc(sub));
    printf("fibo : %ld\n", calc(fibo));

    return 0;
}
