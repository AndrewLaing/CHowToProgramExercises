/*
 * Filename:    ex05_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 * Description: Calculate Integer exponent
 */

#include <stdio.h>


int integerPower(int base, int exponent);


int main()
{
    int base, exponent, result;
    
    printf("Enter the base: ");
    scanf("%d", &base);
    
    printf("Enter the exponent: ");
    scanf("%d", &exponent);
    
    result = integerPower(base, exponent);
    printf("The result is %d\n", result); 
    
    return 0;
}


int integerPower(int base, int exponent)
{
    int result = base;
    int i;
    
    for(i=1; i<exponent; i++)
        result *= base;
    
    return result; 
}

