/*
 * Filename:	ex05_28.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/05/2017
 * Description:	Reverse an integer
 */

#include <stdio.h>


int reverseNumber( int );


int main()
{
    int n;
    
    printf("Enter number: ");
	scanf("%d", &n);
	
	if(n < 0 ) {
		printf("Error - Number must be greater than zero\n");
		return -1;
	}
	
	printf("Number reversed = %d\n", reverseNumber( n ));

	return 0;
}


/* Needs a better algorithm */
int reverseNumber( int num )
{
	int reversed = 0;
	
	while(num > 1) {
		reversed += num%10;
		num/=10;
		if(num>=1)
		    reversed*=10;
	}
	
	if(num==1)
	    reversed += 1;

	return reversed;
}

