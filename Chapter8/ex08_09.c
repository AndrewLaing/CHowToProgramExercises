/*
 * Filename:	ex08_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: Compare strings 
 */

#include <stdio.h>
#include <string.h> /* for strcmp */

int getLine( char [], int );

int main()
{	
    char s1[20], s2[20];
    size_t n;

    printf("Enter string s1: ");
    getLine(s1, 20);
    printf("Enter string s2: ");
    getLine(s2, 20);

    n = strcmp( s1, s2 );
    
    if(n==0) {
    	printf("The two strings are the same\n");
	}
	else if(n==-1) {
		printf("%s is less than %s\n", s1, s2);
	}
	else
	    printf("%s is greater than %s\n", s1, s2);
	
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

