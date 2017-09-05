/*
 * Filename:	ex10_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/07/2017.
 */

#include <stdio.h>

void displayBits( int );

int main()
{	 
    int number1;
    
    number1 = 65535;
    printf("The result of right shifting the following\n");
    displayBits( number1 );
    printf("is\n");
    displayBits( number1 >> 4 ); 

	return 0;
}


void displayBits( int value )
{
	unsigned c, displayMask = 1<<31;
	
	printf( "%7u = ", value );
	
	for( c=1; c<=32; c++ )
	{
		putchar( value & displayMask ? '1' : '0' );
		value <<= 1;
		
		if(c % 8 == 0)
		    putchar( ' ' );
	}
	
	putchar( '\n' );
}


