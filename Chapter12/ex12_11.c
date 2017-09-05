/*
 * Filename:	ex12_11.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/08/2017
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct stackNode {
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int isPalindrome( StackNodePtr *, const char * );
void addWordToStack( StackNodePtr *, const char * );
int stripNonLetters( const char *, char[] );
int getLine( char [], int );
void push( StackNodePtr *, int );
int pop( StackNodePtr * );
int isEmpty( StackNodePtr );


int main()
{
	StackNodePtr stackPtr = NULL;
	char line[80];
	char stripped[80];
	
	printf("Enter a line of text: ");
	getLine(line, 30);
	stripNonLetters(line, stripped);

    addWordToStack( &stackPtr, stripped );
	
	if( isPalindrome( &stackPtr, stripped )==1 )
		printf("\"%s\" is a Palindrome\n", line);
	else
	printf("\"%s\" is NOT a Palindrome\n", line);

	return 0;
}


int isPalindrome( StackNodePtr *stackPtr, const char* word )
{
	char c;
	int i = 0;
	
	while(!isEmpty( *stackPtr ))
	{
		c = pop( stackPtr );
		if(c!=word[i++])
		    return 0;
	}
	
	if(word[i]!='\0')
	    return 0;
	    
	return 1;
}


void addWordToStack( StackNodePtr *stackPtr, const char* word )
{
	/* Push the entered text onto the stack */
	int i=0;
	while(word[i]!='\0') {
		push( stackPtr, word[i]);
		i++;
	}	
}



int stripNonLetters( const char *original, char copy[] )
{
	int i=0, length=0;
	
	while(original[i] != '\0')
	{
		if(isalpha(original[i]))
		    copy[length++] = tolower(original[i]);
		i++;
	}
	copy[length] = '\0';
	
	return length;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
	int c, i=0;
	
	while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
	    s[i++]=c;

	s[i] = '\0';
	
	/* Clear any overflow*/
	fflush(stdin);
	
	return i;	
}



/* Push value onto the stack */
void push( StackNodePtr *topPtr, int info )
{
	StackNodePtr newPtr;
	
	newPtr = malloc( sizeof( StackNode ) ); /* Now points to a place in memory*/
	
	if( newPtr != NULL ) {
		newPtr->data = info;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else
	    printf( "%c not inserted. No memory available.\n", info );
}


/* Pop value from the stack */
int pop( StackNodePtr *topPtr )
{
	StackNodePtr tempPtr;
	int popValue;
	
	tempPtr = *topPtr;
	popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;
	free( tempPtr );
	
	return popValue;
}


/* Test if the list is empty */
int isEmpty( StackNodePtr topPtr )
{
	return topPtr==NULL;
}


