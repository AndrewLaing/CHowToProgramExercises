/*
 * Filename:	ex08_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/06/2017.
 */
#include <stdio.h>
#include <string.h>


int countTokens(char * );
int getLine( char [], int );


int main()
{	    
	int count = 0; 
	char line1[80], line2[80];
	
	printf("Enter line 1: ");
	getLine(line1, 80); 
	
	printf("Enter line 2: ");
	getLine(line2, 80); 
    
    count += countTokens(line1);
    count += countTokens(line2);
		   
    printf("Wordcount = %d\n", count);    
 	return 0;
}


int countTokens(char *text)
{
    char *tokenPtr;
    int count = 0;    
    
    tokenPtr = strtok( text, " \n" );
    
    while( tokenPtr != NULL ) {
    	count++;
    	tokenPtr = strtok( NULL, " \n" );
	}
	
	return count;
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



