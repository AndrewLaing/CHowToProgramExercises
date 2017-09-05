/*
 * Filename:    stripNonLetters.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/08/2017
 * Description: Stack implementation using pointers.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int stripNonLetters( const char *, char[] );
int getLine( char [], int );



int main()
{
    char line[30];
    char stripped[30];
    
    printf("Enter a line of text: ");
    getLine(line, 30);
    stripNonLetters(line, stripped);
    
    printf("Stripped version = %s\n", stripped); 

    return 0;
}


int stripNonLetters( const char *original, char copy[] )
{
    int i=0, length=0;
    
    while(original[i] != '\0')
    {
        if(isalpha(original[i]))
            copy[length++] = original[i];
        i++;
    }
    copy[length] = '\0';
    
    return length;
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


