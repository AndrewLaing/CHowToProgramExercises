/*
 * Filename:    ex02_30.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program which inputs one five-digit number,
 *              separates the number into its individual digits, and
 *              prints the digits separated from one another by three
 *              spaces each.
 */

#include <stdio.h>


int main()
{
    int num;
    
    /* Get a number from the user */
    printf( "Input a five-digit number: " );
    scanf("%d", &num);
    
    printf("%d   ", (num/10000));
    num = num - ((num/10000)*10000);
    
    printf("%d   ", (num/1000));
    num = num - ((num/1000)*1000);
    
    printf("%d   ", (num/100));
    num = num - ((num/100)*100);
    
    printf("%d   ", (num/10));
    num = num - ((num/10)*10);  
    
    printf("%d\n", (num%10));
    
    return 0;
}
