/*
 * Filename:	ex08_25.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/06/2017.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 4
 
int getLine( char [], int );
int getASCIICode( void );

int main()
{
	int num1;
	
	printf("Enter ASCII Code (0-255) > ");
    num1 = getASCIICode();
    
    printf("ASCII Char for code %d = %c\n", num1, num1);
    
    for(num1=0; num1<=255; num1++)
        printf("%c ", num1);
    
		 
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


/* Returns a valid integer */
int getASCIICode()
{
	char str[MAXLEN];
	int result=0;
	
	/* Input a string */
    getLine(str, MAXLEN);
	
	/* Convert to a float */
    sscanf(str, "%d", &result);

    if(result<0 || result>255)
        return -1;
        
	return result;
}
