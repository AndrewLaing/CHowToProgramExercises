/*
 * Filename:    ex03_36.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>

int binToDecimal( int ); 


int main()
{
    int num;
    
    /* Get a number from the user */
    printf( "Input a binary number: " );
    scanf("%d", &num);
    
    /* display the binary version */
    printf("The decimal version is %d\n", binToDecimal(num) );

    return 0;
}

/* binToDecimal converts a binary number to a decimal
 * and returns the result.. */
int binToDecimal(int num) 
{
    int total = 0;
    int multiplier = 1;
    int remainder;
    
    while(num > 0) {
        remainder = num % 10;
        num /= 10;
        total += remainder * multiplier;
        multiplier *= 2;
    }
    
    return total;
}

