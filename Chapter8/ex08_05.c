/*
 * Filename:    ex08_05.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: Using the character handling library ctype.h
 */

#include <stdio.h>
#include <string.h>   /* Used for strlen */
#include <ctype.h>

char inputCharacter( void );

char inputCharacter( void )
{
    char c, sentence[2];
    int i = 0;
    
    puts( "Enter a character: " );
    
    while(( c=getchar() ) != '\n')
        sentence[i++] = c;
        
    if( c=='\n')
        sentence[i++] = c;
    sentence[i] = '\0';
    
    if(strlen(sentence)>0)
        c = sentence[0];
    else
        c = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return c;
}


int main()
{       
    char c = inputCharacter(); 
    printf( "\nThe character entered was: %c\n", c );
    
    printf("\'%c\'%s%s\n",
          c, (isalnum(c) ? " is " : " is not "), "alphabetic or numeric");
    printf("\'%c\'%s%s\n",
          c, (isalpha(c) ? " is " : " is not "), "a letter");
    printf("\'%c\'%s%s\n",
          c, (iscntrl(c) ? " is " : " is not "), "a control character");
    printf("\'%c\'%s%s\n",
          c, (isdigit(c) ? " is " : " is not "), "a number");     
    printf("\'%c\'%s%s\n",
          c, (isgraph(c) ? " is " : " is not "), "a printing character except SPACE");     
    printf("\'%c\'%s%s\n",
          c, (islower(c) ? " is " : " is not "), "lowercase");     
    printf("\'%c\'%s%s\n",
          c, (isprint(c) ? " is " : " is not "), "a printing character including space");            
    printf("\'%c\'%s%s\n",
          c, (ispunct(c) ? " is " : " is not "), "a printing character except SPACE or letter or digit");     
    printf("\'%c\'%s%s\n",
          c, (isspace(c) ? " is " : " is not "), "a whitespace character");        
    printf("\'%c\'%s%s\n",
          c, (isupper(c) ? " is " : " is not "), "uppercase");     
    printf("\'%c\'%s%s\n",
          c, (isxdigit(c) ? " is " : " is not "), "a hexadecimal digit");  
    return 0;
}


