/*
 * Filename:	ex05_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 * Description:	Calculate Integer exponent
 */

#include <stdio.h>


int multiple(int i, int j);


int main()
{
	int i;
    int num1, num2;
    
    for(i=0; i<3; i++)
    {
	    printf("Enter the first number: ");
	    scanf("%d", &num1);
	    
	    printf("Enter the second number: ");
	    scanf("%d", &num2);
	    
	    if (multiple(num1, num2))
		    printf("%d is a multiple of %d\n\n", num2, num1); 
	    else
		    printf("%d is NOT a multiple of %d\n\n", num2, num1);     	
	}

	return 0;
}


int multiple(int i, int j)
{
	return (j%i==0); 
}

