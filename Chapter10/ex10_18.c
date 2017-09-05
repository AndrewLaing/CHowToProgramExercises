/*
 * Filename:    ex10_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/07/2017.
 */
 
#include <stdio.h>

void displayBits( unsigned );

int main()
{    
    unsigned x;
    
    printf("Enter an unsigned number: ");
    scanf("%u", &x);
    fflush(stdin);
    displayBits(x);
    
    return 0;
}


void displayBits( unsigned value )
{
    unsigned c, displayMask, max;
    
    int intSize = sizeof(int);
    max = intSize*8; 
    displayMask = 1<<(max-1);
    printf("This system uses %d-byte integers\n", intSize);

    
    printf( "%7u = ", value );
    
    for( c=1; c<=max; c++ )
    {
        putchar( value & displayMask ? '1' : '0' );
        value <<= 1;
        
        if(c % 8 == 0)
            putchar( ' ' );
    }
    
    putchar( '\n' );
}


