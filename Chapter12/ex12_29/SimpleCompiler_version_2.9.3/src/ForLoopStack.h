/*
 * Filename:    ForLoopStack.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/09/2017.
 * Description: A stack implementation to store the variables needed to
 *              implement the FOR-NEXT loop structure.
 */

#ifndef FORLOOP_STACK_H
#define FORLOOP_STACK_H

#include <stdio.h>
#include <stdlib.h>

struct forLoopNode {
    int addressOfCountVariable;
    int addressOfStepValue;
    int startOfLoopAddress;
    int jmpGTAddress;
    struct forLoopNode *nextPtr;
};

typedef struct forLoopNode ForLoopNode;
typedef ForLoopNode *ForLoopNodePtr;

void pushFL( ForLoopNodePtr *, int, int, int, int );
void popFL( ForLoopNodePtr *, int[] );
int isEmptyFL( ForLoopNodePtr );
void printStackFL( ForLoopNodePtr );

#endif

