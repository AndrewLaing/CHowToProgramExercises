/*
 * Filename:    ex13_05.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/10/2017
 * Description: Macro
 */
 
#include <stdio.h>
#define SUM(x,y) printf("The sum of x and y is %d\n",x+y);


int main()
{
    SUM(5,8);
    return 0;
}


