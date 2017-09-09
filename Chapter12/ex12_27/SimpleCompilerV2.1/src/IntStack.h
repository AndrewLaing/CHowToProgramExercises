/*
 * Filename:    IntStack.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/08/2017.
 * Description: A stack implementation to store integers.
 */

#ifndef INT_STACK_H
#define INT_STACK_H

struct stackNode { 
    int data;
    struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void push( StackNodePtr *, int );
int pop( StackNodePtr * );
int stackTop( StackNodePtr );
int isEmpty( StackNodePtr );
void printStack( StackNodePtr );


#endif

