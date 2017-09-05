/*
 * Filename:	ex12_06.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        05/08/2017
 * Description: Concatenate Unsorted Linked Lists.
 */
 
#include <stdio.h>
#include <stdlib.h>

struct listNode {
	char data;
	struct listNode *nextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void concatenate1( ListNodePtr *, ListNodePtr * );
void concatenate2( ListNodePtr *firstPtr, ListNodePtr *secondPtr );

void insert( ListNodePtr *, char );
char delete( ListNodePtr *, char );
int isEmpty( ListNodePtr );
void printList( ListNodePtr );


int main()
{
	ListNodePtr startPtr1 = NULL, startPtr2 = NULL;
	int i;
    
    char word1[] = "Greatie";
    char word2[] = "Market";

    for(i=0; i<7; i++)
        insert( &startPtr1, word1[i] );
        
    for(i=0; i<6; i++)
        insert( &startPtr2, word2[i] );

    printf("First Linked List:\n");
	printList( startPtr1 );  

    printf("\nSecond Linked List:\n");
	printList( startPtr2 );  
	
	
//	/* FIRST VERSION OF CONCATENATE - The Bad One */
//	
//	/* Using concatenate1 can result in undefined behaviour */
//	concatenate1( &startPtr1, &startPtr2 );
//	
//    printf("\nFirst Linked List after concatenating second:\n");
//	printList( startPtr1 );  
//	
//	/* This is a simple demonstration.
//	 * A more complex version would change the address at *startPtr to
//	 * point to a different block of memory with, for example, shellcode */
//	delete( &startPtr2, 'M' );
//	
//    printf("\nFirst Linked List after deleting first character of second list:\n");
//	printList( startPtr1 ); 
	
	/* SECOND VERSION OF CONCATENATE - The Safer One */
	
	/* Using concatenate1 can result in undefined behaviour */
	concatenate2( &startPtr1, &startPtr2 );
	
    printf("\nFirst Linked List after concatenating second:\n");
	printList( startPtr1 );  

	return 0;
}


/* There are very good reasons not to use this method!!!
 * Note that if the first element of the second list is deleted afterweards
 * elsewhere then this could result in undefined behaviour because firstlist
 * still contains a reference to the memory address which used to exist at
 * the beginning of the second list ( leaving the remainder of the list
 * INACCESSIBLE ) */
void concatenate1( ListNodePtr *firstPtr, ListNodePtr *secondPtr )
{
	ListNodePtr currentPtr;
	
	if( isEmpty( *firstPtr ) ) 
	{
		if( isEmpty( *secondPtr ) )
    	    return;
    	else 
    	    *firstPtr = *secondPtr;
	}
	else if( isEmpty( *secondPtr ) )
		return;
	else
	{
		currentPtr = *firstPtr;
		
		/* find end of first list */
		while( currentPtr->nextPtr != NULL ) 
	    {
			currentPtr = currentPtr->nextPtr;
		} 

		currentPtr->nextPtr = *secondPtr;
	}  
}


void concatenate2( ListNodePtr *firstPtr, ListNodePtr *secondPtr )
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
void insert( ListNodePtr *sPtr, char value )
{
	ListNodePtr newPtr, previousPtr, currentPtr;
	
	newPtr = malloc( sizeof( ListNode ) );
	
	if( newPtr != NULL ) {
		newPtr->data = value;
		newPtr->nextPtr = NULL;
		
		previousPtr = NULL;
		currentPtr = *sPtr;
		
		while( currentPtr != NULL 
		      /*&& value > currentPtr->data*/ /* remove comment to sort lists */
			 ) 
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
char delete( ListNodePtr *sPtr, char value )
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
    		printf( "%c --> ", currentPtr->data );
    		currentPtr = currentPtr->nextPtr;
		}
		
		printf( "NULL\n\n" );
	}
}


