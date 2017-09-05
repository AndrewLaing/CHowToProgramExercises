/*
 * Filename:	ex09_13.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        17/07/2017.
 */

#include <stdio.h>

double fahrenheitToCelsius( double fahrenheit );

int main()
{	
    int i;
    for(i=0; i<=212; i++)
        printf("%10d%+10.3f\n", i, fahrenheitToCelsius(i) );

	return 0;
}


double fahrenheitToCelsius( double fahrenheit )
{
	return (fahrenheit-32)/1.8;
}


