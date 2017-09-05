/*
 * Filename:	ex06_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/05/2017
 */

#include <stdio.h>
#define SIZE 10

void someFunction( const int[], int );

int main()
{
    int a[ SIZE ] = {8,3,1,2,6,0,9,7,4,5};
	
    printf("Answer is:\n");
    someFunction( a, SIZE );
    printf("\n"); 
	
    return 0;
}

void someFunction( const int b[], int size )
{
    if( size > 0)
    {
	someFunction( &b[ 1 ], size-1 );
        printf("%d  ", b[ 0 ]); 
    }
}
