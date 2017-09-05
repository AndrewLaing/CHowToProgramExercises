/*
 * Filename:    ex02_31.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program which calculates and prints the squares
 *              and cubes of the numbers from 0 to 10 and uses tabs to
 *              display them in a table of values.
 */

#include <stdio.h>


int main()
{
    int i;
    
    /* Print column names */
    printf("number\tsquare\tcube\n");

    for(i=0; i<=10; i++)
        printf("%d\t%d\t%d\n", i, i*i, i*i*i);
    
    return 0;
}
