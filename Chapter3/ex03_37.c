/*
 * Filename:    ex03_37.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>


int main()
{
    int i = 1;
    
    while(i<=3000000) {
        if(i%1000000 == 0)
            printf("%d\n", i);
        i++;
    }

    return 0;
}
