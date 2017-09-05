/*
 * Filename:    ex12_21.c
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
int *searchList( ListNodePtr, int );


int main()
{
    ListNodePtr startPtr1 = NULL;
    int i;
    
    srand(time(NULL));

    for(i=0; i<25; i++)
        insert( &startPtr1, rand() % 101 );
        

    printf("Forwards List:\n");
    printList( startPtr1 ); 
    
    int query, *result;
    printf("Enter value to search for: ");
    scanf("%d", &query);
    fflush(stdin);
    result = searchList(startPtr1, query );
    
    
    if(result == NULL)
        printf("%d NOT found\n", query);
    else
    {
        printf("%d WAS found\n", *result);  
        
        /* Now this value can be altered */
        *result = 99;
        printf("\n\nChanging %d to 99:\n", query);
        printList( startPtr1 ); 
        printf("\nThis list probably needs sorting again.\n");          
    }

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


/* If the current node contains the query value
 * return a pointer to it, if the query value is not found
 * when NULL is reached, return NULL */
int *searchList( ListNodePtr currentPtr, int query )
{
    int *result = NULL;
    
    if( currentPtr == NULL ) {
        return NULL;
    }
    else 
    {
        if( currentPtr->data == query ) {
            result = &currentPtr->data;
        }
        else
            result = searchList( currentPtr->nextPtr, query );
    }
    return result;
}


