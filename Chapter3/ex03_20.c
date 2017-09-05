/*
 * Filename:	ex03_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/04/2017
 */

#include <stdio.h>

int main()
{
	float principal, rate, days, interest;
	const int yearInDays = 365;
    
    printf( "Enter loan principal (-1 to end): " );
    scanf( "%f", &principal );

    while( (int)principal != -1) 
    {
	    printf( "Enter interest rate: " );
	    scanf( "%f", &rate );
        printf( "Enter term of the loan in days: " );
   		scanf( "%f", &days );

        interest = principal * rate * days / yearInDays;
    	printf( "The interest charge is $%.2f\n", interest );

	    printf( "\n\nEnter loan principal (-1 to end): " );
	    scanf( "%f", &principal );
	}

	return 0;
}

