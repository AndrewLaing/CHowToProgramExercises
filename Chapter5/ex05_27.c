/*
 * Filename:	ex05_27.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/05/2017
 */

#include <stdio.h>
#include <math.h>

int isPrime( int );


int main()
{
    int n;
    
    for(n=1; n<=10000; n++)
	    isPrime(n);  	

	return 0;
}


int isPrime( int n )
{
	int high = (int)sqrt(n);
	int i;
	
	if(n<=2) {
		printf("%d is a prime number\n", n);
		return 1;
	}
	
	if(n%2==0)
	    return 0;
	
	for(i=3; i<=high; i+=2)
	{
		if(n%i==0)
		   return 0;
	}
	
	printf("%d is a prime number\n", n);
	return 1;
}

