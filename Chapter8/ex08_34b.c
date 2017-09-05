/*
 * Filename:    ex08_34b.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        05/07/2017.
 * Description: Write a program that read several lines of text and prints
 *              a table indicating the number of one letter words, two letter
 *              words, three letter words etc.
 * ToDo: Either create a tokeniser, use strtok, use regexes etc
 *       use strlen for word length, add to array like 34a
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void addToCount( int [], const char * );
void printResult( int [] );
int getLine( char [], int );
int strlen2( const char* );

 
int main()
{
    char str[80];
    int count[26] = {0};
    int i;

    for(i=0; i<3; i++)
    {
        printf("Enter line #%d: ", i);
        getLine(str, 80); 
        addToCount( count, str);
    }
        
    printResult(count);
    return 0;
}


void addToCount(int count[], const char *sentence)
{
    char *tokenPtr; 
    
    tokenPtr = strtok( sentence, " .,;:?" );
    
    while( tokenPtr != NULL ) {
        ++count[strlen2(tokenPtr)]; 
        tokenPtr = strtok( NULL, " .,;:?" );
    }   
}


void printResult(int count[])
{   
    int i;
    
    printf("\n%s%15s", "Word Length","Occurences\n");
    for(i=1; i<15; i++)
        printf("\n%-16d%d", i, count[i]);
    
    printf("\n");
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


/* Using pointer arithmetic */
int strlen2( const char* s )
{
    int i=0;

    while(*s++!='\0')
        i++;

    return i;
}

