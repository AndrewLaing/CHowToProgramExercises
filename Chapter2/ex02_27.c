/*
 * Filename:	ex02_27.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Display the checkerboard pattern with eight printf
 *				statements and then display the same pattern with as 
 *				few printf statements as possible.
 */

#include <stdio.h>


int main()
{
	printf( "--VERSION ONE--\n\n" );
	
	printf( "* * * * * * * *\n" );
	printf( " * * * * * * * *\n" );
	printf( "* * * * * * * *\n" );
	printf( " * * * * * * * *\n" );	
	printf( "* * * * * * * *\n" );
	printf( " * * * * * * * *\n" );
	printf( "* * * * * * * *\n" );
	printf( " * * * * * * * *\n\n" );	

	printf( "--VERSION TWO--\n\n" );

    char* pattern;
    int i;
    for(i=2; i<10; i++) {
    	pattern = (i%2 == 0) ? "* * * * * * * *\n" : " * * * * * * * *\n";
    	printf(pattern);
	}


	return 0;
}
