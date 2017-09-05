/*
 * Filename:	ex05_22.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 */

#include <stdio.h>

void printDigits( int );
int integerPartOfQuotient( int, int );
int integerRemainder( int, int );


int main()
{
    int a;
    
    printf("Enter digits: ");
	scanf("%d", &a);
	
	if(a < 1 || a > 32767){
		printf("Error - Number must be in the range 1 to 32767\n");
		return -1;
	}
   
    printDigits(a);

	return 0;
}

/* */
void printDigits(int num) 
{
	int res = 0;
	if(num>=10000) {
		res = integerPartOfQuotient(num, 10000);
		printf("%d ", res);
		num -= (res*10000); 
	}
	if(num>=1000) {
		res = integerPartOfQuotient(num, 1000);
		printf("%d ", res);
		num -= (res*1000); 
	}
	if(num>=100) {
		res = integerPartOfQuotient(num, 100);
		printf("%d ", res);
		num -= (res*100); 
	}
	if(num>=10) {
		res = integerPartOfQuotient(num, 10);
		printf("%d ", res);
		num -= (res*10); 
	}
	printf("%d ", integerRemainder(num, 10));
}


/* A quotient is a result obtained by dividing one quantity by another.*/
int integerPartOfQuotient( int a, int b )
{
	return a/b;
}


int integerRemainder( int a, int b )
{
	return a%b;
}

