/*
 * Filename:    ex09_08.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/07/2017.
 */

#include <stdio.h>


int main()
{   
    int i, x, y;
    
    for(i=0; i<4; i++) 
    {
        printf("Enter the two numbers: ");
        scanf("%i%d", &x, &y);
        printf("%d %d\n", x, y);
    }

    return 0;
}




