/*
 * Filename:    startsWithEndsWith.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/08/2017
 * Description: Two methods wich test whether a string starts eith
 *              or ends with the character provided.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    /* is alpha etc*/


int startsWith( const char *, char );
int endsWith( const char *, char );
int getLine( char [], int );


int main()
{
    char line[50];
    
    printf("Please enter expression: ");
    getLine(line, 50 ); 

    if(startsWith(line, '(') )
        printf("Line starts with (\n");
    else
        printf("Line does not start with (\n");
        
    if(endsWith(line, ')') )
        printf("Line ends with )\n");
    else
        printf("Line does not end with )\n");
        
    return 0;
}


int startsWith( const char *s, char c )
{
    if(s!=NULL)
        return s[0] == c;
    return 0;
}


int endsWith( const char *s, char c )
{
    if(s==NULL)
       return 0;
    int i=0;
    
    while(s[i]!='\0')
        i++;
    
    return s[--i] == c;
}




/* Read a string into a character array and return the length of the array 
 * this version does not add newline characters */
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

