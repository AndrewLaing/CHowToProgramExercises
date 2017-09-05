/*
 * Filename:    ex03_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/04/2017
 */

#include <stdio.h>

int main()
{
    float totalGallons = 0, totalMiles = 0;
    float gallons, miles, average;
    
    printf( "Enter the gallons used (-1 to end): " );
    scanf( "%f", &gallons );

    while((int)gallons != -1) 
    {
        printf( "Enter the miles driven: " );
        scanf( "%f", &miles );
        totalGallons += gallons;
        totalMiles += miles;
        
        if(gallons != 0)
            average = (float) miles / gallons;
        else
            average = 0;

        printf( "The miles / gallon for this tank was %f\n\n", average );
        
        printf( "Enter the gallons used (-1 to end): " );
        scanf( "%f", &gallons );
    }

    if(totalGallons != 0)
        average = (float) totalMiles / totalGallons;
    else
        average = 0;

    printf( "\nThe overall miles per gallon was %f\n", average );
    
    return 0;
}

