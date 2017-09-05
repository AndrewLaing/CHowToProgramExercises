/*
 * Filename:    ex08_18.c
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
    char line1[80], line2[80];
    char searchStr[80];
    char *searchPtr;
    char searchChr;
    int count = 0;
    
    printf("Enter line 1: ");
    getLine(line1, 80); 
    
    printf("Enter line 2: ");
    getLine(line2, 80); 
    
    printf("Enter search character: ");
    getLine(searchStr, 2);  
    searchChr = searchStr[0];
    
    searchPtr = strchr( line1, searchChr );
    while(searchPtr != NULL )
    {
        count++;
        searchPtr = strchr( searchPtr+1, searchChr );
    }
    
    searchPtr = strchr( line2, searchChr );
    while(searchPtr != NULL )
    {
        count++;
        searchPtr = strchr( searchPtr+1, searchChr );
    }
    
    printf("%d occurrences of '%c' found in the text\n", count, searchChr);
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

