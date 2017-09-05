/*
 * Filename:    ex05_31.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/05/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int flip( void );


int main()
{
    srand( (time(NULL)) );
    int total = 0;
    int i;
    
    for(i=0; i<100; i++)
        total += flip();
    
    printf("\n\nThe total number of heads was = %d\n", total);
    printf("The total number of tails was = %d\n", 100-total);  

    return 0;
}



int flip( )
{
    int res = rand()%2;

    if(res)
        printf("Heads ");
    else
        printf("Tails ");
    
    return res;
}

