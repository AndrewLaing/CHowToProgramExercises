/*
 * Filename:     makeWordlist.c
 * Author:       Andrew Laing
 * Email:        parisianconnections@gmail.com
 * Date:         28/07/2017.
 * Description:  Reads in a wordlist and writes out to another file all
 *               of the words of the specified length wordLen
 */
 
#include <stdio.h>

int strlen2( const char * );
char *strcpy2( char *, const char * );

int main()
{
    int wordLen = 2;
    
    char line  [ 256 ]; /* or other suitable maximum line size */
    char linec [ 256 ]; // copy of line
    
    FILE *ifPtr = fopen("sowpods.txt", "r");
    FILE *ofPtr = fopen("wordlist.txt", "w");
    
    if( ifPtr == NULL)
        printf( "\"sowpods.txt\" could not be opened.\n" );
    else if( ofPtr == NULL )
        printf( "\"wordlist.txt\" could not be opened.\n" );
    else 
    {
        while ( fgets ( line, sizeof line, ifPtr ) != NULL )
        {
            if(strlen2(line) == wordLen+1 ) {    /* +1 to include /n */
                strcpy2(linec, line);
                fprintf (ofPtr, "%s\n", linec); 
            }

        }
        
        fclose(ifPtr);
        fclose(ofPtr);          
    }

    return 0;
}



int strlen2( const char *s )
{
    int i=0;
    
    while(*s++!='\0')
        i++;

    return i;
}



char *strcpy2( char *s1, const char *s2 )
{   
    char *result = s1;
    
    while(*s2!='\0' && *s2!='\n')
        *s1++=*s2++;
        
    *s1='\0';
    return result;  
}

