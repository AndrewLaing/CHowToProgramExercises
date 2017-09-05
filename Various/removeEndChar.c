/*
 * Filename:    removeEndChar.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/08/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



void pushLineEntriesToTable( const char * );
int getLine( char [], int );
int startsWith( const char *, char );
int endsWith( const char *, char );
int strlen2( const char* s );
void removeEndChar( char *s );


int main()
{
    char str[80];
    
    printf("Enter sentence: ");
    getLine(str, 80); 
    
    pushLineEntriesToTable( str );

    return 0;
}


void pushLineEntriesToTable( const char *line )
{
    char *tokenPtr;
    char temp[10];
    
    tokenPtr = strtok( line, " " );
    
    while( tokenPtr != NULL ) 
    {
        if(strlen2(tokenPtr) > 1 ) 
        {
            if( startsWith(tokenPtr, '(') ) {
                printf("(\n");
                tokenPtr++;
            }
            if( strlen2(tokenPtr) > 1 && endsWith(tokenPtr, ')') ) {
                removeEndChar(tokenPtr);
                printf("%s\n", tokenPtr);
                printf(")\n");
            }
            else
                printf("%s\n", tokenPtr);   
        }
        else
            printf("%s\n", tokenPtr); 

        tokenPtr = strtok( NULL, " " );
    }
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


void removeEndChar( char *s )
{
    if(s==NULL)
       return;
    int i=0;
    
    while(s[i]!='\0')
        i++;
    
    s[--i] = '\0';
}



int strlen2( const char* s )
{
    int i=0;
    
    while(*s++!='\0')
        i++;

    return i;
}
