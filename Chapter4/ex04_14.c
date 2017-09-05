/*
 * Filename:	ex04_14.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: The factorial function is used frequently in
 *				probability problems. The factorial of a positive
 *				integer n (written n! and pronounced n factorial) 
 *				is equal to the product of the positive integers 
 *				from from 1 to n. Write a program that calculates
 *				the factorials of the integers from 1 to 5. Print
 *				the results in tabular format. 
 */

#include <stdio.h>

int main()
{
    int factorial = 1, max = 5;
    int n;
    
    printf("N\tFactorial N\n");
    
    for(n = 1; n <= max; n++) {
    	factorial *= n;
    	printf("%d\t%d\n", n, factorial);
	}

	return 0;
}

