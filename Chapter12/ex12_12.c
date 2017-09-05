/*
 * Filename:	ex12_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        07/08/2017
 * Description: Convert Infix math expression to Postfix
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    /* is alpha etc*/

struct stackNode {
	char data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void convertToPostfix( char infix[], char postfix[] );
int isOperator( char c );
int precedence( char operator1, char operator2 );
void push( StackNodePtr *, char );
char pop( StackNodePtr * );
char stackTop( StackNodePtr );
int isEmpty( StackNodePtr );
void printStack( StackNodePtr );
int getLine( char [], int );


void testPrecedence()
{
	char op1='+', op2='*';
    printf("precedence( %c, %c ) = %d \n", op1, op2, precedence( op1, op2 ));	
}

void testIsOperator()
{
	char op1='+', nonOp = '2';
	
    if( isOperator( op1 ) )
        printf("\"%c\" is an Operator\n", op1);
    else
        printf("\"%c\" is NOT an Operator\n", op1);
        
    if( isOperator( nonOp ) )
        printf("\"%c\" is an Operator\n", nonOp );
    else
        printf("\"%c\" is NOT an Operator\n", nonOp );
}

int main()
{
    char infix[50];
    char postfix[50];
    
    printf("Please enter infix expression: ");
    getLine(infix, 50 ); 

    convertToPostfix( infix, postfix ); 
    printf("Postfix expression: %s\n", postfix);
    
	return 0;
}


void convertToPostfix( char infix[], char postfix[] )
{
    int i=0, j=0;	
	char c;

	/* Push left parenthesis to stack */
    StackNodePtr stackPtr = NULL;
    push( &stackPtr, '(' ); 
    
    /* Add right parenthesis to end of infix */
    while( infix[i]!='\0')
    	i++;

	infix[i++] = ')';
	infix[i] = '\0';
	
	i=0;
	
	/* Do the conversion */
	while( !isEmpty( stackPtr ) && infix[i]!='\0' )
	{
		c = infix[i++];
		
		if( isdigit(c) ) 
		{
			while( isdigit(c) ) {
				postfix[j++] = c;
				c = infix[i++];
			}
			postfix[j++] = ' ';
			
			if(c == ')' || isOperator(c) )
			    i--;
		}
		else if( c == '(')
		    push( &stackPtr, '(' );
		else if( isOperator(c) == 1 ) 
		{
			if( !isEmpty( stackPtr ) && isOperator( stackTop(stackPtr) ) ) {
				while( isOperator( stackTop(stackPtr) ) && 
				       (precedence( stackTop(stackPtr), c )) >= 0 ) 
				{
				   	postfix[j++] = pop( &stackPtr );
					postfix[j++] = ' ';
				}
				push( &stackPtr, c );
			}
			else
			    push( &stackPtr, c );
		}
		else if( c == ')') 
		{
			if( !isEmpty( stackPtr ) ) 
			{
				c = pop( &stackPtr ); 

				while( !isEmpty( stackPtr ) && c != '(' ) {
					postfix[j++] = c;
					postfix[j++] = ' ';
					c = pop( &stackPtr ); 
				}
			}
	    }
	}
	postfix[j] = '\0';
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


/* Returns -1 if operator1 has lower precedence than operator2,
 * 0 if it has the same precedence, and 1 if it has higher precedence 
 * order of precedence = ^ * / % + -   
 */
int precedence( char operator1, char operator2 )
{
	int result = 1;

	switch( operator1 )
	{
		case '^':
			if( operator2 == '^') result = 0;
			break;
	    case '*': case '/': case '%':
	    	switch( operator2 ) {
	    		case '^':
	    			result = -1;
	    			break;
	    		case '*': case '/': case '%':
	    			result = 0;
	    		    break;
	    		default:
	    			break;
			}
	    	break;
	    case '+': case '-':	
	        switch( operator2 ) {
	    		case '-': case '+':
	    			result = 0;
	    			break;
	    		default:
	    			result = -1;
	    			break;
			}
	    	break;
	}

    return result;
}


/* Push value onto the stack */
void push( StackNodePtr *topPtr, char info )
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
char pop( StackNodePtr *topPtr )
{
	StackNodePtr tempPtr;
	char popValue;
	
	tempPtr = *topPtr;
	popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;
	free( tempPtr );
	
	return popValue;
}


/* Return the value at the top of the stack */
char stackTop( StackNodePtr topPtr )
{
	char topValue;
	
	topValue = topPtr->data;
	
	return topValue;	
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
    		printf( "%c --> ", currentPtr->data );
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

