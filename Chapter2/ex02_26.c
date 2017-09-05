/*
 * Filename:    ex02_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program that reads in two integers and determines
 *              and prints if the first is a multiple of the second.
 */

#include <stdio.h>


/* The method isMultiple returns 0 if num1 is a multiple
 * of num2, otherwise it returns the remainder
 */
int isMultiple(int num1, int num2)
{
    return num1 % num2 == 0;
}


int main()
{
    int num1, num2;
    
    /* Get a number from the user */
    printf( "Input two numbers: " );
    scanf("%d%d", &num1, &num2);
    
    /* 0 is false */
    if(isMultiple(num1, num2))
        printf( "%d is a multiple of %d.\n", num1, num2 );
    else
        printf( "%d is NOT a multiple of %d.\n", num1, num2 );

    return 0;
}

