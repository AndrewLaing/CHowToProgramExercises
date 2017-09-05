/*
 * Filename:	ex06_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/05/2017
 */

#include <stdio.h>
#define SIZE 10

int whatIsThis( const int[], int );


int main()
{
	int x, a[ SIZE ] = {1,2,3,4,5,6,7,8,9,10};
	
	x = whatIsThis( a, SIZE );
	printf("Result is %d\n", x);
	
    return 0;
}

int whatIsThis( const int b[], int p )
{
	if(p==1)
    	return b[0];
    else
        return b[p-1] + whatIsThis(b, p-1); 
}
 
