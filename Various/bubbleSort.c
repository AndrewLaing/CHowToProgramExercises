/*
 * Filename:    ex06_11.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/05/2017
 * Description: Bubble Sort Algorithm
 */

#include <stdio.h>
#define SIZE 10

void bubbleSort( int[] );


int main()
{
    int a[ SIZE ] = {2,6,4,8,10,12,89,68,45,37};
    int i;
    
    printf( "Data items in original order:\n" );
    
    for( i=0; i<=SIZE-1; i++)
        printf("%4d", a[i]);

    bubbleSort( a ); 
    
    printf( "\nData items in ascending order:\n" );
    
    for( i=0; i<=SIZE-1; i++)
        printf("%4d", a[i]);
    
    printf("\n");
    
    return 0;
}


void bubbleSort( int a[] )
{
    int i, pass, hold;
    int switchMade;

    for(pass=1; pass<=SIZE-1; pass++)
    {
        switchMade = 0;
        for(i=0; i<=SIZE-1-pass; i++)
        {
            if(a[i] > a[i+1]) 
            {
                hold = a[i];
                a[i] = a[i+1];
                a[i+1]=hold;
                switchMade = 1;
                // printf("\nSwap made!\n");
            }
        }
        
        if(switchMade == 0) {
            // printf("\n\nExiting loop!\n");
            break;
        }
            
    }   
}


