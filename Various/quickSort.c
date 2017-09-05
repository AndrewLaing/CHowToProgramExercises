/*
 * Filename:    quickSort.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Quick sort
 */

#include <stdio.h>
#define ARRLEN 10

void quickSort(int *, int );
void doQuickSort(int *, int, int );
int partition(int *, int, int );
void swap(int *, int, int );

// Methods /////////////////////////////////

int main()
{
    int array[ARRLEN] = { 37, 2, 6, 4, 89, 8, 10, 12, 68, 45 };    
    int i;
    
    printf("Before sorting:\n");
    for(i=0; i<ARRLEN; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    quickSort(array, ARRLEN);
    
    printf("After sorting:\n");
    for(i=0; i<ARRLEN; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    return 0;
}


/* Start off the quicksort algorithm */
void quickSort(int *array, int arrayLength)
{
    doQuickSort(array, 0, arrayLength-1); 
}


void doQuickSort(int *array, int start, int end)
{
    int pivotPoint;
    
    /* Base case - if start=end then it is sorted */
    if(start < end)
    {
        pivotPoint = partition(array, start, end);
        
        /* Sort the sublist on the lhs of the pivot point */
        doQuickSort(array, start, pivotPoint-1);
        
        /* Sort the sublist on the rhs of the pivot point */
        doQuickSort(array, pivotPoint+1, end);      
    }
}


/* Finds the correct position of the start element in the array 
 * by swapping with elements smaller the larger. Partition returns
 * this index position */
int partition(int *array, int start, int end)
{
    int i, swapped=1;
    int pivotPoint=start;
    
    while(swapped==1)
    {
        swapped=0;
        for(i=end; i>pivotPoint; i--) {
            if(array[i] < array[pivotPoint]) 
            {
                swap(array, pivotPoint, i);
                pivotPoint = i;
                swapped = 1;
            }
        }
        for(i=start; i<pivotPoint; i++) {
            if(array[i] > array[pivotPoint]) {
                swap(array, pivotPoint, i);
                pivotPoint = i;
                swapped = 1;
            }
        }
    }
    
    return pivotPoint;
}


/* Swap the element at index A with the element at index B */
void swap(int *array, int indexA, int indexB)
{
    int temp = array[indexA];
    array[indexA] = array[indexB];
    array[indexB] = temp;
}

