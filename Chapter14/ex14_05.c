/*
 * Filename:    ex14_05.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        29/10/2017
 * Description: file processing
 *              tmpfile() creates a temporary file which is opened in wb+
 *                        this file file is destroyed after its filePtr is
 *                        closed or the program terminates
 */
 
#include <stdio.h>


int main( int argc, char *argv[])
{
    FILE *filePtr, *tempFilePtr;
    int c;
    char fileName[30];
    
    printf("This program adds a space after every chararcter.\n"
           "Enter a file to be modified: ");
    scanf("%s", fileName);
    
    if( (filePtr = fopen( fileName, "r+" ) ) != NULL  )
        if( ( tempFilePtr = tmpfile() ) != NULL  ) 
        {
            while( (c = getc( filePtr ) ) != EOF ) {
                putchar( c );
                putc( c, tempFilePtr );
                putc( ' ', tempFilePtr );
            }
            
            rewind( tempFilePtr );
            rewind( filePtr );
            printf("\n\nThe file after modification is:\n");
            
            while( (c = getc( tempFilePtr  ) ) != EOF ) {
                putchar( c );
                putc( c, filePtr );
            }            
        }
        else
            printf("Unable to open temporary file\n");
    else
        printf("Unable to open %s\n", fileName);

    fclose(tempFilePtr);
    fclose(filePtr);
    
    return 0;
}


