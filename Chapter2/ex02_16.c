/*
 * Filename:    ex02_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/04/2017
 * Description: Write a program that asks the user to enter two numbers
 *              obtains two numbers from the user, and prints the sum,
 *              product, difference, quotient and modulus of the two numbers
 */

#include <stdio.h>

int sum( int, int );
int product( int, int );
int difference( int, int );
int quotient( int, int );
int modulus( int, int );


int main()
{
    int num1, num2;
    
    /* Get two numbers from the user */
    printf( "Enter two integers: " );
    scanf("%d%d", &num1, &num2);
    
    printf( "Sum        = %d\n", sum(num1, num2) );
    printf( "Product    = %d\n",product(num1, num2) );
    printf( "Difference = %d\n", difference(num1, num2) );
    printf( "Quotient   = %d\n", quotient(num1, num2) );
    printf( "Modulus    = %d\n", modulus(num1, num2) );

    return 0;
}


/* The method sum calculates and returns the sum of the
 * two numbers passed to it 
 */
int sum(int num1, int num2)
{
    return num1 + num2;
}

/* The method product calculates and returns the product
 * of the two numbers passed to it 
 */
int product(int num1, int num2)
{
    return num1 * num2;
}

/* The method difference calculates and returns the difference 
 * between the two numbers passed to it 
 */
int difference(int num1, int num2)
{
    return (num1 > num2) ? num1-num2 : num2-num1;
}

/* The method quotient calculates and returns 
 * the quotient of the two numbers passed to it 
 */
int quotient(int num1, int num2)
{
    return (num1+num2)/2;
}

/* The method modulus calculates and returns the modulus
 * of the two numbers passed to it 
 */
int modulus(int num1, int num2)
{
    return num1%num2;
}


