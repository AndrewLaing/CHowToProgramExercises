/*
 * Filename:    ex14_08.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/10/2017
 * Description: reverse file using a stack
 */
 
#include <stdio.h>
#include <stdlib.h>     /* malloc */


struct stackNode {
    char data;
    struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void push( StackNodePtr *, char );
char pop( StackNodePtr * );
int isEmpty( StackNodePtr );


int main( int argc, char *argv[] )
{
    StackNodePtr stackPtr = NULL;
    FILE *inFilePtr, *outFilePtr;
    char c;
    
    if( argc != 3 ) 
    {
        printf("Usage: reverse infile outfile\n");
        exit(1);
    }
    else 
    {
        /* Push the contents of the infile 1 char at a time to the stack */
        if( (inFilePtr = fopen( argv[1], "r" ) ) != NULL  )
            while( (c = fgetc( inFilePtr ) ) != EOF )
                push(&stackPtr, c);
        else {
            printf("File %s could not be opened\n", argv[1]);
            exit(1);
        }

        /* pop contents of stack to outfile, reversing infile */
        if( (outFilePtr = fopen( argv[2], "w" ) ) != NULL  )
            while( !isEmpty( stackPtr ) )
                fputc( pop( &stackPtr ), outFilePtr );
        else {
            fclose(inFilePtr);
            printf("File %s could not be opened\n", argv[2]);
            exit(1);
        }  
    }   
    
    fclose(inFilePtr);
    fclose(outFilePtr);
    
    return 0;
}


/* Push value onto the stack */
void push( StackNodePtr *topPtr, char info )
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
char pop( StackNodePtr *topPtr )
{
    StackNodePtr tempPtr;
    char popValue;
    
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



