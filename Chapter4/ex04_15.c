/*
 * Filename:	ex04_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/04/2017
 * Description: Modify the compound interest program of Section 4.6
 *				to repeat its steps for iterest rates of 5 percent,
 *				6 percent, 7 percent, 8 percent, 9 percent, and 10 percent.
 *				Use a fdor loop to vary the interest rate.
 */

#include <stdio.h>
#include <math.h>

int main()
{
    int year, rateInt;
    double amount, principal = 1000.0, rate = 0.05;
    
    for(rateInt=5; rateInt <=10; rateInt++) 
    {
    	rate = (float)rateInt / 100;
    	
    	printf( "\n--- Interest at %d percent ---\n", rateInt );
		printf( "%4s%21s\n", "Year", "Amount on deposit" );
    	
	    for(year = 1; year <= 10; year++ )
	    {
	    	amount = principal * pow( 1.0 + rate, year );
	    	printf( "%4d%21.2f\n", year, amount );	
		}    	
	}

	return 0;
}

