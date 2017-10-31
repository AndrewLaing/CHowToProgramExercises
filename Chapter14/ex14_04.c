/*
 * Filename:    ex14_04.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/10/2017
 * Description: Command line args sort ascend or descend
 */
 
#include <stdio.h>
#include <stdlib.h>     /* exit */

void bubbleSortAscending( int [], int );
void bubbleSortDecending( int [], int );

int main( int argc, char *argv[])
{
    int testArray[] = {2,6,5,3,7,8,1,4};
    
    if(argc == 1 )
        bubbleSortAscending(testArray, 8);
    else if(argc == 2) 
    {
        if(argv[1][0]=='-') 
        {
            if(argv[1][1] == 'a')
                bubbleSortAscending(testArray, 8);
            else if(argv[1][1] == 'd')
                bubbleSortDescending(testArray, 8);
            else {
                printf("Usage: sortArray [ -d | -a ]\n");
                exit(1);
            }
        }
        else {
            printf("Usage: sortArray [ -d | -a ]\n");
            exit(1);
        }
    }
    else {
        printf("Usage: sortArray [ -d | -a ]\n");
        exit(1);
    }
    
    /* Print out the contents of the sorted array */
    int i;
    for(i=0; i<8; i++)
        printf("%d ", testArray[i]);
    
    putchar( '\n' );
    return 0;
}


void bubbleSortAscending( int a[], int arraySize )
{
    int i, pass, hold;
    int switchMade;

    for(pass=1; pass<=arraySize-1; pass++)
    {
        switchMade = 0;
        for(i=0; i<=arraySize-1-pass; i++)
        {
            if(a[i] > a[i+1])  {
                hold = a[i];
                a[i] = a[i+1];
                a[i+1]=hold;
                switchMade = 1;
            }
        }
        
        if(switchMade == 0) {
            break;
        }    
    }   
}


void bubbleSortDescending( int a[], int arraySize )
{
    int i, pass, hold;
    int switchMade;

    for(pass=1; pass<=arraySize-1; pass++)
    {
        switchMade = 0;
        for(i=0; i<=arraySize-1-pass; i++)
        {
            if(a[i] < a[i+1])  {
                hold = a[i];
                a[i] = a[i+1];
                a[i+1]=hold;
                switchMade = 1;
            }
        }
        
        if(switchMade == 0) {
            break;
        }    
    }   
}
