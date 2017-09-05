/*
 * Filename:    ex05_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 * Description: Calculate hypotenuse length
 */

#include <stdio.h>
#include <math.h>


double calcHypotenuse(double side1, double side2);


int main()
{
    float side1, side2, hypotenuse;
    
    printf("Enter length of side 1: ");
    scanf("%f", &side1);
    
    printf("Enter length of side 2: ");
    scanf("%f", &side2);
    
    hypotenuse = calcHypotenuse(side1, side2);
    printf("The length of the hypotenuse is %.2f\n", hypotenuse); 
    
    return 0;
}


double calcHypotenuse(double side1, double side2)
{
    double squareHypotenuse = (side1 * side1) + (side2 * side2);

    return sqrt(squareHypotenuse); 
}

