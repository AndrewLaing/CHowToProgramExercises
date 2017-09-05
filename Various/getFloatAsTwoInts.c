/*
 * Filename:	getFloatAsTwoInts.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/06/2017.
 * Description: Input a float and store it as two integers, one for
 *				the left hand side of the decimal point, and one for
 *              the right hjand side.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXFLOATLEN 14
#define MAXINTVAL 999999   /* Thus maxFloat = 999999.999999*/


int getLine( char [], int );
int getFloatAsTwoInts(int [2]);


int main()
{
	int num1[2] = {0};
	
	printf("Enter float string (MAX 13 CHARS) > ");
    getFloatAsTwoInts(num1);
    
    printf("lhs = %06d\n", num1[0]);
    printf("rhs = %06d\n", num1[1]);
		 
 	return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
	int c, i=0;
	
	while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
	    s[i++]=c;

	if(c=='\n')
	    s[i++]=c;
	s[i] = '\0';
	
	fflush(stdin); /* Clear any overflow*/
	
	return i;	
}


/* Returns a 1 if valid, -1 if invalid */
int getFloatAsTwoInts(int floatSides[2])
{
	char str[MAXFLOATLEN], rhStr[MAXFLOATLEN];
	int lhs=0, rhs=0;
	
	/* Input a float string */
    getLine(str, MAXFLOATLEN);
    	
	/* Get number on lhs of fp */
   	sscanf(str, "%d", &lhs);	
    floatSides[0] = lhs; 	

    /* find index of floating point */
    int i=0, fpIndex = -1;
    
    do {
    	if(str[i]=='.')
    		fpIndex = i;
		i++;
	} while(i<MAXFLOATLEN && fpIndex==-1);
    
    /* Get number on rhs of fp */
    if(fpIndex >= 0) 
	{
    	int k;

    	for(i=0, k=fpIndex+1; 
		    k<MAXFLOATLEN && str[k]!='\0' && str[k]!='\n'; i++, k++)
    	    rhStr[i] = str[k];
    	rhStr[i]='\0';
    	
        sscanf(rhStr, "%d", &rhs);
        
        /* Remove excess numbers */
        while(rhs>MAXINTVAL)
            rhs/=10;
        
        floatSides[1] = rhs; 
	}

    if(lhs > MAXINTVAL) {
    	printf("\n*** Fatal Error! Floating-point Accumulator overflow ***\n");
    	return -1;
	}
	else
    	return 1;
}

