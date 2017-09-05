/*
 * Filename:    ex06_38.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/05/2017
 */

#include <stdio.h>

void stringReverse( char[]);


int main()
{
    char str[] = "Test String 3";
    
    stringReverse( str );
    
    return 0;
}


void stringReverse( char str[] )
{
    if(str[0]=='\0')
        return;
    else
        stringReverse(&str[1]); 
        
    printf("%c", str[0]); 
}

