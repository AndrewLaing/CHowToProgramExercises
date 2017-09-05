/*
 * Filename:	ex05_42.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/05/2017
 */

#include <stdio.h>
int DEBUG = 1;
int start = 1;

int gcd( int, int );

int main()
{
    printf("gcd(81, 9) = %d\n", gcd(81, 9));
    printf("gcd(7, 21) = %d\n", gcd(7, 21));
	printf("gcd(17, 6) = %d\n", gcd(17, 6));
    printf("gcd(116, 96) = %d\n", gcd(116, 96));   

	return 0;
}

int gcd( int x, int y)
{
    if(y==0)
        return x;
    else
        return gcd(y, x%y);
}

