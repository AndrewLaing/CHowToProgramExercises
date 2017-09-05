/*
 * Filename:    queueImplementation.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/08/2017
 * Description: Queue implementation using pointers.
 */
 
#include <stdio.h>
#include <stdlib.h>

struct queueNode {
    char data;
    struct queueNode *nextPtr;
};

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

void enqueue( QueueNodePtr *, QueueNodePtr *, char );
char dequeue( QueueNodePtr *, QueueNodePtr * );
int isEmpty( QueueNodePtr );
void printQueue( QueueNodePtr );
void instructions( void );


int main()
{
    QueueNodePtr headPtr = NULL, tailPtr = NULL;
    int choice;
    char item;
    
    instructions();
    printf( "? " );
    scanf( "%d", &choice );
    
    while( choice!=3 )
    {
        switch( choice )
        {
            case 1:
                printf( "Enter a character: " );
                scanf( "\n%c", &item );
                enqueue( &headPtr, &tailPtr, item );
                printQueue( headPtr );  
                break;
            case 2:
                if( !isEmpty( headPtr ) ) {
                    item = dequeue(&headPtr, &tailPtr );
                    printf( "%c has been dequeued.\n", item );
                }

                printQueue( headPtr );  
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


/* Add an item onto the queue */
void enqueue( QueueNodePtr *headPtr,  QueueNodePtr *tailPtr, char value )
{
    QueueNodePtr newPtr;
    
    newPtr = malloc( sizeof( QueueNode ) ); /* Now points to a place in memory*/
    
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


/* Remove an item from the queue */
char dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr )
{
    char value; 
    QueueNodePtr tempPtr;
    
    value = (*headPtr)->data;   
    tempPtr = *headPtr;

    *headPtr = (*headPtr)->nextPtr;
    
    if( *headPtr == NULL)
        *tailPtr = NULL;
    
    free( tempPtr );
    
    return value;
}


/* Test if the queue is empty */
int isEmpty( QueueNodePtr headPtr )
{
    return headPtr==NULL;
}


/* Print the contents of the queue from currentPtr */
void printQueue( QueueNodePtr currentPtr )
{
    if( currentPtr == NULL )
        printf( "Queue is empty.\n\n" );
    else 
    {
        printf( "The queue is:\n" );
        
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
            "    1 to add an item to the queue.\n"
            "    2 to remove an item from the queue.\n"
            "    3 to end.\n" );
}

