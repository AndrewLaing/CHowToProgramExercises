/*
 * Filename:	ex05_11.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/04/2017
 */

#include <stdio.h>
#include <math.h>


void roundToInteger( float );
void roundToTenths( float );
void roundToHundreths( float );
void roundToThousandths( float );


int main()
{
	int i;
	float num;

    for(i=0; i<4; i++)
    {
	    printf("Enter the value of x: ");
		scanf("%f", &num);
		roundToInteger(num);
		roundToTenths(num);
		roundToHundreths(num);
		roundToThousandths(num);    	
	}

	return 0;
}


void roundToInteger(float number) {
	float rounded = floor(number + .5);
	printf("original = %f  Rounded to Integer = %.0f\n", number, rounded);
}

void roundToTenths(float number) {
	float rounded = floor(number * 10 + .5) / 10;
	printf("original = %f  Rounded to Tenth = %.1f\n", number, rounded);
}

void roundToHundreths(float number) {
	float rounded = floor(number * 100 + .5) / 100;
	printf("original = %f  Rounded to Hundredth = %.2f\n", number, rounded);
}

void roundToThousandths(float number) {
	float rounded = floor(number * 1000 + .5) / 1000;
	printf("original = %f  Rounded to Thousandth = %.3f\n", number, rounded);
}

