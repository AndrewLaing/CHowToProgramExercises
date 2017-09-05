/*
 * Filename:    ex04_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/04/2017
 * Description: Modify the program in fig04_06 so that it uses only integers
 *              to calculate the compound interest.
 */

#include <stdio.h>
#include <math.h>

int main()
{
    int year;
    long amount, principal = 100000, rate = 5;
    long modifier;
    long r = rate+100;
    int count;
    
    printf( "%4s%21s\n", "Year", "Amount on deposit" );
    
    for(year = 1; year <= 10; year++ )
    {
        modifier = r;
        for(count=1; count<year; count++) {
            modifier*=r;
            modifier/=100;
        }
            
            
        //printf("modifier = %d\n", modifier );
        /* amount = principal * ((1 + rate)**years)    */
        amount = (principal * modifier)/100;
        printf( "%4d%21d\n", year, amount );    
    }

    return 0;
}
