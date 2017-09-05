/*
 * Filename:    ex12_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/08/2017
 */
 
#include <stdio.h>
#include <stdlib.h>

struct stackNode {
    int data;
    struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int getLine( char [], int );
void push( StackNodePtr *, int );
int pop( StackNodePtr * );
int isEmpty( StackNodePtr );


int main()
{
    StackNodePtr stackPtr = NULL;
    char line[30];
    
    printf("Enter a line of text: ");
    getLine(line, 30);
    
    /* Push the entered text onto the stack */
    int i=0;
    while(line[i]!='\0') {
        push( &stackPtr, line[i]);
        i++;
    }
    
    /* Pop the contents of the stack */
    while(!isEmpty( stackPtr ))
        printf("%c",pop( &stackPtr ) );
    
    printf("\n"); 

    return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}



/* Push value onto the stack */
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


/* Pop value from the stack */
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


/* Test if the list is empty */
int isEmpty( StackNodePtr topPtr )
{
    return topPtr==NULL;
}


