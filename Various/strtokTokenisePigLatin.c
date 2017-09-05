/*
 * Filename:    ex08_13.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/06/2017.
 * Notes:       IMPORTANT - strtok changes the original string by placing
 *                          nullbytes in place of the delimiters
 *                          eg "token and token\0"
 *                             "token\0and\0token\0"
 *                          So if you need the original intact, keep or send 
 *                          a copy to be tokenised.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getLine( char [], int );
void printLatinWord(char *);


int main()
{
    char str[80];
    char *tokenPtr;
    
    printf("Enter sentence: ");
    getLine(str, 80); 
    
    tokenPtr = strtok( str, " " );
    
    
    while( tokenPtr != NULL ) {
        printLatinWord(tokenPtr); 
        tokenPtr = strtok( NULL, " " );
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


void printLatinWord(char *word)
{
    if(strlen(word)>1)
        printf("%s%cay ",&word[1], tolower(word[0]));
    else
        printf("%cay ", tolower(word[0]));
    
}
