/*
 * Filename:    doubleToString.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Convert a double to a string
 *              Accurate to 6 decimal places
 */


#include <stdio.h>
#include <stdlib.h>

void doubleToString(char [], double );

int main()
{
    double num = 341234.123456; 
    char output[__SIZEOF_FLOAT__];

    doubleToString(output, num);
    printf("double is = %s", output);

    return 0;

}

void doubleToString(char s[], double num)
{
    sprintf(s, "%f", num);
}

