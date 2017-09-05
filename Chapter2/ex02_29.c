/*
 * Filename:	ex02_29.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Display the integer equivalents of letters.
 */

#include <stdio.h>


int main()
{
    char* letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";
    int i;
    for(i=0; i<53; i++) {
    	printf("%d\t", letters[i]);
    	if((i+1) % 5 == 0)
    	     printf("\n");
	}

	return 0;
}
