/*
 * Filename:     linearSearchFile.c
 * Author:       Andrew Laing
 * Email:        parisianconnections@gmail.com
 * Date:         29/07/2017.
 */
 
#include <stdio.h>

int strlen2( const char * );
char *strcpy2( char *, const char * );
int strcmp2( const char *, const char * );

int main()
{
    char line  [ 256 ]; /* or other suitable maximum line size */
    char *query = "TESTING";
    int res;
    FILE *searchFPtr = fopen("7LetterWordlist.txt", "r");

    if( searchFPtr == NULL )
        printf( "Search file could not be opened.\n" );
    else 
    {
        while ( fgets ( line, sizeof line, searchFPtr ) != NULL )
        {
            res = strcmp2(  line, query );
            if(res==0) {
                printf("%s found in file\n", query);
                break;
            } else if(res>0) {
                printf("quitting on word %s\n", line);
                printf("%s not found in file\n", query);
                break;
            }
                
        }
        
        fclose( searchFPtr );       
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


int strcmp2( const char *s1, const char *s2 )
{      
    while(*s2!='\0') {
        if(*s1<*s2)
            return -1;
        else if(*s1>*s2)
            return 1;
        s1++;
        s2++;           
    }

    return 0;   
}


