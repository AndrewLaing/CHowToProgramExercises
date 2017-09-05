/*
 * Filename:	ex03_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	int i;
	int counter, number;
	int largest = 0;
	
	for(i=0; i<10; i++)
	{
		printf("Input number: ");
		scanf("%d", &number);
		
		if(number > largest)
		    largest = number;
	}
    
    printf("The largest number entered was %d", largest);
    
	return 0;
}

