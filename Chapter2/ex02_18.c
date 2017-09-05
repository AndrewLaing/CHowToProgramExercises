/*
 * Filename:    ex02_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/04/2017
 * Description: Write a program that asks the user to enter two integers,
 *              obtains the numbers from the user, then prints the larger 
 *              number followed by the words "is larger". If the numbers
 *              are equal, print the message "These numbers are equal."
 *              Use only the single-selection form of the if statement
 *              you learned in this chapter. 
 */

#include <stdio.h>


int main()
{
    int num1, num2;
    
    /* Get two numbers from the user */
    printf( "Enter two integers: " );
    scanf("%d%d", &num1, &num2);
    
    if(num1 > num2)
        printf("%d is larger.", num1);

    if(num1 < num2)
        printf("%d is larger.", num2);
        
    if(num1 == num2)
        printf("These numbers are equal.");
        
    return 0;
}
