/*
 * Filename:    stringToIntBaseN.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        29/06/2017.
 * TODO:        Add a way of allowing valid lower-case characters
 */

#include <stdio.h>
#include <string.h>   /* Used for strlen */
#include <ctype.h>

int stringToInt(char *, int );

/* 
 * Derived from User-msg555 Site-Dream in Code
 *              http://www.dreamincode.net/forums/topic/24809-base-conversion/
 * Note: This assumes letters are upper-case
 */
int stringToInt(char *str, int base)
{
    int result = 0;
    
    /* Used for string validation */
    char maxNum = '9';
    char minChar = '0', maxChar = '9';
    
    if(base==0)
        base=10; 
    else if(base<=10)
        maxNum = '0' + base - 1;
    else 
    {
        minChar = 'A';
        maxChar = 'A' + (base-11);
    }

    //Process characters in order from most significant to least significant
    while(*str)
    {
        /* Validate string!*/
        if( !((*str>='0' && *str<=maxNum ) || (*str>=minChar && *str<=maxChar)) )
        {
            printf("Invalid String!\n");
            break;
        }

        // shift the number left a place
        result *= base;
        
        // add the current digit using ASCII math
        if('A' <= *str && *str <= maxChar)
            result += *str - 'A' + 10;
        else
            result += *str - '0';

        str++;
    }
    return result;
}


int main()
{       
    char *test = "FFFF";
    int base = 16;
    printf( "The base %d conversion is %d\n", base, stringToInt(test, base) );
    printf( "The base %d conversion is %d\n", 2, stringToInt("1111111111111111", 2) );
    return 0;
}


