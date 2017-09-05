/*
 * Filename:    ex03_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
    int a;
    
    printf("A\tA+2\tA+4\tA+6\n\n");
    
    for(a=3; a<=15; a+=3)
        printf("%d\t%d\t%d\t%d\n", a, (a+2), (a+4), (a+6));
    
    return 0;
}
