/*
 * Filename:	ex02_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/04/2017
 * Description: Write a program that inputs three different integers from 
 * 				the keyboard, then prints the sum, the average, the product,
 *				the smallest and the largest of these numbers. 
 *				Use only the single-selection form of the if statement
 *				you learned in this chapter. The screen dialogue should
 *				appear as follows;
 *
 *					Input three different integers: 13 27 14
 *					Sum is 54
 *					Average is 18
 *					Product is 4914
 *					Smallest is 13
 *					Largest is 27
 */

#include <stdio.h>

int sum( int, int, int );
int average( int, int, int );
int product( int, int, int );
int smallest( int, int, int );
int largest( int, int, int );


int main()
{
	int num1, num2, num3;
	
	/* Get three numbers from the user */
	printf( "Input three different integers: " );
	scanf("%d%d%d", &num1, &num2, &num3);
	
	printf( "Sum is %d\n", sum(num1, num2, num3) );
	printf( "Average is %d\n", average(num1, num2, num3) );	
	printf( "Product is %d\n", product(num1, num2, num3) );
	printf( "Smallest is %d\n", smallest(num1, num2, num3) );
	printf( "Largest is %d\n", largest(num1, num2, num3) );

	return 0;
}


/* The method sum calculates and returns the sum of the
 * three numbers passed to it 
 */
int sum(int num1, int num2, int num3)
{
	return num1 + num2 + num3;
}

/* The method average calculates and returns 
 * the average of the three numbers passed to it 
 */
int average(int num1, int num2, int num3)
{
	return (num1+num2+num3)/3;
}


/* The method sum calculates and returns the product of the
 * three numbers passed to it 
 */
int product(int num1, int num2, int num3)
{
	return num1 * num2 * num3;
}

/* The method smallest returns the smallest
 * of the three numbers passed to it 
 */
int smallest(int num1, int num2, int num3)
{
	if(num1 < num2)
	{
		if(num1 < num3) {
			return num1;
		}
		else {
			return num3;
		}
	}
	
	if(num2 < num3)
	    return num2;
	
	return num3;
}


/* The method largest returns the largest
 * of the three numbers passed to it 
 */
int largest(int num1, int num2, int num3)
{
	if(num1 > num2)
	{
		if(num1 > num3) {
			return num1;
		}
		else {
			return num3;
		}
	}
	
	if(num2 > num3)
	    return num2;
	
	return num3;
}

