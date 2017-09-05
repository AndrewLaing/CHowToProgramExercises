/*
 * Filename:    ex04_29.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/04/2017
 */

#include <stdio.h>


int main()
{
    int a=0, b=1, g=5, i=4, j=7, x=9, y=6, Y=0;
    
    if( (  !(x<5) && !(y>=7)  )  == !( (x<5) || (y>=7) ) )
        printf("First expression passes\n");
    
    if( ( !(a==b) || !(g!=5) ) == !( (a==b) && (g!=5) ) )
        printf("Second expression passes\n");
    
    if( !( (x<=8) && (Y>4)) == ( !(x<=8) || !(Y>4)) )
        printf("Third expression passes\n");

    if( !( (i>4) || (j<=6)) == ( !(i>4) && !(j<=6)) )
        printf("Fourth expression passes\n");
    
    return 0;
}

