/*
 * Filename:    ex03_39.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>

int numberOfSevens( int );


int main()
{
    int num;
    
    /* Get a number from the user */
    printf( "Input a number: " );
    scanf("%d", &num);
    
    /* display the binary version */
    printf("The number of sevens in your number is %d\n", numberOfSevens(num) );

    return 0;
}


/* binToDecimal converts a binary number to a decimal
 * and returns the result.. */
int numberOfSevens(int num) 
{
    int total = 0;
    int remainder;
    
    while(num > 0) {
        remainder = num % 10;
        num /= 10;
        
        if(remainder == 7)
            total++;
    }
    
    return total;
}

