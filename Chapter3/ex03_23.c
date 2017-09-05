/*
 * Filename:	ex03_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	int i;
	
	for(i=1; i<=10; i++)
	{
		if(i<10)
	    	printf("%d   ", i);
	    else
	        printf("%d", i);
	}
    
	return 0;
}
