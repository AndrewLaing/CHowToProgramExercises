/*
 * Filename:    ex11_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        30/07/2017.
 */

#include <stdio.h>

int main(int argc, char **argv)
{      
    FILE *ifPtr = stdin;
    FILE *ofPtr = stdout;

    printf("argc = %d\n", argc); 

    char c, sentence[120];
    int i = 0;
    
    
    if(argc < 2)
        fputs( "Enter a line of text: ", ofPtr );
    else if(argc > 1) {
        if ( ( ifPtr = fopen( argv[1], "r" ) ) == NULL )
        {
            printf("Error - unable to open file \"%s\"\n", argv[1]);
            return -1;
        }
        
        if(argc > 2) {
            if ( ( ofPtr = fopen( argv[2], "w" ) ) == NULL )
            {
                printf("Error - unable to open file \"%s\"\n", argv[2]);
                return -1;
            }
        }   
    }
    
    if(argc < 2) 
    {
        while(( c=fgetc(ifPtr) ) != '\n')
            sentence[i++] = c;
            
        sentence[i] = '\0';
        
        fputs( "\nThe line entered was: ", ofPtr );
        fputs( sentence, ofPtr );        
    }
    else 
    {
        while(( c=fgetc(ifPtr) ) != EOF) {
            sentence[i++] = c;
            if(c=='\n') {
                sentence[i] = '\0';
                i = 0;
                fputs( sentence, ofPtr ); 
            }
        }
        sentence[i] = '\0';
        fputs( sentence, ofPtr ); 
    }

    return 0;
}


