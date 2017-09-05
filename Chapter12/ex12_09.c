/*
 * Filename:    ex12_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        05/08/2017
 */
 
#include <stdio.h>
#include <stdlib.h>

struct listNode {
    char data;
    struct listNode *nextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void makeReverseCopy(ListNodePtr, ListNodePtr * );
void insert( ListNodePtr *, char );
char delete( ListNodePtr *, char );
int isEmpty( ListNodePtr );
void printList( ListNodePtr );
int numberOfItemsInList( ListNodePtr );


int main()
{
    ListNodePtr startPtr1 = NULL, startPtr2 = NULL;
    int i;
    
    char word1[] = "ThisString";

    for(i=0; i<10; i++)
        insert( &startPtr1, word1[i] );
        
    printf("First Linked List:\n");
    printList( startPtr1 );
    
    makeReverseCopy( startPtr1, &startPtr2 ); 
    printf("Reversed Linked List:\n");
    printList( startPtr2 );  

    return 0;
}


void makeReverseCopy( ListNodePtr sPtr, ListNodePtr *reversedPtr )
{
    ListNodePtr currentPtr, addMePtr;
    
    currentPtr = sPtr;
    addMePtr = sPtr;
    
    if( currentPtr == NULL )
        return;
    else {
        currentPtr = currentPtr->nextPtr;
        makeReverseCopy( currentPtr, reversedPtr );
    }

    if(addMePtr != NULL)
        insert( reversedPtr, addMePtr->data );
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



