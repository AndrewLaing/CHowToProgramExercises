/*
 * Filename:	ex06_37.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/05/2017
 */

#include <stdio.h>
#define SIZE 15

void printArray( int[], int );


int main()
{
	int i, array[ SIZE ];
	
	/* Initialise array */
	for(i=0; i<=SIZE-1; i++)
	    array[ i ] = 2 * i;
	    
	printArray(array, SIZE); 
	
    return 0;
}


void printArray( int array[], int arrLen )
{
    if(arrLen==0) {
    	return;
	}
	else {
		printf("%d ", array[0]);
		printArray(++array, arrLen-1); 
	}
}

