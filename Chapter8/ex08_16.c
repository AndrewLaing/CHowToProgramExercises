/*
 * Filename:    ex08_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/06/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int getLine( char [], int );


int main()
{
    char text[80];
    char searchStr[80];
    char *searchPtr;
    
    printf("Enter text: ");
    getLine(text, 80); 
    
    printf("Enter search string: ");
    getLine(searchStr, 80);     
    
    searchPtr = strstr( text, searchStr );
    
    while(searchPtr != NULL )
    {
        printf("%s\n", searchPtr);
        searchPtr = strstr( searchPtr+1, searchStr );
    }
    

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

