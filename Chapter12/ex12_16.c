/*
 * Filename:    ex12_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        08/08/2017
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



int main()
{
    int i, item;
    TreeNodePtr rootPtr = NULL;
    
    srand(time(NULL));

    printf("The numbers being placed in the tree are:\n");
    
    for(i=1; i<10; i++) {
        item = rand() % 15;
        printf("%3d", item);
        insertNode( &rootPtr, item );
    }    
    
    /* Traverse the tree preOrder */
    printf("\n\nThe preOrder traversal is:\n");
    preOrder( rootPtr );
    
    /* Traverse the tree inOrder */
    printf("\n\nThe inOrder traversal is:\n");
    inOrder( rootPtr );
    
    /* Traverse the tree postOrder */
    printf("\n\nThe postOrder traversal is:\n");
    postOrder( rootPtr );
    
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
        if( value <= (*treePtr)->data )
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


