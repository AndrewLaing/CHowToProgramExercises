/*
 * Filename:	ex12_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/08/2017
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct treeNode {
	struct treeNode *leftPtr;
	int data;
	struct treeNode *rightPtr;
};


typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;


struct queueNode {
	TreeNodePtr data;
	struct queueNode *nextPtr;
};


typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

void insertNode( TreeNodePtr *, int );
void inOrder( TreeNodePtr );
void preOrder( TreeNodePtr );
void postOrder( TreeNodePtr );
void levelOrder( TreeNodePtr );

void enqueue( QueueNodePtr *, QueueNodePtr *, TreeNodePtr );
TreeNodePtr dequeue( QueueNodePtr *, QueueNodePtr * );
int isEmpty( QueueNodePtr );


TreeNodePtr deleteNode( TreeNodePtr, int );
TreeNodePtr findMin( TreeNodePtr );


int main()
{
    int i, item;
    TreeNodePtr rootPtr = NULL;
    
    srand(time(NULL));

	
	for(i=1; i<20; i++) {
		item = rand() % 15;
		insertNode( &rootPtr, item );
	}    
	
	/* Traverse the tree preOrder */
    printf("The preOrder traversal is:\n");
    preOrder( rootPtr );
    
	/* Traverse the tree inOrder */
    printf("\n\nThe inOrder traversal is:\n");
    inOrder( rootPtr );
    
	/* Traverse the tree postOrder */
    printf("\n\nThe postOrder traversal is:\n");
    postOrder( rootPtr );
    
	/* Traverse the tree levelOrder */
    printf("\n\nThe levelOrder traversal is:\n");
    levelOrder( rootPtr );
    
    
    
    int valToDelete;
	printf("\n\nEnter value to delete ");
	scanf("%d", &valToDelete);
	fflush(stdin);
	
	rootPtr = deleteNode( rootPtr, valToDelete );

	/* Traverse the tree preOrder */
    printf("\nThe preOrder traversal after deletion is:\n");
    preOrder( rootPtr );
    
	/* Traverse the tree inOrder */
    printf("\n\nThe inOrder traversal after deletion is:\n");
    inOrder( rootPtr );
    
	/* Traverse the tree postOrder */
    printf("\n\nThe postOrder traversal after deletion is:\n");
    postOrder( rootPtr );

	/* Traverse the tree levelOrder */
    printf("\n\nThe levelOrder traversal is:\n");
    levelOrder( rootPtr );
    
	return 0;
}


void levelOrder( TreeNodePtr treePtr )
{
	QueueNodePtr headPtr = NULL, tailPtr = NULL;
	TreeNodePtr temp;
	
	if( treePtr == NULL ) 
	    return;

	enqueue( &headPtr, &tailPtr, treePtr );
	
	while(!isEmpty( headPtr ) )
	{
		temp = dequeue( &headPtr, &tailPtr );
		printf( "%3d", temp->data );
		if( temp->leftPtr != NULL )
		    enqueue( &headPtr, &tailPtr, temp->leftPtr );
		if( temp->rightPtr != NULL )
		    enqueue( &headPtr, &tailPtr, temp->rightPtr );
	} 
}


/* Insert value into the list in its sorted position */
void insertNode( TreeNodePtr *treePtr, int value )
{
    if( *treePtr == NULL )
    {
    	*treePtr = malloc( sizeof( TreeNode ) );
    	
    	if(*treePtr != NULL) {
    		( *treePtr )->data = value;
    		( *treePtr )->leftPtr = NULL;
    		( *treePtr )->rightPtr = NULL;
		}
    	else
	        printf( "%c not inserted. No memory available.\n", value );
	}
    else {
    	if( value < (*treePtr)->data )
    	    insertNode( &( ( *treePtr )->leftPtr ), value );
    	else if( value > (*treePtr)->data )
    	    insertNode( &( ( *treePtr )->rightPtr ), value );
	}
	
}


TreeNodePtr deleteNode( TreeNodePtr treePtr, int value )
{
	if( treePtr == NULL )
        return NULL;
    else if( value < treePtr->data ) 
	    treePtr->leftPtr = deleteNode( treePtr->leftPtr, value );
	else if( value > treePtr->data )
    	treePtr->rightPtr = deleteNode( treePtr->rightPtr, value );
    else 
	{
		// Case 1: No children
		if( treePtr->leftPtr == NULL && treePtr->rightPtr == NULL ){
			free(treePtr);
			treePtr = NULL;    /* because the parent still holds this address */
		}
		// Case 2: One child
		else if( treePtr->leftPtr == NULL )
		{
			/* store address of node being deleted */
			TreeNodePtr temp = treePtr;
			treePtr = treePtr->rightPtr;
			free(temp);   /* free the memory space formerly allocated to treePtr*/
		}
		else if( treePtr->rightPtr == NULL )
		{
			/* see previous */
			TreeNodePtr temp = treePtr;
			treePtr = treePtr->leftPtr;
			free(temp);	
		}
		// Case 3: Two children
		else
		{
			TreeNodePtr temp = findMin(treePtr->rightPtr);
			treePtr->data = temp->data;
			treePtr->rightPtr = deleteNode( treePtr->rightPtr, temp->data );
		}
	}
	return treePtr;
}


/* Find the node with the lowest value in the branch passed */
TreeNodePtr findMin( TreeNodePtr treePtr )
{
	/* first an idiot check */
	if(treePtr == NULL) return NULL;
	
	/* if this is the lowest value return it */
	if(treePtr->leftPtr == NULL)
	    return treePtr;
	else
	    return findMin( treePtr->leftPtr ); 
}


void inOrder( TreeNodePtr treePtr )
{
	if( treePtr != NULL ) {
		inOrder( treePtr->leftPtr );
		printf( "%3d", treePtr->data );
		inOrder( treePtr->rightPtr );
	}
}


void preOrder( TreeNodePtr treePtr )
{
	if( treePtr != NULL ) {
		printf( "%3d", treePtr->data );
		preOrder( treePtr->leftPtr );
		preOrder( treePtr->rightPtr );
	}
}


void postOrder( TreeNodePtr treePtr )
{
	if( treePtr != NULL ) {
		postOrder( treePtr->leftPtr );
		postOrder( treePtr->rightPtr );
		printf( "%3d", treePtr->data );
	}
}


/* Add an item onto the queue */
void enqueue( QueueNodePtr *headPtr,  QueueNodePtr *tailPtr, TreeNodePtr value )
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
	    printf( "%d not inserted. No memory available.\n", value->data );
}


/* Remove an item from the queue */
TreeNodePtr dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr )
{
	TreeNodePtr value;	
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


