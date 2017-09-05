/*
 * Filename:	ex12_25.c
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

void insertNode( TreeNodePtr *, int );
void inOrder( TreeNodePtr );
void preOrder( TreeNodePtr );
void postOrder( TreeNodePtr );

TreeNodePtr deleteNode( TreeNodePtr, int );
TreeNodePtr findMin( TreeNodePtr );


void outputTree( TreeNodePtr );
void doOutputTree( TreeNodePtr, int );


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
    
    printf("\n\nThe tree output is:\n");
    outputTree( rootPtr );


	return 0;
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


void outputTree( TreeNodePtr treePtr )
{
	if( treePtr == NULL )
		return;
	else
	   doOutputTree( treePtr, 0 );
}



void doOutputTree( TreeNodePtr currentPtr, int totalSpaces )
{
	int i;
	while( currentPtr != NULL )
	{
		doOutputTree( currentPtr->rightPtr, totalSpaces+5 );
		
		for( i=1; i<=totalSpaces; i++ )
		    printf(" ");
		
		printf( "%d\n", currentPtr->data );
		currentPtr = currentPtr->leftPtr;
		totalSpaces += 5;
	}
}

