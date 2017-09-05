/*
 * Filename:	getAsciiCode.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/08/2017
 */
 
#include <stdio.h>

int main()
{
	char c;
    printf("Enter a character: ");
    c=getchar();
    fflush(stdin);
    printf("%c = %d", c, c );

	return 0;
}


