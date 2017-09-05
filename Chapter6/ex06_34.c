/*
 * Filename:    ex06_34.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/05/2017
 */

#include <stdio.h>
#define SIZE 100

int linearSearch( const int[], int, int );


int main()
{
    int a[ SIZE ], x, searchKey, element;
    
    for(x=0; x<=SIZE-1; x++)
        a[ x ] = 2 * x;
    
    printf( "Enter integer search key: ");
    scanf("%d", &searchKey);
    element = linearSearch( a, searchKey, SIZE );
    
    if( element != -1 )
        printf( "Found value in element %d\n", element );
    else
        printf( "Value not found\n" ); 
    
    return 0;
}


int linearSearch( const int array[], int key, int size )
{
    if(size <= 0)
        return -1;
        
    if(array[size-1]==key)
        return size-1;
    else
        return linearSearch(array, key, size-1);
}
 
