/*
 * Filename:    getInteger.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/06/2017.
 * Description: Input an Integer
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 7

int getLine( char [], int );
int getInteger( void );

int main()
{
    int num1;
    
    printf("Enter integer string (MAX 6 CHARS) > ");
    num1 = getInteger();
    
    printf("num1 = %d\n", num1);
         
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
int getInteger()
{
    char str[MAXLEN];
    int result=0;
    
    /* Input a string */
    getLine(str, MAXLEN);
    
    /* Convert to a float */
    sscanf(str, "%d", &result);

    return result;
}
