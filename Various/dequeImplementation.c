/*
 * Filename:    dequeImplementation.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/08/2017
 * Description: Deque implementation using pointers.
 */
 
#include <stdio.h>
#include <stdlib.h>

struct dequeNode {
    char data;
    struct dequeNode *nextPtr;
};

typedef struct dequeNode DequeNode;
typedef DequeNode *DequeNodePtr;

void push_front( DequeNodePtr *, DequeNodePtr *, char );
void push_back( DequeNodePtr *, DequeNodePtr *, char );
char pop_front( DequeNodePtr *, DequeNodePtr * );
char pop_back( DequeNodePtr *, DequeNodePtr * );
char front( DequeNodePtr * );
char back( DequeNodePtr * );

int isEmpty( DequeNodePtr );
void printDeque( DequeNodePtr );
void instructions( void );


int main()
{
    DequeNodePtr headPtr = NULL, tailPtr = NULL;
    int choice;
    char item;
    
    instructions();
    printf( "? " );
    scanf( "%d", &choice );
    
    while( choice!=7 )
    {
        switch( choice )
        {
            case 1:
                printf( "Enter a character: " );
                scanf( "\n%c", &item );
                push_front( &headPtr, &tailPtr, item );
                printDeque( headPtr );  
                break;
            case 2:
                printf( "Enter a character: " );
                scanf( "\n%c", &item );
                push_back( &headPtr, &tailPtr, item );
                printDeque( headPtr );  
                break;
            case 3:
                if( !isEmpty( headPtr ) ) {
                    item = pop_front(&headPtr, &tailPtr );
                    printf( "%c has been popped from the front of the deque.\n", item );
                }

                printDeque( headPtr );  
                break;
            case 4:
                if( !isEmpty( headPtr ) ) {
                    item = pop_back(&headPtr, &tailPtr );
                    printf( "%c has been popped from the back of the deque.\n", item );
                }

                printDeque( headPtr );  
                break;
            case 5:
                if( !isEmpty( headPtr ) ) {
                    item = front(&headPtr);
                    printf( "%c is the item at the front of the deque.\n", item );
                }

                printDeque( headPtr );  
                break;
            case 6:
                if( !isEmpty( tailPtr ) ) {
                    item = back(&tailPtr);
                    printf( "%c is the item at the back of the deque.\n", item );
                }

                printDeque( headPtr );
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


/* Push value to the front of the deque */
void push_front( DequeNodePtr *headPtr, DequeNodePtr *tailPtr, char value )
{
    DequeNodePtr newPtr;
    
    newPtr = malloc( sizeof( DequeNode ) ); /* Now points to a place in memory*/
    
    if( newPtr != NULL ) 
    {
        newPtr->data = value;
        newPtr->nextPtr = *headPtr;
        
        if( isEmpty( *headPtr ) ) {
            *tailPtr = newPtr;
        }
        
        *headPtr = newPtr;
    }
    else
        printf( "%c not inserted. No memory available.\n", value );
}


/* Add an item onto the end of the deque */
void push_back( DequeNodePtr *headPtr,  DequeNodePtr *tailPtr, char value )
{
    DequeNodePtr newPtr;
    
    newPtr = malloc( sizeof( DequeNode ) ); /* Now points to a place in memory*/
    
    if( newPtr != NULL ) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        if( isEmpty( *headPtr ) )
            *headPtr = newPtr;
        else
            ( *tailPtr )->nextPtr = newPtr;
        
        *tailPtr = newPtr;
    }
    else
        printf( "%c not inserted. No memory available.\n", value );
}


/* Remove an item from the back of the deque */
char pop_front( DequeNodePtr *headPtr, DequeNodePtr *tailPtr )
{
    char value; 
    DequeNodePtr tempPtr;
    
    value = (*headPtr)->data;   
    tempPtr = *headPtr;

    *headPtr = (*headPtr)->nextPtr;
    
    if( *headPtr == NULL)
        *tailPtr = NULL;
    
    free( tempPtr );
    
    return value;
}


/* Pop value from the back of the deque */
char pop_back( DequeNodePtr *headPtr, DequeNodePtr *tailPtr )
{
    DequeNodePtr tempPtr, previousPtr, currentPtr;
    char value;
    
    if(headPtr == tailPtr)
    {
        value   = (*headPtr)->data; 
        tempPtr = *headPtr;
        *headPtr = NULL;
        *tailPtr = NULL;
        free( tempPtr );
    }
    else
    {
        previousPtr = *headPtr;
        currentPtr = ( *headPtr )->nextPtr;
        
        /* Find the previous node before the tail */
        while( currentPtr->nextPtr != NULL ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
        
        /* Remove the tail and set the node before it as the new tail */
        previousPtr->nextPtr = NULL;
        *tailPtr = previousPtr;
        free( currentPtr );
    }
    
    return value;
}


char front( DequeNodePtr *headPtr )
{
    char value;
    value = (*headPtr)->data;   
    return value;
}


char back( DequeNodePtr *tailPtr )
{
    char value;
    value = (*tailPtr)->data;   
    return value;
}


/* Test if the deque is empty */
int isEmpty( DequeNodePtr headPtr )
{
    return headPtr==NULL;
}


/* Print the contents of the queue from currentPtr */
void printDeque( DequeNodePtr currentPtr )
{
    if( currentPtr == NULL )
        printf( "Deque is empty.\n\n" );
    else 
    {
        printf( "The deque is:\n" );
        
        while( currentPtr != NULL) {
            printf( "%c --> ", currentPtr->data );
            currentPtr = currentPtr->nextPtr;
        }
        
        printf( "NULL\n\n" );
    }
}


/* Display the menu */
void instructions( void )
{
    printf( "Enter your choice:\n"
            "    1 to push an item to the front of the deque.\n"
            "    2 to push an item to the back of the deque.\n"         
            "    3 to pop an item from the front of the deque.\n"
            "    4 to pop an item from the back of the deque.\n"
            "    5 to peek at the item at the front of the deque.\n"
            "    6 to peek at the item at the back of the deque.\n"
            "    7 to end.\n" );
}

