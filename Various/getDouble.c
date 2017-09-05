/*
 * Filename:	getFloat.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Input a double
 *              Note Max 6 places decimal accuracy
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXFLOATLEN 14

int getLine( char [], int );
double getDouble( void );

int main()
{
	double num1;
	
	printf("Enter double string (MAX 12 CHARS) > ");
    num1 = getDouble();
    
    printf("num1 = %lf\n", num1);
		 
 	return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
	int c, i=0;
	
	while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
	    s[i++]=c;

	if(c=='\n')
	    s[i++]=c;
	s[i] = '\0';
	
	/* Clear any overflow*/
	fflush(stdin);
	
	return i;	
}


/* Returns a valid WORDLENGTH integer, sentinel value, or Error code */
double getDouble()
{
	char str[MAXFLOATLEN];
	double result;
	
	/* Input a string */
    getLine(str, MAXFLOATLEN);
	
	/* Convert to a float */
    sscanf(str, "%lf", &result); /* Note lf flag for double (long float)*/

	return result;
}
