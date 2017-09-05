/*
 * Filename:    ex08_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/06/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void countLetters(int [26], char * );
void printResult(int [26]);
int getLine( char [], int );


const char *alphabet = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    int results[26] = {0};
    char line1[80], line2[80];
    
    printf("Enter line 1: ");
    getLine(line1, 80); 
    
    printf("Enter line 2: ");
    getLine(line2, 80); 
    
    countLetters(results, line1);
    countLetters(results, line2);
    
    
    printResult(results);
    
    return 0;
}


void countLetters(int results[26], char *line)
{
    char *searchPtr;
    int i;
    
    for(i=0; i<26; i++)
    {   
        searchPtr = strchr( line, alphabet[i]);
        while(searchPtr != NULL )
        {   
            ++results[i];
            searchPtr = strchr( searchPtr+1, alphabet[i] );
        }
    }
}




void printResult(int results[26])
{
    printf("---- Total occurences of each letter in the text ----\n\n");
    
    
    int i;
    for(i=1; i<=8; i++)
    {
        printf("%c\t", alphabet[i-1]);
    }
    printf("\n");
    for(i=1; i<=8; i++)
    {
        printf("%d\t", results[i-1]);
    }
    printf("\n\n");
    
    for(i=9; i<=16; i++)
    {
        printf("%c\t", alphabet[i-1]);
    }
    printf("\n");
    for(i=9; i<=16; i++)
    {
        printf("%d\t", results[i-1]);
    }
    printf("\n\n");
    
    for(i=17; i<=24; i++)
    {
        printf("%c\t", alphabet[i-1]);
    }
    printf("\n");
    for(i=17; i<=24; i++)
    {
        printf("%d\t", results[i-1]);
    }
    printf("\n\n");
    
    for(i=25; i<=26; i++)
    {
        printf("%c\t", alphabet[i-1]);
    }
    printf("\n"); 
    for(i=25; i<=26; i++)
    {
        printf("%d\t", results[i-1]);
    }
    printf("\n\n"); 
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

