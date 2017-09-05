/*
 * Filename:	ex08_06.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: Using gets, tolower, and toupper
 */

#include <stdio.h>
#include <string.h>   /* Used for strlen */
#include <ctype.h>



int main()
{	
    int i = 0;    
    char s[100];
	
	printf("Enter a line of text: ");
	gets( s );
	 
    while(s[i]!='\0')
        printf("%c", tolower(s[i++]));
    printf("\n");

    i = 0;
    while(s[i]!='\0')
        printf("%c", toupper(s[i++]));
    printf("\n");

 	return 0;
}


