/*
 * Filename:    parseSMLFile.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/07/2017.
 * Notes:       Opcode must be passed as a string because if for example
 *              it was 530000 it would be converted to 53, which could
 *              be an opcode or an operand - have a splitting method already 
 *              in place for separating them
 */
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void parsefile( void );
int getFilename( char [], int );
int is_valid_int(const char *);

int main()
{   

    parsefile();
    return 0;
}


void parsefile()
{
    int lineNumber, opCode, validLine;
    int sourceLineNumber = 0;
    char line[ 100 ];
    char *linePtr;
    size_t tokenNumber = 0;
    char *tokenPtr;
    // CLEARSCREEN;
    char filename[30];
    
    printf("Enter name of file to load: ");
    getFilename(filename, 30); 

    FILE *sourceFilePtr = fopen(filename, "r");

    if( sourceFilePtr == NULL ) {
        printf("Error - unable to open file \"%s\"\n", filename);
        return;
    }
    else 
    {
        while ( fgets ( line, sizeof line, sourceFilePtr ) != NULL )
        {
            validLine = 0;
            sourceLineNumber++;
            
            linePtr = line;
            while(linePtr[0]==' ')
                linePtr++;

            tokenNumber = 0;
            tokenPtr = strtok (linePtr, " \t");
            while (tokenPtr != NULL)
            {
                if(is_valid_int( tokenPtr ) >= 0) {
                    if(tokenNumber == 0) {
                        sscanf(tokenPtr, "%d", &lineNumber);
                        validLine++;
                        printf("Line number is %d\n", lineNumber);
                    }
                    else if(tokenNumber == 1) {
                        sscanf(tokenPtr, "%d", &opCode);
                        validLine++;
                        printf("Opcode is %06d\n", opCode);
                    } 
                }
                    
                tokenPtr = strtok (NULL, " \t");
                tokenNumber++;
            }
            if(validLine==2)
                printf("linenumber=%d add %d %06d here\n", sourceLineNumber, lineNumber, opCode ); 
        }       
    }

    fclose( sourceFilePtr );
}


/* Get a filename without the newline character */
int getFilename( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


int is_valid_int(const char *str)
{
   // Handle negative numbers.
   //
   if (*str == '-' || *str=='+')
      ++str;

   // Handle empty string or just "-".
   //
   if (!*str)
      return -1;

   // Check for non-digit chars in the rest of the stirng.
   //
   while (*str)
   {
      if (!isdigit(*str))
         return -1;
      else
         ++str;
   }

   return 1;
}



