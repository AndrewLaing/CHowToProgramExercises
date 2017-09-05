/*
 * Filename:	ex10_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/07/2017.
 */

#include <stdio.h>

int power2( int, int );
void displayBits( unsigned );

int main()
{	 
    int result, number=6, pow=4;
    
    result = power2(number, pow); 
    printf("power2(6, 4) = %d\n", result);
    
    displayBits( result );
	return 0;
}


int power2(int number, int pow)
{
	return number * (2<<pow);
}

void displayBits( unsigned value )
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


