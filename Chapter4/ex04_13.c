/*
 * Filename:    ex04_13.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: Write a program that calculates and prints the sum
 *              of the odd integers from 1 to 15.
 */

#include <stdio.h>


int main()
{
    int sum = 0, number;
    
    for(number = 1; number <= 15; number += 2)
        sum += number;
    
    printf("Sum is %d\n", sum );

    return 0;
}

