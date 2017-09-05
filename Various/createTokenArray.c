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
#define MAXLINELENGTH 100
#define MAXTOKENLENGTH 20

int getLine( char [], int );
int createTokenArray( const char *line, char tokenArray[][MAXTOKENLENGTH] );
char *strcpy2( char *s1, const char *s2 );


int main()
{
    char str[ MAXLINELENGTH ];
    char tokenArray[ MAXLINELENGTH/2 ][ MAXTOKENLENGTH ];
    
    printf("Enter the line to tokenise > ");
    getLine( str, MAXLINELENGTH );
    
    int tokenArrayLength;
    
    tokenArrayLength = createTokenArray( str, tokenArray );
    
    int i;
    for(i=0; i<tokenArrayLength; i++ )
    {
        printf("%d: %s\n", i, tokenArray[i]);
    }  
    
    return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    if(c=='\n') s[i++] = '\n';
    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


int createTokenArray( const char *line, char tokenArray[][ MAXTOKENLENGTH ] )
{
    int length = 0;
    char str[ MAXLINELENGTH ]; /* make copy of line because strtok 
                                * alters the line it tokenises */
    char *tokenPtr;
    
    strcpy2(str, line);
    
    /* Splitting on newlines so the tokens do not contain them */
    tokenPtr = strtok( str, " \n" );
    
    while( tokenPtr != NULL ) {
        strcpy2( tokenArray[length++], tokenPtr );  
        tokenPtr = strtok( NULL, " \n" );
    }
         
    return length;
}


char *strcpy2( char *s1, const char *s2 )
{   
    char *result = s1;
    
    while(*s2!='\0')
        *s1++=*s2++;
        
    *s1='\0';
    return result;  
}


