/*
 * Filename:    ex06_35.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/05/2017
 * Description: Binary Search
 */

#include <stdio.h>
#define SIZE 15

int binarySearch( const int[], int, int, int );


int binarySearch( const int b[], int searchKey, 
                  int low, int high )
{
    if(high < low || low > high)
        return -1; 
        
    int middle = (low+high)/2;    
        
    if( searchKey == b[ middle ] )
        return middle;
    else if( searchKey < b[ middle ] )
        return binarySearch ( b, searchKey, low, middle-1 );
    else
        return binarySearch ( b, searchKey, middle+1, high );
}


int main()
{
    int a[ SIZE ], i, key, result;
    
    for(i=0; i<=SIZE-1; i++)
        a[ i ] = 2 * i;
        
        
    for(i=0; i<=SIZE-1; i++)
        printf("%d ",a[ i ]);
    printf("\n");
    
    printf( "Enter a number between 0 and 28: ");
    scanf("%d", &key);
    
    result = binarySearch( a, key, 0, SIZE-1 );
    
    if( result != -1 )
        printf( "\n%d found in array element %d\n", 
                key, result );
    else
        printf( "\n%d not found\n", key ); 
    
    return 0;
}




