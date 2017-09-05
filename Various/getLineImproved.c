/*
 * Filename:	getValidInteger.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/08/2017.
 * Description: Input an Integer
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 9

int getLine( char [], int );
int isValidIntegerString( const char * );
int getValidInteger();


int main()
{
	int num1;
	
	printf("Enter integer string > ");
    num1 = getValidInteger();
    
    printf("num1 = %d\n", num1);
		 
 	return 0;
}


/* Read a string into a character array and return the length of the array  
 * Note: this produces an error message if the user trys to overflow the
 *       the character array, but allows them to retype rather than crashing
 */
int getLine( char s[], int maxLength )
{
	int c, count, i, validLine=0;
	
	while(validLine == 0)
	{
		count=0, i=0;
		while( count <= maxLength && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
		{
			s[i++]=c;
			count++;
		}
		
		if( count > maxLength ) {
			printf("Error - max line length is %d characters\n", maxLength );
			printf("Please retype line: ");
		}
		else validLine++;   
	
    	fflush(stdin);  /* Clear any overflow*/
	}

	if(c=='\n')
	    s[i++]=c;
	s[i] = '\0';

	
	fflush(stdin);  /* Clear any overflow*/
	
	return i;	
}


/* This method returns 1 if the user could extract a valid signed
 * or unsigned int from it, otherwise ir returns 0
 * Note: at the moment the method does not check that the string
 *       is within system boundaries 
 */ 
int isValidIntegerString(const char *str)
{
	int i=0;
    
    /* Check first that only valid characters are used */
	while( str[i] != '\n' && str[i] != '\0' )
	{
		if( i==0 && ( str[0]=='+' || str[0]=='-' ) )
		    ;
		else if( isdigit(str[i]) == 0 )
			return 0;
			
		i++;
	}

    /* Finally check that a valid signed or unsigned int has been entered */
	if( (str[i-1]=='\0' || str[i-1] != '\n' ) && isdigit(str[0]) )
	    return 1;
	else if( ( str[0]=='+' || str[0]=='-' ) ) {
		if( str[1]=='\0' || str[1] == '\n' )
		    return 0;
		else
		    return 1;
	}
    else
    	return 0;
}


/* This method gets the user to input, then returns a valid integer
 * Note: The maximum length of the integer is define as MAXLEN, and 
 *       at the moment the method does not check that the string
 *       is within system integer boundaries. 
 */
int getValidInteger()
{
	char str[MAXLEN];
	int result=0;
	int validInt = 0;
	
	/* Input a string */
    getLine(str, MAXLEN);
    
    while(validInt == 0)
    {
    	validInt = isValidIntegerString( str ); 

		if( validInt == 0 ) 
		{
			printf("Error - Please enter a valid number: ");
			getLine(str, MAXLEN);			
		}
	}
	
	/* Convert string to an integer */
    sscanf(str, "%d", &result);

	return result;
}
