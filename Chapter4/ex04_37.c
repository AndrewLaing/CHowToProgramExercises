/*
 * Filename:    ex04_37.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/04/2017
 */

#include <stdio.h>


int main()
{
    int x;
    int leftLoopAt=0;
    
    for(x = 1; x <= 10; x++)
    {
        if(x == 5) {
            leftLoopAt = x;
            x=11;
        }
        else
            printf("%d ", x );
    }
     
    printf("\nBroke out of loop at x == %d\n", leftLoopAt );

    return 0;
}

