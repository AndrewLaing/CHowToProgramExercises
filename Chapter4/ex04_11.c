/*
 * Filename:	ex04_11.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: Write a program that finds the smallest of
 *				several integers.Assume the first integer read specifies
 *				the number of values remaining to be entered. 
 */

#include <stdio.h>


int main()
{
    int count, num;
    int smallest = 0;
    
    printf("Enter the number of values to be entered: ");
    scanf("%d", &count);
    if(count>0) {
    	printf("Enter number: ");
        scanf("%d", &smallest);
	}
    
    while(count-- > 1) {
    	printf("Enter number: ");
    	scanf("%d", &num);
    	if(num < smallest)
    	    smallest = num;
	}
	
	printf("\nThe smallest of the entered numbers is %d\n", smallest);
    
	return 0;
}

