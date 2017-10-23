/*
 * Filename:    ForLoopStack.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/09/2017.
 * Description: A stack implementation to store the variables needed to
 *              implement the FOR-NEXT loop structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include "ForLoopStack.h"


/**
 * The function push pushes the integer info to the top of the stack referenced
 * by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 * @param acv The address of a For loop count variable to push to the 
               top of the stack.
 * @param asv The address of a For loop step variable to push to the 
               top of the stack.
 * @param sla The address of the start of the For loop to push to the 
               top of the stack.
 * @param jga The address of where the doJMPGTInstruction was added.      
 */
void pushFL( ForLoopNodePtr *topPtr, int acv, int asv, int sla, int jga )
{
    ForLoopNodePtr newPtr;
    
    newPtr = malloc( sizeof( ForLoopNode ) ); /* Now points to a place in memory*/
    
    if( newPtr != NULL ) {
        newPtr->addressOfCountVariable = acv;
        newPtr->addressOfStepValue     = asv;
        newPtr->startOfLoopAddress     = sla;
        newPtr->jmpGTAddress           = jga;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else
        printf( "No memory available to create new for loop node.\n");
}


/**
 * The function pop pops the integer stored on the the top of the stack 
 * referenced by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 * @param contents An array to contain the for loop values popped from the
 *        top of the stack.
 */
void popFL( ForLoopNodePtr *topPtr, int contents[] )
{
    ForLoopNodePtr tempPtr;
    
    tempPtr = *topPtr;
    contents[0] = (*topPtr)->addressOfCountVariable;
    contents[1] = (*topPtr)->addressOfStepValue;
    contents[2] = (*topPtr)->startOfLoopAddress;
    contents[3] = (*topPtr)->jmpGTAddress;
    
    *topPtr = (*topPtr)->nextPtr;
    free( tempPtr );
}


/**
 * The function isEmpty tests whether the stack referenced by the 
 * pointer topPtr is empty or not.
 * @param topPtr A pointer to the top of a stack.
 * @return 1 if the stack is empty, otherwise 0. 
 */
int isEmptyFL( ForLoopNodePtr topPtr )
{
    return topPtr==NULL;
}


/**
 * The function printStack prints out, in an easy to read format, the
 * contents of the stack referenced by the pointer topPtr.
 * @param topPtr A pointer to the top of a stack.
 */
void printStackFL( ForLoopNodePtr currentPtr )
{
    if( currentPtr == NULL )
        printf( "The stack is empty.\n\n" );
    else 
    {
        printf( "The stack is:\n" );
        
        while( currentPtr != NULL) {
            printf( " %d %d %d %d -->\n", currentPtr->addressOfCountVariable, 
                                    currentPtr->addressOfStepValue,
                                    currentPtr->startOfLoopAddress,
                                    currentPtr->jmpGTAddress );
            currentPtr = currentPtr->nextPtr;
        }
        
        printf( "NULL\n\n" );
    }
}

