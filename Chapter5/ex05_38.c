/*
 * Filename:    ex05_38.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/05/2017
 */

#include <stdio.h>


int fibonacciNR( int );
double fibonacciDubs( double );

int main()
{
    int i;
    
    for(i=1; i<49; i++) {
        printf("fibonacciNR(%d) = %d\n", i, fibonacciNR(i));
    }
        
    for(i=1; i<1479; i++) {
        printf("fibonacciDubs(%d) = %.0f\n", i, fibonacciDubs(i));
    }  

    return 0;
}


/* Non-recursive fibonacci function */
int fibonacciNR( int num )
{
    int a=0, b=1;
    int fib=1;
    
    int i;
    
    if(num==1)
        return 0;
        
    for(i=2; i<num; i++) {
        fib = a+b;
        a = b;
        b = fib; 
    }
    
    return fib;
}

/* Non-recursive fibonacci function */
double fibonacciDubs( double num )
{
    double a=0, b=1;
    double fib=1;
    
    int i;
    
    if(num==1)
        return 0;
        
    for(i=2; i<num; i++) {
        fib = a+b;
        a = b;
        b = fib; 
    }
    
    return fib;
}

