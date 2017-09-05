/*
 * Filename:	ex03_32.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	int x, y;
	
	printf( "Enter values for x and y: " );
	scanf( "%d%d", &x, &y );
	
	// pattern one
	if( y == 8 ) {
		if( x == 5 )
        	printf("@@@@@\n");	
	}
	else
	    printf("#####\n");
	printf("$$$$$\n");
	printf("&&&&&\n");

    printf("--------------------------------------\n\n");


	// pattern two
	if( y == 8 ) {
	    if( x == 5 )
	        printf("@@@@@\n");
    }
	else {
		printf("#####\n");
	    printf("$$$$$\n");
	    printf("&&&&&\n");
	}

    printf("--------------------------------------\n\n");


	// pattern three
	if( y == 8 ) {
		if( x == 5 )
        	printf("@@@@@\n");
	}
	else {
		printf("#####\n");
	    printf("$$$$$\n");
	}

	printf("&&&&&\n");


	return 0;
}

