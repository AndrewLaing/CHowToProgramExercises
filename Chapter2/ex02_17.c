/*
 * Filename:    ex02_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/04/2017
 * Description: Write a program that prints the numbers 1 to 4 
 *              on the same line. Write the program using the
 *              following methods;
 *                  a) Using one printf statement with 
 *                      no conversion specifiers. 
 *                  b) Using one printf statement with 
 *                      four conversion specifiers. 
 *                  a) Using four printf statements. 
 */

#include <stdio.h>


int main()
{
    printf( "1 2 3 4\n");
    printf( "%d %d %d %d\n",1, 2, 3, 4 );
    printf( "1 " );
    printf( "2 " );
    printf( "3 " );
    printf( "4\n" );

    return 0;
}
