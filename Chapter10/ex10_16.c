/*
 * Filename:    ex10_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/07/2017.
 */

#include <stdio.h>

unsigned packCharacters( char, char, char, char );
void unpackCharacters( unsigned );
void displayBits( unsigned );


int main()
{    
    char a, b, c, d;
    unsigned result;
    
    printf("Enter character 1: ");
    scanf("%c", &a);
    fflush(stdin);
    
    printf("Enter character 2: ");
    scanf("%c", &b);
    fflush(stdin);
    
    printf("Enter character 3: ");
    scanf("%c", &c);
    fflush(stdin);
    
    printf("Enter character 4: ");
    scanf("%c", &d);
    fflush(stdin);
    
    printf("%c before = ", a);
    displayBits( a );
    printf("%c before = ", b);
    displayBits( b );
    printf("%c before = ", c);
    displayBits( c );
    printf("%c before = ", d);
    displayBits( d );
    
    result = packCharacters(a, b, c, d); 
    printf("Result   = ");
    displayBits( result );
    
    printf("\nUnpacking ...\n");
    unpackCharacters( result );
    return 0;
}


void unpackCharacters( unsigned packed )
{
    unsigned temp = packed;
    unsigned mask=255;
    mask <<= 24;
    
    char a,b,c,d;
    temp &= mask;
    temp>>=24;
    a = temp;
    
    temp = packed;
    mask >>= 8;
    temp &= mask;
    temp>>=16;
    b = temp;
    
    temp = packed;
    mask >>= 8;
    temp &= mask;
    temp>>=8;
    c = temp;
    
    temp = packed;
    mask >>= 8;
    temp &= mask;
    d = temp;
    
    printf("a = %c\nb = %c\n", a, b);
    printf("c = %c\nd = %c\n", c, d);
    printf("%c = ", a);
    displayBits( a );
    printf("%c = ", b);
    displayBits( b );
    printf("%c = ", c);
    displayBits( c );
    printf("%c = ", d);
    displayBits( d );
}


unsigned packCharacters( char a, char b, char c, char d )
{
    unsigned result = a;
    
    result <<=8;
    result|=b;
    result <<=8;
    result|=c;
    result <<=8;
    
    return result|=d;  /* Inclusive OR */
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


