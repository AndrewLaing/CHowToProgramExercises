/*
 * Filename:    ex03_22.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
    int c = 5;

    printf("c   = %d\n", c);
    printf("c-- = %d\n", c--);
    printf("c   = %d\n\n", c);
    
    c = 5;

    printf("  c = %d\n", c);
    printf("--c = %d\n", --c);
    printf("  c = %d\n", c);
    
    return 0;
}

