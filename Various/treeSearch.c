/*
 * Filename:	ex12_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/08/2017
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

TreeNodePtr searchTree( TreeNodePtr, int );

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
    
    
    int query;
	TreeNodePtr result;
	printf("\n\nEnter value to search for: ");
	scanf("%d", &query);
	fflush(stdin);
	result = searchTree(rootPtr, query );
	
	if(result != NULL)
	    printf("\n%d was found\n", result->data );
	else
	    printf("\n%d was NOT found\n", query );
    
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


TreeNodePtr searchTree( TreeNodePtr treePtr, int query )
{
	TreeNodePtr result = treePtr;
	
	if( treePtr != NULL ) 
	{
		if( query < treePtr->data) 
		    result = searchTree( treePtr->leftPtr, query );
		else if( query > treePtr->data)
		    result = searchTree( treePtr->rightPtr, query );
		else
		    return treePtr;	
	}
    return result;
}

