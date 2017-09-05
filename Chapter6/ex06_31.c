 /*
 * Filename:    ex06_31.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/05/2017
 * Description: Bucket Sort - Space-time trade off
 *              Performs faster than bubble sort but requires more memory.
 */
 

#include <stdio.h>
#define SIZE 10


void bucketSort( int[], int );


int main()
{
    int i;
    int toSort[SIZE] = { 122, 642, 4, 322, 113, 9, 575, 44, 176, 8 };
    
    for(i=0; i<SIZE; i++)
        printf("%d ",toSort[i]);
    printf("\n");
    
    bucketSort( toSort , SIZE  );
    
    for(i=0; i<SIZE; i++)
        printf("%d ",toSort[i]);
    printf("\n");
    
    return 0;
}


void bucketSort( int toSort[], int arrLen )
{
    if(arrLen <=1)
        return;
    
    int bucket[SIZE][arrLen];
    int indexes[SIZE] = { 0 };
    
    int max = toSort[0];
    
    int i, j, row;
    int modBy = 10;
    int divBy = 1;
    
    for(i=1; i<arrLen; i++)
        if(toSort[i]>max) {
            max = toSort[i];
        }
    
    
    /* eg (3021/1)%1    == 1
     *    (3021/1)%10   == 2      
     *    (3021/1)%100  == 0  
     *    (3021/1)%1000 == 3 
     *    10000 > 3021 QUIT LOOP
     */
    
    while(divBy < max)
    {
        /* Reinitialise indexes*/
        for(i=0; i<arrLen; i++) {
            indexes[i] = 0;
        }
        
        /* Sort each item into the correct bucket */
        for(i=0; i<arrLen; i++)
        {
            row = (toSort[i]/divBy)%modBy;
            bucket[row][indexes[row]]=toSort[i];
            
            ++indexes[row];
        }
        
        /* Put the items in the buckets back into the original array */
        row = 0;
        for(i=0; i<arrLen; i++)
        {
            for(j=0; j<indexes[i]; j++)
                toSort[row++]=bucket[i][j];
        }
        
        divBy*=10;
    }
}

