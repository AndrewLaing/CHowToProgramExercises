/*
 * Filename:    ex09_07.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/07/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNumber( int max );

int main()
{   
    srand( time(NULL) );
    int i, sum=0, x[10];
    
    for(i=0; i<10; i++) 
    {
        x[i] = getRandomNumber(1000) ;
    }
    
    
    printf("%s\t%s\n", "Value", "Total characters");
    
    for(i=0; i<10; i++) 
    {
        sum += printf("%d", x[i]);
        printf("\t%d\n", sum);
        x[i] = getRandomNumber(1000) ;
    }
    return 0;
}


/* Returns a random number in the range 0 to max-1*/
int getRandomNumber( int max )
{
    return (rand()%max)+1;
}


