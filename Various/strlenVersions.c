/*
 * Filename:	ex08_33.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/07/2017.
 */

#include <stdio.h>

/* Using array subscripting */
int strlen1( const char* );

/* Using pointer arithmetic */
int strlen2( const char* );

int main()
{	
    char test1[] = "This is only a test string ok";
    char test2[] = "This is a longer test string than the first one";

    printf("---- strlen1 ----\n");
    printf("test1 length = %d\n", strlen1( test1 ));
    printf("test2 length = %d\n", strlen1( test2 ));

    printf("\n---- strlen2 ----\n");
    printf("test1 length = %d\n", strlen2( test1 ));
    printf("test2 length = %d\n", strlen2( test2 ));
 	return 0;
}

/* Using array subscripting */
int strlen1( const char* s )
{
    int i=0;
    
	while(s[i]!='\0')
		i++;

	return i;
}

/* Using pointer arithmetic */
int strlen2( const char* s )
{
    int i=0;
    
	while(*s++!='\0')
		i++;

	return i;
}
