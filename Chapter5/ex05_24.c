/*
 * Filename:    ex05_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/05/2017
 */

#include <stdio.h>


int fahrenheitToCelsius( int );
int celsiusToFahrenheit( int );


int main()
{
    int celsius, fahrenheit;
    
    printf("Enter temperature in celsius: ");
    scanf("%d", &celsius);
    printf("Temperature converted to fahrenheit = %d\n", celsiusToFahrenheit(celsius));

    printf("\nEnter temperature in fahrenheit: ");
    scanf("%d", &fahrenheit);
    printf("Temperature converted to fahrenheit = %d\n", fahrenheitToCelsius(fahrenheit));

    return 0;
}


int fahrenheitToCelsius( int fahrenheit )
{
    return (int) ((5.0/9.0)*(fahrenheit-32));
}

int celsiusToFahrenheit( int celsius )
{
    return (int)(celsius * (9.0/5.0) + 32);
}

