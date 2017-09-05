/*
 * Filename:    ex03_42.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>

const float PI = 3.14159;

float diameter( float );
float area( float );
float circumference( float );


int main()
{
    float radius;
    
    /* Get a number from the user */
    printf( "Input the radius: " );
    scanf("%f", &radius);
    
    /* display the results */
    printf("Diameter is %.2f\n", diameter(radius) );
    printf("Area is %.2f\n", area(radius) );
    printf("Circumference is %.2f\n", circumference(radius) );
    return 0;
}


float diameter(float radius)
{
    return radius * 2;
}


float area(float radius)
{
    return PI * (radius * radius);
}


float circumference(float radius)
{
    return 2 * PI * radius;
}

