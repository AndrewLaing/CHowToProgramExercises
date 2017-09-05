/*
 * Filename:	ex03_45.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/04/2017
 */

#include <stdio.h>

float getValidLength( int );
int isValidRATriangle( float, float, float );


int main()
{
	float a, b, c;
	
	a = getValidLength(1); 
	b = getValidLength(2);
	c = getValidLength(3);
	
	/* display the results */
	if( isValidRATriangle(a, b, c) )
	    printf("The values inputted could represent the sides\nof a right-angled triangle.\n");
	else
	    printf("The values inputted could NOT represent\nthe sides of a right-angled triangle.\n");	
	return 0;
}


float getValidLength(int side)
{
	float sideLength = 0;
	while(sideLength<=0) {
		printf("Enter the length of side #%d: ", side);
		scanf("%f", &sideLength);
		
		if(sideLength <= 0)
		    printf("Side length must be greater than zero.\n");
	}

	return sideLength;
}


int isValidRATriangle(float a, float b, float c)
{
	if(a>b)
	{
		if(a>c)
		    return ( (c*c)+(b*b) == (a*a) );
		else
		    return ( (a*a)+(b*b) == (c*c) );
	}
	else if(b>c)
	    return ( (a*a)+(c*c) == (b*b) );
	else
	    return ( (a*a)+(b*b) == (c*c) );
}


