/*
 * Filename:    ex05_29.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/05/2017
 * Description: Greatest Common Denominator
 */

#include <stdio.h>


int gcd( int, int );


int main()
{
    int a, b;
    
    printf("Enter the first number: ");
    scanf("%d", &a);
    
    printf("Enter the second number: ");
    scanf("%d", &b);
    
    printf("The gcd = %d\n", gcd( a, b ));

    return 0;
}


int gcd( int a, int b )
{
    if(a%b==0)
        return b;
    else
        return gcd(b, a%b);
}

