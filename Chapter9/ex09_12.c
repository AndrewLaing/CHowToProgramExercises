/*
 * Filename:	ex09_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        17/07/2017.
 */

#include <stdio.h>

int getLine( char [], int );

int main()
{
	char string[50];
    int length;
    
    printf("--- using scanf ---\n");
    printf("Enter the string: ");
    scanf("%s%n", string, &length);
    printf("length = %d\n", length);
    fflush(stdin);
	printf("%*s\n", length*2, string);
	
    printf("\n--- using getline ---\n");
    printf("Enter the string: ");
    length = getLine(string, 50); 
	printf("%*s\n", length*2, string);
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
