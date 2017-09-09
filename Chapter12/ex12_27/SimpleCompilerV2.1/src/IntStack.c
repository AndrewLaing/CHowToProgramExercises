/*
 * Filename:    IntStack.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/08/2017.
 * Description: A stack implementation to store integers.
 */

#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"


/**
 * The function push pushes the integer info to the top of the stack referenced
 * by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 * @param info A number to push to the top of the stack.
 */
void push( StackNodePtr *topPtr, int info )
{
    StackNodePtr newPtr;
    
    newPtr = malloc( sizeof( StackNode ) ); /* Now points to a place in memory*/
    
    if( newPtr != NULL ) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else
        printf( "%c not inserted. No memory available.\n", info );
}


/**
 * The function pop pops the integer stored on the the top of the stack 
 * referenced by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 * @return The integer stored on the the top of the stack 
 */
int pop( StackNodePtr *topPtr )
{
    StackNodePtr tempPtr;
    int popValue;
    
    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free( tempPtr );
    
    return popValue;
}


/**
 * The function stackTop returns the integer stored on the the top of the stack 
 * referenced by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 * @return The integer stored on the the top of the stack 
 */
int stackTop( StackNodePtr topPtr )
{
    int topValue;
    
    topValue = topPtr->data;
    
    return topValue;    
}


/**
 * The function isEmpty tests whether the stack referenced by the 
 * pointer topPtr is empty or not.
 * @param topPtr A pointer to the top of a stack.
 * @return 1 if the stack is empty, otherwise 0. 
 */
int isEmpty( StackNodePtr topPtr )
{
    return topPtr==NULL;
}


/**
 * The function printStack prints out, in an easy to read format, the
 * contents of the stack referenced by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 */
void printStack( StackNodePtr currentPtr )
{
    if( currentPtr == NULL )
        printf( "The stack is empty.\n\n" );
    else 
    {
        printf( "The stack is:\n" );
        
        while( currentPtr != NULL) {
            printf( "%d --> ", currentPtr->data );
            currentPtr = currentPtr->nextPtr;
        }
        
        printf( "NULL\n\n" );
    }
}

