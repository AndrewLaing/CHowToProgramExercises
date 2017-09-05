/*
 * Filename:	ex12_14.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        08/08/2017
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    /* for isdigit etc*/
#include <math.h>     /* for pow */

struct stackNode {
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;


int evaluatePostfixExpression( char * );
int calculate( int, int, char );
void push( StackNodePtr *, int );
int pop( StackNodePtr * );
int isEmpty( StackNodePtr );
void printStack( StackNodePtr );
int getLine( char [], int );
int isOperator( char );

int main()
{
    char postfix[50];
    int result;
    
    printf("Please enter postfix expression: ");
    getLine( postfix, 50 ); 
    
    result = evaluatePostfixExpression( postfix );
    printf("Result: %d\n", result);
    
	return 0;
}


int evaluatePostfixExpression( char *expr )
{
	StackNodePtr stackPtr = NULL;
	char c;
	int x, y;
	int i=0, mult=1, num=0;
	
	while( expr[i] != '\0' )
	{
		mult=1; num=0;
		c = expr[i];
		if( isdigit(c) ) 
		{
			while( isdigit(c) ) 
			{
				num *= mult;
				num += c-48;
				c = expr[++i];
				mult *= 10;
			}
			--i;
			push( &stackPtr, num );
		}
		else if( isOperator( c ) )
		{
			if(isEmpty( stackPtr ) ) {
				printf("Invalid postfix expression!\n");
				return 0;
			}
			x = pop( &stackPtr );
			
			if(isEmpty( stackPtr ) ) {
				printf("Invalid postfix expression!\n");
				return 0;
			}
			y = pop( &stackPtr );
			
			push( &stackPtr, calculate(y, x, c) );
		}
		i++;
	}
	
	if(isEmpty( stackPtr ) ) {
		printf("Invalid postfix expression!\n");
		return 0;
	}
	
	return pop( &stackPtr );
}


int calculate( int op1, int op2, char operator )
{
	int result = 0;
	
	switch( operator )
	{
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
		case '*':
			result = op1 * op2;
			break;
		case '/':
			result = op1 / op2;
			break;
		case '^':
			result = pow( op1, op2 );
			break;
		case '%':
			result = op1 % op2;
			break;
		default:
			break;
	}
	
	return result;
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


/* Print the contents of the stack from currentPtr */
void printStack( StackNodePtr currentPtr )
{
	if( currentPtr == NULL )
    	printf( "The stack is empty.\n\n" );
    else 
	{
    	printf( "The stack is:\n" );
    	
    	while( currentPtr != NULL) {
    		printf( "%d --> ", currentPtr->data );
    		currentPtr = currentPtr->nextPtr;
		}
		
		printf( "NULL\n\n" );
	}
}


/* Read a string into a character array and return the length of the array 
 * this version does not add newline characters */
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


/* Returns 1 if the character is an Operator, otherwise 0 */
int isOperator( char c )
{
	int result = 0;

	switch( c )
	{
		case '^': case '*': case '/': case '%': case '+': case '-':	
	        result = 1;
	    	break;
	    default:
	    	break;
	}

    return result;
}


