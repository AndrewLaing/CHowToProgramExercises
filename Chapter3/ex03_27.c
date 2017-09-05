/*
 * Filename:	ex03_27.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	int i;
	int counter, number;
	int largest = 0, secondLargest = 0;
	
	for(i=0; i<10; i++)
	{
		printf("Input number: ");
		scanf("%d", &number);
		if(number > largest) {
			secondLargest = largest;
			largest = number;
		}
		else if(number > secondLargest)
		    secondLargest = number;
	}
    
    printf("The two largest numbers entered were %d and %d\n", secondLargest, largest);
    
	return 0;
}
