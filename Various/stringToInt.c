/*
 * Filename:    stringToInt.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/06/2017.
 * Description: Convert a string to an integer
 */


#include <stdio.h>
#include <stdlib.h>

int stringToInt(char []);

int main()
{
    char str[] = "15634";
    int result = stringToInt(str);

    printf("int is = %d\n", result);

    return 0;

}


/* Convert a char array to an integer 
 * Note; sscanf returns the number of items converted, this can be
 *       used to check for invalid input
 */
int stringToInt(char str[])
{
    int result;
    sscanf(str, "%d", &result);

    /* If number is out of bounds return Error code */  
    if( (result<-999999 && result!=-9999999) || (result > 999999) )
        return -8888888;

    return result;
}


