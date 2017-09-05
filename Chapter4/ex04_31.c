/*
 * Filename:    ex04_31.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/04/2017
 */

#include <stdio.h>

#define printStar printf( "*" );
#define printSpace printf( " " ); 
#define newLine printf( "\n" );

int main()
{
    int i, j, k;
    
    int max=2;
    
    for(i=0; i<=max; i++) 
    {
        for(j=0; j<(max-i); j++)
            printSpace;
        for(k=0; k<(1+(i*2)); k++)
            printStar;
        newLine;
    }

    for(i=max-1; i>=0; i--) 
    {
        for(j=0; j<(max-i); j++)
            printSpace;
        for(k=0; k<(1+(i*2)); k++)
            printStar;
        newLine;
    }
    
    return 0;
}

