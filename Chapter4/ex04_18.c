/*
 * Filename:    ex04_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/04/2017
 * Description: Histogram.
 */

#include <stdio.h>


int main()
{
    int a, b, c, d, e;
    int count;
    
    printf("Enter five numbers separated by spaces: ");
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);

    for(count = 0; count < a; count++)
        printf("*");
    
    printf("\n");
    
    for(count = 0; count < b; count++)
        printf("*");
    
    printf("\n");

    for(count = 0; count < c; count++)
        printf("*");
    
    printf("\n");    
    
    
    for(count = 0; count < d; count++)
        printf("*");
    
    printf("\n");    
    
    for(count = 0; count < e; count++)
        printf("*");
    
    printf("\n");

    return 0;
}

