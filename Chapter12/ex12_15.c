/*
 * Filename:    ex12_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        08/08/2017
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct queueNode {
    int customer;
    struct queueNode *nextPtr;
};

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

void enqueue( QueueNodePtr *, QueueNodePtr *, int );
int dequeue( QueueNodePtr *, QueueNodePtr * );
int isEmpty( QueueNodePtr );
void printQueue( QueueNodePtr );
int getQueueLength( QueueNodePtr );


int main()
{
    srand(time(NULL));
    
    QueueNodePtr headPtr = NULL, tailPtr = NULL;
    
    int arrivalIntervalMax = 4;
    
    int minutes;
    int customerDue;
    int customerServiceTime;
    int currentCustomerArrival;
    
    int temp;
    int longestQueue = 0;
    int longestWait = 0;
    
    
    customerDue =  ( rand() % arrivalIntervalMax ) + 1;
    customerServiceTime =  ( rand() % 4 ) + 1 + customerDue;
    enqueue( &headPtr, &tailPtr, customerDue );
    
    for( minutes=customerDue; minutes<=720; minutes++ )
    {
        temp = getQueueLength( headPtr );
        if( temp > longestQueue )
            longestQueue = temp;
 
        if( minutes == customerDue )
        {
            printf("A customer arrived at %d\n", minutes);
            enqueue( &headPtr, &tailPtr, minutes ); 
            
            customerDue = ( rand() % arrivalIntervalMax ) + 1 + minutes;
            
            if( currentCustomerArrival == 0 ) {
                customerServiceTime =  ( rand() % 4 ) + 1 + minutes;
                currentCustomerArrival = minutes;
            }
                
        }
        if( minutes == customerServiceTime )
        {
            if( ( customerServiceTime - currentCustomerArrival ) > longestWait )
                longestWait = customerServiceTime - currentCustomerArrival;
                
            printf("The customer served at %d arrived at %d\n", minutes, currentCustomerArrival);
            if( !isEmpty( headPtr ) ) {
                currentCustomerArrival = dequeue( &headPtr, &tailPtr );
                customerServiceTime =  ( rand() % 4 ) + 1 + minutes;
            }
            else
                currentCustomerArrival = 0;
        }
    }
    
    printf("\nThe maximum number of customers at any one time was %d people.\n", longestQueue );
    printf("The longest wait any 1 customer experienced was %d minutes.\n", longestWait );
    printf("The number of customers still waiting to be served at closing time was %d\n", getQueueLength( headPtr ) );

    return 0;
}


/* Add an item onto the queue */
void enqueue( QueueNodePtr *headPtr,  QueueNodePtr *tailPtr, int value )
{
    QueueNodePtr newPtr;
    
    newPtr = malloc( sizeof( QueueNode ) ); /* Now points to a place in memory*/
    
    if( newPtr != NULL ) {
        newPtr->customer = value;
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
int dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr )
{
    int value;  
    QueueNodePtr tempPtr;
    
    value = (*headPtr)->customer;   
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
            printf( "%d --> ", currentPtr->customer );
            currentPtr = currentPtr->nextPtr;
        }
        
        printf( "NULL\n\n" );
    }
}


/* Return the length of the queue from currentPtr */
int getQueueLength( QueueNodePtr currentPtr )
{
    int queueLength = 0;
    if( currentPtr != NULL )
    {       
        while( currentPtr != NULL) {
            queueLength++;
            currentPtr = currentPtr->nextPtr;
        }
    }
    
    return queueLength;
}

