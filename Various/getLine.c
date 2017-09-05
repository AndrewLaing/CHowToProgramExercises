/*
 * Filename:    ex07_25.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Convert a hex string to an integer
 */

#include <stdio.h>
#include <stdlib.h>

int getLine( char [], int );

int main()
{
    char str[5];
    int num1;
    
    printf("Enter hex string (MAX 4 CHARS) > ");
    getLine(str, 5); 
    
    /* Convert Hexstring to an integer */
    sscanf(str, "%x", &num1);
    
    /* Print as hex using %x */
    printf("0x%x %d\n", num1, num1); 
    printf("%08X %i\n", num1, num1); 
         
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


