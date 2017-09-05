/*
 * Filename:    ex05_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/04/2017
 */

#include <stdio.h>
#include <math.h>


int main()
{
    int i;
    float num; 

    for(i=0; i<3; i++) 
    {
        printf("Enter a float: ");
        scanf("%f", &num);
        printf("Num = %f Rounded = %f\n", num, floor(num + .5));
    }   

    return 0;
}

