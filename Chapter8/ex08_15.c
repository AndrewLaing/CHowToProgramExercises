/*
 * Filename:	ex08_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/06/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printTokensInReverse(char *tokenPtr);
int getLine( char [], int );


int main()
{
	char str[80];
	char *tokenPtr;
	
	printf("Enter sentence: ");
	getLine(str, 80); 
	
	tokenPtr = strtok( str, " " );	
	printTokensInReverse(tokenPtr); 

 	return 0;
}

/* Uses recursion to print tokens in reverse order */
void printTokensInReverse(char *tokenPtr)
{
	if(tokenPtr==NULL)
		return;
	    	    
	char *temp = tokenPtr;
	
	tokenPtr = strtok( NULL, " " );
    printTokensInReverse(tokenPtr);

	printf("%s ", temp);
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

