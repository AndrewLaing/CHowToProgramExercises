/*
 * Filename:    ex07_25.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Maze Traversal - Using the right hand against wall method
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    /* For toupper() */

int getLine( char [], int );


int isHexString(char []);
void getHexString(char []);



int isHexString(char hex[])
{
    int i;
    char c;
    for(i=0; i<6; i++)
    {
        c = hex[i];
        if(c=='\n')
        {
            hex[i]='\0';
            return 1;
        }
        if(c<48 || c>57)
        {
            if(c<65 || c>70) 
                return -1;
        }
    }
    return 1;
}


void getHexString(char hex[7])
{
    int length;
    while(length!=6)
    {
    printf("Enter hex string > ");
    length = getLine(hex, 7);   /* Include null byte */
    
    if(length<6)
        printf("*** Error - Hex string must be 6 chars long ***\n");
        
    if(isHexString(hex)==-1) {
        printf("*** Error - %s is not a valid hex string ***\n", hex);
        length = 0;
    }
            
    }
    
};

int main()
{
    char str[7];

    getHexString(str);
    /* Print as hex using %x */
    printf("str1 = %s\n", str); 
          
    return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=toupper(c);

    if(c=='\n')
        s[i++]=c;
    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


