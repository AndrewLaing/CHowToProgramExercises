/*
 * Filename:    ex04_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: Write a program that calculates and prints the
 *              average of several integers. Assume the last value
 *              read with scanf is the sentinel 9999. A typical
 *              input sequence might be
 *                  10 8 11 7 9 9999
 *              indicating that the average of all the values 
 *              preceding 9999 is to be calculated. 
 */

#include <stdio.h>


int main()
{
    int count = 0, num;
    int sum = 0;
    float average = 0;
    
    printf("Enter each number on a seperate line (enter 9999 to exit): ");
    scanf("%d", &num);
    
    while(num != 9999) {
        sum += num;
        count++;
        scanf("%d", &num);
    }
    
    if(count)
        average = (float) sum / count;
    
    printf("\nThe average of the entered numbers is %f\n", average);
    
    return 0;
}

