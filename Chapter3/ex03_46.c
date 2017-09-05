/*
 * Filename:	ex03_46.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>

int operation1( int );
int operation2( int, int, int, int );
int operation3( int );
int decrypt( int );
int encrypt( int );


int main()
{
    int number;

	printf("Enter the number to encrypt: ");
	scanf("%d", &number);
	
	int encrypted = encrypt(number); 	
	printf("The encrypted number is %d\n", encrypted);
	
	int decrypted = decrypt(encrypted);
	printf("The decrypted number is %d\n", decrypted);

	return 0;
}


/* Used by encrypt. */
int operation1(int number)
{
    return (number+7)%10;
}


/* Used by both encrypt and decrypt. */
int operation2(int one, int two, int three, int four)
{
	int result = two;
	result += (one*10);
	result += (four*100);
	result += (three*1000);
	
	return result;
}


/* Used by decrypt. */
int operation3(int number)
{
    return (number+3)%10;
}


/* Decrypt number and return the result. */
int decrypt(int number)
{
    int one, two, three, four;
    int result;
    
    four = operation3(number%10);
	number/=10;

	three = operation3(number%10);
	number/=10;
	
    two = operation3(number%10);
	number/=10;
	
    one = operation3(number%10);
    
    result = operation2(one, two, three, four);
    
    return result;
}


/* Encrypt number and return the result. */
int encrypt(int number)
{
    int one, two, three, four;
    int result;
    
    four = operation1(number%10);
	number/=10;

	three = operation1(number%10);
	number/=10;
	
    two = operation1(number%10);
	number/=10;
	
    one = operation1(number%10);
    
    result = operation2(one, two, three, four);
    
    return result;
}

