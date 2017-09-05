/*
 * Filename:	ex04_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: Write a program that calculates and prints the sum
 *				of the even integers from 2 to 30.
 */

#include <stdio.h>


int main()
{
    int sum = 0, number;
    
    for(number = 2; number <= 30; number += 2)
        sum += number;
    
	printf("Sum is %d\n", sum );

	return 0;
}

