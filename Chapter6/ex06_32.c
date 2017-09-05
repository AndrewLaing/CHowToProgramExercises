 /*
 * Filename:	ex06_32.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/05/2017
 * Description: Selection Sort
 */
 

#include <stdio.h>
#define SIZE 10

void selectionSort( int[], int );


int main()
{
	int i;
	int toSort[SIZE] = { 122, 642, 4, 322, 113, 9, 575, 44, 176, 8 };
	
	for(i=0; i<SIZE; i++)
	    printf("%d ",toSort[i]);
	printf("\n");
	
    selectionSort( toSort , SIZE  );
    
    for(i=0; i<SIZE; i++)
	    printf("%d ",toSort[i]);
	printf("\n");
	
    return 0;
}


void selectionSort( int toSort[], int arrLen )
{
    if(arrLen <= 1)
        return;

    int i, index, temp;    
    int smallest = toSort[0];

    for(i=1; i<arrLen; i++) 
	{
    	if(toSort[i] < smallest) {
    		smallest = toSort[i];
    		index = i;
		}
	}
	
	if(smallest < toSort[0]) {
		temp = toSort[0];
		toSort[0] = smallest;
		toSort[index] = temp;
	}
	
	/* Note: pointer augmentation points to the next item in the array */
	selectionSort( ++toSort, arrLen-1 );
}

