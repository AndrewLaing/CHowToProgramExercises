/*
 * Filename:	ex12_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/08/2017
 * Description: 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct listNode {
	int data;
	struct listNode *nextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void insert( ListNodePtr *, int );
int delete( ListNodePtr *, int );
int isEmpty( ListNodePtr );
void printList( ListNodePtr );
void printListBackwards( ListNodePtr );


int main()
{
	ListNodePtr startPtr1 = NULL;
	int i;
    
    srand(time(NULL));

    for(i=0; i<25; i++)
        insert( &startPtr1, rand() % 101 );
        

    printf("Forwards List:\n");
	printList( startPtr1 );  
	
    printf("\n\nBackwards List:\n");
	printListBackwards( startPtr1 );  
	return 0;
}


/* Insert value into the list in its sorted position */
void insert( ListNodePtr *sPtr, int value )
{
	ListNodePtr newPtr, previousPtr, currentPtr;
	
	newPtr = malloc( sizeof( ListNode ) );
	
	if( newPtr != NULL ) {
		newPtr->data = value;
		newPtr->nextPtr = NULL;
		
		previousPtr = NULL;
		currentPtr = *sPtr;
		
		while( currentPtr != NULL && value > currentPtr->data ) 
	    {
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		} 
		
		if( previousPtr == NULL ) {
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		}
		else {
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}
	}
	else
	    printf( "%c not inserted. No memory available.\n", value );
}


/* Delete the entry from the list corresponding to value */
int delete( ListNodePtr *sPtr, int value )
{
	ListNodePtr previousPtr, currentPtr, tempPtr;
	
	if( value == ( *sPtr )->data ) {
		tempPtr = *sPtr;             /* tempPtr holds the address to be freed */
		*sPtr = ( *sPtr )->nextPtr;
		free( tempPtr );
		return value;
	}
	else
	{
        previousPtr = *sPtr;
        currentPtr = ( *sPtr )->nextPtr;
        
        while( currentPtr != NULL && currentPtr->data != value ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
		}
		
		if( currentPtr != NULL) {
			tempPtr = currentPtr ;  /* tempPtr holds the address to be freed */
			previousPtr->nextPtr = currentPtr->nextPtr;
			free( tempPtr );
			return value;
		}
	}
	
	return 0;
}


/* Test if the list is empty */
int isEmpty( ListNodePtr sPtr )
{
	return sPtr==NULL;
}


/* Print the contents of the list from currentPtr */
void printList( ListNodePtr currentPtr )
{
	if( currentPtr == NULL )
    	printf( "List is empty.\n\n" );
    else 
	{
    	printf( "The list is:\n" );
    	
    	while( currentPtr != NULL) {
    		printf( "%d --> ", currentPtr->data );
    		currentPtr = currentPtr->nextPtr;
		}
		
		printf( "NULL\n\n" );
	}
}


/* Print the contents of the list backwards using recursion */
void printListBackwards( ListNodePtr currentPtr )
{
	ListNodePtr copyPtr = NULL;
	
	if( currentPtr == NULL ) {
		printf( "The list is:\n" );
		printf( "NULL" );
	    return;
    }
    else 
	{
		copyPtr = currentPtr;
		currentPtr = currentPtr->nextPtr;
		printListBackwards( currentPtr );
    	printf( " --> %d", copyPtr->data );
	}
}


