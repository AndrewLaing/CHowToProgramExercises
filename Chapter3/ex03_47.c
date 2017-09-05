/*
 * Filename:	ex03_47.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/04/2017
 */

#include <stdio.h>


int factorial( int );
float estimateE( int );
float calculateEX( int );


int main()
{
	int num;
	
	printf( "Enter a number and I will tell you its factorial\n" );
	printf( "and use it to estimate e, and calculate\n" );
	printf( "the value of e to the power of x: " );
	scanf( "%d", &num );
	
	if( num < 1 ) {
		printf( "Error - number must be 1 or greater\n");
		return 0;
	}
    	
    printf( "Factorial       =  %d\n",factorial(num) );
    printf( "Estimation of e =  %f\n",estimateE(num) );    
    printf( "Value of e to the power of x = %f\n",calculateEX(num) );

	return 0;
}


int factorial(int n)
{
	int factorial = 1;
    
	while(n>1) {
    	factorial *= n;
    	n--;
	}
	
	return factorial;
}


float estimateE(int n)
{
	float estimate = 2.0;
	
	while(n>1) {
    	estimate += ( 1.0 / (float)(factorial(n)) );
    	n--;
	}
	
	return estimate;
}

float calculateEX(int n)
{
	int x = 2;
	int numerator = n;
	float result = 1 + numerator / 1.0;
	
	while(x <= n) 
	{	
		numerator *= n;
		
    	result += ( (float)numerator / (float)(factorial(x)) );
    	x++;
	}
	
	return result;
}


