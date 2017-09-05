/*
 * Filename:	ex04_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: Write a program that sums a sequence of Integers.
 *				Assume the first integer read with scanf specifies
 *				the number of values remaining to be entered. Your 
 *				program should read only one value each time scanf 
 *				is executed. A typical input sequence might be
 *					5 100 200 300 400 500
 *				where the 5 indicates that the subsequent 5 values
 *				are to be summed. 
 */

#include <stdio.h>


int main()
{
    int count, num;
    int sum = 0;
    
    printf("Enter the number of values to be entered: ");
    scanf("%d", &count);
    
    while(count-- > 0) {
    	printf("Enter number: ");
    	scanf("%d", &num);
    	sum += num;
	}
	
	printf("\nThe sum of the entered numbers is %d\n", sum);
    
	return 0;
}

