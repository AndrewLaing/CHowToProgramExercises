/*
 * Filename:	stackImplementation.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/08/2017
 * Description: Stack implementation using pointers.
 */
 
#include <stdio.h>
#include <stdlib.h>

struct stackNode {
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void push( StackNodePtr *, int );
int pop( StackNodePtr * );
int isEmpty( StackNodePtr );
void printStack( StackNodePtr );
void instructions( void );


int main()
{
	StackNodePtr stackPtr = NULL;
	int choice;
	int value;
	
	instructions();
	printf( "? " );
	scanf( "%d", &choice );
	
	while( choice!=3 )
	{
		switch( choice )
		{
			case 1:
				printf( "Enter a number: " );
	            scanf( "%d", &value );
	            push( &stackPtr, value );
				printStack( stackPtr );  
				break;
			case 2:
				if( !isEmpty( stackPtr ) ) 
    				printf( "The popped value is %d.\n ",
					        pop( &stackPtr ) );
					
				printStack( stackPtr );  
				break;
			default:
				printf( "Invalid choice.\n\n" );
				instructions(); 
				break;
		}
		
		printf( "? " );
       	scanf( "%d", &choice );
	}
	
	printf( "End of run.\n" );

	return 0;
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


/* Print the contents of the stack from currentPtr */
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


/* Display the menu */
void instructions( void )
{
	printf( "Enter your choice:\n"
		    "    1 to push a value on the stack.\n"
		    "    2 to pop a value off the stack.\n"
		    "    3 to end.\n" );
}

