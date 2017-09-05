/*
 * Filename:	ex03_38.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>


int main()
{
	int i = 1;
	
	while(i<=100) 
	{
		printf("*");
		
		if(i++%10 == 0)
		    printf("\n");
	}

	return 0;
}
