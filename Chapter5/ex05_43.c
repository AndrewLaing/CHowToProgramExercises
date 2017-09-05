/*
 * Filename:    ex05_43.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/05/2017
 */

#include <stdio.h>


int main()
{
    static int count=1;
    
    printf("Count = %d\n", count++);
    while(count < 6) {
        main();
    }

    return 0;
}

