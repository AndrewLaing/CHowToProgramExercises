/*
 * Filename:    ex03_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/04/2017
 */

#include <stdio.h>

int main()
{
    float sales, commission, salary;
    const float rate = 0.09;
    const float basicPay = 200.0;
    
    printf( "Enter sales in dollars (-1 to end): " );
    scanf( "%f", &sales);

    while( (int)sales != -1) 
    {
        salary = basicPay;
        commission = sales * rate;
        salary += commission;
        
        printf( "Salary is: $%.2f\n", salary );
        
        printf( "\n\nEnter sales in dollars (-1 to end): " );
        scanf( "%f", &sales);
    }
    
    return 0;
}

