/*
 * Filename:    ex10_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/07/2017.
 */

#include <stdio.h>

unsigned packCharacters( char, char, char, char );
void unpackCharacters( unsigned );
void displayBits( unsigned );
void displayBitsReeversed( unsigned );


int main()
{    
    unsigned result = 1135;
    printf("Original bits:\n");
    displayBits( result );
    
    printf("Reversed bits:\n");
    displayBitsReversed( result );

    return 0;
}



void displayBits( unsigned value )
{
    unsigned c, displayMask = 1<<31;
    
    for( c=1; c<=32; c++ )
    {
        putchar( value & displayMask ? '1' : '0' );
        value <<= 1;
        
        if(c % 8 == 0)
            putchar( ' ' );
    }
    
    putchar( '\n' );
}


void displayBitsReversed( unsigned value )
{
    unsigned c, displayMask = 1;
    
    for( c=1; c<=32; c++ )
    {
        putchar( value & displayMask ? '1' : '0' );
        value >>= 1;
        
        if(c % 8 == 0)
            putchar( ' ' );
    }
    
    putchar( '\n' );
}

