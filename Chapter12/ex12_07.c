/*
 * Filename:	ex12_07.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        05/08/2017
 * Description: Merge sorted Linked Lists containing unique values.
 */
 
#include <stdio.h>
#include <stdlib.h>

struct listNode {
	int data;
	struct listNode *nextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void merge( ListNodePtr *firstPtr, ListNodePtr *secondPtr );

void insert( ListNodePtr *, int );
int delete( ListNodePtr *, int );
int isEmpty( ListNodePtr );
void printList( ListNodePtr );


int main()
{
	ListNodePtr startPtr1 = NULL, startPtr2 = NULL;
	int i;
    

    for(i=0; i<20; i = i+2)
        insert( &startPtr1, i );
        
    for(i=1; i<20; i = i+2)
        insert( &startPtr2, i );

    printf("First Linked List:\n");
	printList( startPtr1 );  

    printf("\nSecond Linked List:\n");
	printList( startPtr2 );  
	

	merge( &startPtr1, &startPtr2 );
	
    printf("\nFirst Linked List after mergeing second:\n");
	printList( startPtr1 );  

	return 0;
}



void merge( ListNodePtr *firstPtr, ListNodePtr *secondPtr )
{
	    ListNodePtr headPtr, tailPtr;
	    
	    headPtr = *firstPtr;
    	tailPtr = *secondPtr;		

		while( tailPtr != NULL ) 
	    {
	    	insert( &headPtr, tailPtr->data );
	    	tailPtr = tailPtr->nextPtr;
		} 
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

