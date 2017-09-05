/*
 * Filename:    ex05_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/05/2017
 */

#include <stdio.h>

void printFactors( int );
int isPerfect( int );


int main()
{
    int n;
    
    for(n=1; n<=100000; n++)
    {
        if(isPerfect(n))
            printFactors( n );  
    }

    return 0;
}


void printFactors( int n )
{
    int i=1;
    int sum = 0;
    
    while(sum < n) {
        sum+=i;
        printf("%d ", i);
        i++;
    }   
    printf("= %d\n", n);
}


int isPerfect( int n )
{
    int perfect = 0;
    int i=1;
    int sum = 0;
    
    while(sum <= n) {
        sum+=i;
        
        if(sum==n)
            perfect = 1;
        
        i++;
    }
    
    return perfect;
}

