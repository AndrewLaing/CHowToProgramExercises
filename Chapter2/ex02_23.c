/*
 * Filename:    ex02_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program that reads in five integers and then
 *              determines and prints the largest and smallest integers.
 *              in the group. Use only the programming techniques you
 *              have learned in this chapter.
 */

#include <stdio.h>

int smallest( int, int, int, int, int );
int largest( int, int, int, int, int );

int main()
{
    int num1, num2, num3, num4, num5;
    
    /* Get five numbers from the user */
    printf( "Input five different integers: " );
    scanf("%d%d%d%d%d", &num1, &num2, &num3, &num4, &num5);
    
    printf( "Smallest is %d\n", smallest(num1, num2, num3, num4, num5) );
    printf( "Largest is %d\n", largest(num1, num2, num3, num4, num5) );

    return 0;
}


/* The function smallest returns the smallest
 * of the five numbers passed to it 
 */
int smallest(int num1, int num2, int num3, int num4, int num5)
{
    int smallest = num1;
    
    if(num2 < smallest)
        smallest = num2;
    
    if(num3 < smallest)
        smallest = num3;
        
    if(num4 < smallest)
        smallest = num4;
        
    if(num5 < smallest)
        smallest = num5;
    
    return smallest;
}

/* The function largest returns the largest
 * of the five numbers passed to it 
 */
int largest(int num1, int num2, int num3, int num4, int num5)
{
    int largest = num1;
    
    if(num2 > largest)
        largest = num2;
    
    if(num3 > largest)
        largest = num3;
        
    if(num4 > largest)
        largest = num4;
        
    if(num5 > largest)
        largest = num5;
    
    return largest;
}


