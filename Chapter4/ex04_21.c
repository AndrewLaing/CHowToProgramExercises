/*
 * Filename:	ex04_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/04/2017
 * Description: Rewrite the program of fig04_02 so that the initialisation
 *				of the variable counter is done in the declaration instead
 *				of the for structure.
 */

#include <stdio.h>


int main()
{
    int counter = 1;
    
    for( ; counter <= 10; counter++)
    	printf("%d\n", counter );

	return 0;
}

