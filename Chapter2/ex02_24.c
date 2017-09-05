/*
 * Filename:	ex02_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program that reads an integer and determines
 *				and prints whther it is odd or even.
 *				Note: No booleans in C. A comparison returns 1 for true
 *				      or 0 for false;
 */

#include <stdio.h>


/* The method isEven returns 1 if the number is even,
 * otherwise it returns 0
 */
int isEven(int num)
{
    return num%2==0;
}


int main()
{
	int num;
	
	/* Get a number from the user */
	printf( "Input a number: " );
	scanf("%d", &num);
	
	/* 0 is false */
	if(isEven(num))
	    printf( "%d is even.\n", num );
	else
	    printf( "%d is odd.\n", num );

	return 0;
}
