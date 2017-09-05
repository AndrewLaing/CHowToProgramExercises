/*
 * Filename:	ex03_35.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int isPalindrome( int );


int main()
{
	int num;
	
	/* Get a number from the user */
	printf( "Input a five-digit number: " );
	scanf("%d", &num);
	
	if(isPalindrome(num))
	    printf("%d is a palindrome.", num);
	else
	    printf("%d is NOT a palindrome.", num);
	return 0;
}


/* isPalindrome copies a number, produces a reversed version
 * of the number and checks if the reversed version is the
 * same as the original. */
int isPalindrome(int num) {
	int copy = num;
	int reverse = 0;
	
	reverse += copy/10000;
	copy = copy - ((copy / 10000) * 10000);
	
	reverse += ( (copy/1000) * 10 );
	copy = copy - ((copy / 1000) * 1000);
	
	reverse += ( (copy/100) * 100 );
	copy = copy - ((copy / 100) * 100);
	
	reverse += ( (copy/10) * 1000 );
	copy = copy - ((copy / 10) * 10);
	
	reverse += ( (copy%10) * 10000 );
	
	return num==reverse;
}

