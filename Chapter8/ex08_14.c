/*
 * Filename:	ex08_14.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/06/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getLine( char [], int );


int main()
{
	char str[80];
	char *tokenPtr;
	int areaCode;
	long number, num2;
	
	printf("Enter phone number: ");
	getLine(str, 80); 
	
	tokenPtr = strtok( str, " ()-" );
	
	int i=0;
	while( tokenPtr != NULL ) {
		if(i==0)
		    sscanf(tokenPtr, "%d", &areaCode);
		else if(i==1) {
			sscanf(tokenPtr, "%ld", &number);
			number *= 10000;
		}
		else {
			sscanf(tokenPtr, "%ld", &num2);
			
			number += num2;
		}
		i++;
    	tokenPtr = strtok( NULL, " ()-" );
	}
		 
    printf("Area code = %d\n", areaCode);
    printf("Number = %li\n", number);
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


