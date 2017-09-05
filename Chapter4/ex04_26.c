/*
 * Filename:	ex04_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        22/04/2017
 * Description: Calculate pi
 */

#include <stdio.h>

float calculatePi( int );


int main()
{   
    int i;

    for(i=2; i<200000; i++)
    {
    	printf("Pi calculated using %d terms = %f\n", i, calculatePi(i));
	}

	return 0;
}


float calculatePi(int terms) 
{
    int i;
    float pi = 4;
    float divisor = 3;
    for(i=0; i<terms; i++) {
    	if(i%2==0) 
    		pi -= (4.0/divisor);
    	else
    		pi += (4.0/divisor);
        	
        divisor += 2.0;
	}
	
	return pi;
}

