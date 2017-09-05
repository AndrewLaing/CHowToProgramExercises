/*
 * Filename:	ex08_37.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/07/2017.
 */

#include <stdio.h>
#include <string.h>
#define PERMITTEDLENGTH 9


void printCheck(char [], int );
int getLine( char [], int );


int main()
{
    char amount[PERMITTEDLENGTH+1];
    int length;
    
    printf("Enter amount to be paid: ");
    length = getLine(amount, PERMITTEDLENGTH+1);
	
    printCheck(amount, length);
	return 0;
}


void printCheck(char amount[], int length)
{
	int spaces = PERMITTEDLENGTH - length;
	int i;
	for(i=0; i<spaces; i++)
	    printf("*");
	printf("%s\n", amount);
	
	for(i=0; i<PERMITTEDLENGTH; i++)
	    printf("-");
	printf("\n");
	for(i=1; i<=PERMITTEDLENGTH; i++)
	    printf("%d", i);
	printf("\n");
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

