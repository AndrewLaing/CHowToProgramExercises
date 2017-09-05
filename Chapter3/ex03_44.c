/*
 * Filename:    ex03_44.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>

float getValidLength( int );
float isValidTriangle( float, float, float );


int main()
{
    float a, b, c;
    
    a = getValidLength(1); 
    b = getValidLength(2);
    c = getValidLength(3);
    
    /* display the results */
    if( isValidTriangle(a, b, c) )
        printf("The values inputted could represent the sides of a triangle.\n");
    else
        printf("The values inputted could NOT represent the sides of a triangle.\n");   
    return 0;
}


float getValidLength(int side)
{
    float sideLength = 0;
    while(sideLength<=0) {
        printf("Enter the length of side #%d: ", side);
        scanf("%f", &sideLength);
        
        if(sideLength <= 0)
            printf("Side length must be greater than zero.\n");
    }

    return sideLength;
}


float isValidTriangle(float a, float b, float c)
{
    if((a+b)<c)
        return 0;
    if((a+c)<b)
        return 0;
    if((b+c)<a)
        return 0;
    return 1;
}

