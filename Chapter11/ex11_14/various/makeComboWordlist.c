/*
 * Filename:	 makeWordlist.c
 * Author:       Andrew Laing
 * Email:        parisianconnections@gmail.com
 * Date:         28/07/2017.
 * Description:  Reads in a wordlist and writes out to another file all
 *				 of the words of the specified length wordLen
 */
 
#include <stdio.h>

int strlen2( const char * );
char *strcpy2( char *, const char * );

int main()
{
    char line  [ 256 ]; /* or other suitable maximum line size */
    char linea [ 256 ];
    char lineb [ 256 ];
    char linec [ 256 ]; // copy of line
	
    FILE *headFPtr = fopen("2LetterWordlist.txt", "r");
    FILE *tailFPtr = fopen("5LetterWordlist.txt", "r");
    FILE *ofPtr = fopen("newWordlist.txt", "w");
    
    if( ofPtr == NULL )
        printf( "Output file could not be opened.\n" );
    else if( headFPtr == NULL )
        printf( "Head wordlist could not be opened.\n" );
    else if( tailFPtr == NULL )
        printf( "Tail wordlist could not be opened.\n" );
    else 
	{
		while ( fgets ( linea, sizeof linea, headFPtr ) != NULL )
		{
		    strcpy2( lineb, linea );
		    rewind( tailFPtr );
		    
			while ( fgets ( line, sizeof line, tailFPtr) != NULL )
			{
				strcpy2(linec, line);
	            fprintf (ofPtr, "%s%s\n", lineb, linec);	
			}
	    }
	    
	    fclose( ofPtr );
	    fclose( headFPtr );	
		fclose( tailFPtr );		
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

