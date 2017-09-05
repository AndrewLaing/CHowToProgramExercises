/*
 * Filename:    ex10_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        22/07/2017.
 * Returns 0 if the integer contains an odd number of bits, else 1
 * eg 3 (0011) has an even number of bits so returns 1
 *    8 (1000) has an odd number of bits so returns 0
 */
 
#include <stdio.h>

int mystery( unsigned bits );


int main()
{    
    unsigned x;
    
    printf("Enter an integer: ");
    scanf("%u", &x);
    printf("The result is %d\n", mystery(x) );

    return 0;
}

int mystery( unsigned bits )
{
    int i, mask=1<<31, total=0;
    
    for( i=1; i<=32; i++, bits<<=1 )
        if( (bits & mask ) == mask ) {
            ++total;
        }
    
    return !( total % 2) ? 1 : 0;
}
