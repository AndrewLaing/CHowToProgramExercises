/*
 * Filename:	linkedList.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        09/07/2017.
 * Description: Implementation of a linked list for a histogram
 * Derived from: http://www.java2s.com/Tutorial/C/0260__Data-Structure/LinkedLists.htm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char word[30];
	int count;
    struct node *next;
};


struct node *insert( struct node *, const char *, int );
int searchlist ( struct node *, char * );
struct node *updateList( struct node *, const char * );
void printlist ( struct node * );
void freeList( struct node * );


int main()
{
	struct node *start = NULL;
	
	start = updateList( start, "Word One" );
	start = updateList( start, "Word Two" );
	start = updateList( start, "Word Three" );
	start = updateList( start, "Word Four" );                          
	
	printf("--- Initial list ---\n");
	printlist ( start );
	searchlist ( start, "Word Two" );
	searchlist ( start, "Dumplings" );

    start = updateList( start, "Word Two" );
	printf("\n\n--- Updated list ---\n");
	printlist ( start );

	/* Free all the memory allocated for the linked list */
	freeList( start );
	return 0;
}


struct node *insert(struct node *p, const char *word, int n)
{
    struct node *temp;
    
    /* If this is the first node...*/
    if( p == NULL )
	{
        p = ( struct node * )malloc( sizeof(struct node) );

        if( p==NULL ) {
            printf("Error\n");
            exit(0);
        }
        
        strcpy(p-> word, word);
        p-> count = n;
        p-> next = NULL;
    } 
	else 
	{
        temp = p;
        
        /* move to the end of the list */
        while (temp-> next != NULL)
            temp = temp-> next;
        
		/* Allocate space for a new node */    
        temp-> next = (struct node *)malloc(sizeof(struct node));
        
        /* If space could not be allocated */
        if(temp -> next == NULL){
           printf("Error\n");
           exit(0);
        }
        
        /* Add the node details */
        temp = temp-> next;
        strcpy(temp-> word, word);
        temp-> count = n;
        temp-> next = NULL;
    }
        
	return (p);
}


/* searchlist looks for a word in the linked list */
int searchlist( struct node *p, char *toFind )
{
	struct node *temp;
	temp = p;
	int found = 0;

	if(p!= NULL)
	{
	    do {
	    	if(strcmp(temp->word, toFind) == 0) {
	    	    found=1;
				break;	
			}
	        temp = temp-> next;
	    } while (temp!= NULL);
	}
	else
	{
		printf("The list is empty\n");
		return 0;
	}
	
	if(found==0)
	    printf("%s NOT found in linked list\n", toFind);
	else
	    printf("%s found :)\n", toFind);
	
	return found;
}


struct node *updateList(struct node *p, const char *word)
{
    struct node *temp;
    
    /* If this is the first node...*/
    if( p == NULL )
	{
        p = ( struct node * )malloc( sizeof(struct node) );

        if( p==NULL ) {
            printf("Error\n");
            exit(0);
        }
        
        strcpy(p-> word, word);
        p-> count = 1;
        p-> next = NULL;
        
        return (p);
    } 
    
    temp = p;
    
    /* Search for token, if found update its count */
    while (temp-> next != NULL)
    {
    	if(strcmp(temp->word, word) == 0) {
    		temp-> count += 1;
    		return (p);
    	}
    	temp = temp-> next; 
	}
       
    /* If token is not in the list add it */
	/* Allocate space for a new node */    
    temp-> next = (struct node *)malloc(sizeof(struct node));
    
    /* If space could not be allocated */
    if(temp -> next == NULL){
       printf("Error\n");
       exit(0);
    }
    
    /* Add the node details */
    temp = temp-> next;
    strcpy(temp-> word, word);
    temp-> count = 1;
    temp-> next = NULL;

	return (p);
}


void printlist ( struct node *p )
{
	struct node *temp;
	temp = p;
	printf("%s\t\t\t%s\n\n","Token", "Value" );
	if(p!= NULL)
	{
	    do {
	    	printf("%s\t%13d\n",temp->word, temp->count );
	        temp = temp-> next;
	    } while (temp!= NULL);
	}
	else
		printf("The list is empty\n");
}


/* Note: this is not strictly necessary as free only frees the memory
 *       allocated by malloc to be used again by the program */
void freeList(struct node* head)
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}



















