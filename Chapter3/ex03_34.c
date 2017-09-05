/*
 * Filename:	ex03_34.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	int size, i, j;
	
	printf( "Enter size of square: " );
	scanf( "%d", &size );
	
	if(size < 1 || size > 20) {
		printf("Size must be in the range 1 through 20");
		return 0;
	}
	
    for(i=0; i<size; i++) 
	{
        for(j=0; j<size; j++) 
		{
        	if(i==0 || i==size-1)
    	        printf("*");
    	    else if(j==0 || j==size-1)
    	        printf("*");
    	    else
    	        printf(" ");
    	}
    	printf("\n");
	}


	return 0;
}

