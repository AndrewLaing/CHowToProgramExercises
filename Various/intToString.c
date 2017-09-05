/*
 * Filename:    intToString.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Convert a double to a string
 *              Accurate to 6 decimal places
 */


#include <stdio.h>
#include <stdlib.h>

void intToString(char [], int );

int main()
{
    int num = 341234; 
    char output[__SIZEOF_INT__];

    intToString(output, num);
    printf("int is = %s", output);

    return 0;

}

void intToString(char s[], int num)
{
    sprintf(s, "%d", num);
}

