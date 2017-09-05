/*
 * Filename:    ex05_37.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/05/2017
 */

#include <stdio.h>

int power( int, int );


int main()
{
    int n=3, exp=4;

    printf("power(3,4) = %d\n", power(n, exp));

    return 0;
}


int power( int num, int exponent)
{
    if(exponent==1) {
        return num;
    }
    else
        return num * power(num, exponent-1);
}

