/*
 * Filename:    ex02_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program that reads in the radius of a circle
 *              and prints the circle's diameter, circumference and
 *              area. Use the constant value of 3.14159 for PI. Do
 *              each of the calculations inside the printf statements
 *              and use the conversion specifier %f.
 */

#include <stdio.h>


int main()
{
    const float PI = 3.14159;
    float radius;
    
    /* Get two numbers from the user */
    printf( "Input the radius: " );
    scanf("%f", &radius);

    printf( "Diameter      = %f\n", (2 * radius) ); 
    printf( "Circumference = %f\n", (2 * PI * radius) );
    printf( "Circumference = %f\n", (PI * (radius * radius)) );

    return 0;
}
