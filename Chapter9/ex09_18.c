/*
 * Filename:	ex09_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/07/2017.
 */

#include <stdio.h>


int getLine( char [], int );

int main()
{	 
    char a[50], b[50], c[50];
    printf("Please type suzy: ");
    getLine(a, 50);
	printf("Please type \'suzy\': "); 
    getLine(b, 50);
    printf("Please type \"suzy\": ");
    getLine(c, 50);
    printf("\ninput1 = %s\n", a);
    printf("input2 = %s\n", b);
    printf("input3 = %s\n", c);


	return 0;
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
