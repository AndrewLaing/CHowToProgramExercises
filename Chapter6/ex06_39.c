/*
 * Filename:	ex06_39.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/05/2017
 */

#include <stdio.h>

int minimum( int[], int );


int main()
{
	int arrLen = 10;
	int array[10] = {27,5,3,6,44,15,5,7,25,14};
		    
    printf("Minimum = %d\n", minimum(array, arrLen)); 
	
    return 0;
}


int minimum( int array[], int arrLen )
{
	if(arrLen == 1)
	    return array[0];
	else if(array[0] < array[arrLen-1])
		return minimum(array, arrLen-1);
	else
	    return minimum(++array, arrLen-1); 
}

