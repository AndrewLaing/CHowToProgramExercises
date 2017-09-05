/*
 * Filename:	ex05_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 */

#include <stdio.h>


void side( int );


int main()
{
	int i;
    int num;
    
    for(i=0; i<3; i++)
    {
	    printf("Enter a number: ");
	    scanf("%d", &num);
	    
	    side(num);     	
	}

	return 0;
}


void side(int n)
{
	int i, j;
	
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("*");
		}
		printf("\n");
	}
	
	printf("\n");
}

