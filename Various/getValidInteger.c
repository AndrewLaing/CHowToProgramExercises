/*
 * Filename:    getValidInteger.c
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



/* This method gets the user to input, then returns a valid integer
 * Note: The maximum length of the integer is define as MAXLEN, and 
 *       at the moment the method does not check that the string
 *       is within system integer boundaries. 
 
 ** PROBLEM CAUSED BY SSCANF skipping SPACES
 */
int getValidInteger()
{
    char str[MAXLEN+1];
    int result = 0;
    int validInt = 0;
    
    /* Input a string */
    getLine(str, MAXLEN);
    
    /* If the string is valid convert and return it */
    while(validInt == 0)
    { 
        /* sscanf returns the number of conversions made */
        if( !isspace(str[0]) )
            validInt = sscanf(str, "%d", &result); 

        if( validInt == 0 ) 
        {
            printf("Error - Please enter a valid number: ");
            getLine(str, MAXLEN);           
        }
    }

    return result;
}

