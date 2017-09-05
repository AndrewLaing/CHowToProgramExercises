/*
 * Filename:	ex12_08.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        05/08/2017
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
int sumList( ListNodePtr );
int numberOfItemsInList( ListNodePtr );
float averageValueInList( ListNodePtr );


int main()
{
	ListNodePtr startPtr1 = NULL;
	int i;
    
    srand(time(NULL));

    for(i=0; i<25; i++)
        insert( &startPtr1, rand() % 101 );
        

    printf("First Linked List:\n");
	printList( startPtr1 );  
	
	printf("The sum of the items in the list is: %d\n", sumList( startPtr1) );
	printf("The number of items in the list is : %d\n", numberOfItemsInList( startPtr1) );
	printf("The average value in the list is   : %.2f\n", averageValueInList( startPtr1) );
	
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


/* Return the sum of the elements */
int sumList( ListNodePtr currentPtr )
{
	int result = 0;
	if( currentPtr == NULL )
    	printf( "List is empty.\n\n" );
    else 
	{
    	while( currentPtr != NULL) {
    		result += currentPtr->data;
    		currentPtr = currentPtr->nextPtr;
		}
	}
	
	return result;
}


/* Return the sum of the elements */
int numberOfItemsInList( ListNodePtr currentPtr )
{
	int result = 0;
	if( currentPtr == NULL )
    	printf( "List is empty.\n\n" );
    else 
	{
    	while( currentPtr != NULL) {
    		result++;
    		currentPtr = currentPtr->nextPtr;
		}
	}
	
	return result;
}


float averageValueInList( ListNodePtr currentPtr )
{
	int sum = sumList( currentPtr );
	float items = ( float )numberOfItemsInList( currentPtr );
	
	return sum/items;
	
	  
}
