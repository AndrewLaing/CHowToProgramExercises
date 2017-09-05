/*
 * Filename:    ex03_40.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>


int main()
{
    int i = 1;
    int addSpace = 1;
    
    while(i<=64)
    {
        printf("* ");
    
        if(i%8==0) {
            printf("\n");
            addSpace++;
    
            if(addSpace%2==0)
                printf(" ");
        }
        i++;   
    }
    
    return 0;
}
