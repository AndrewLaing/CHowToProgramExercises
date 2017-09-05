/*
 * Filename:    ex03_41.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 * Notes:       The program exits as soon as it goes above
 *              the maximum integer value.
 */

#include <stdio.h>


int main()
{
    int i = 2;
    
    while(i>0) {
        printf("%d ", i);
        i*=2;
    }

    return 0;
}
