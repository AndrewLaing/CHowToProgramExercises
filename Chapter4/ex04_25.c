/*
 * Filename:	ex04_25.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        22/04/2017
 * Description: Print a table of decimal, binary, octal and
 *				hexadecimal equivalents.
 */

#include <stdio.h>

void printDecimalAsBinary( int );


int main()
{   
    int i;
    printf("Decimal\tBinary\tOctal\tHex\n");
    for(i=0; i<20; i++)
    {
    	printf("%d\t", i);
    	printDecimalAsBinary(i);
    	printf("\t%o\t%X\n", i, i);	
	}

	return 0;
}

void printDecimalAsBinary(int dec) 
{
	int pos=1;
	
	while(pos<=dec)
	    pos*=2;
	    
	pos/=2;
	
    while(pos>1) 
	{
		if(dec>=pos) {
			printf("%d",(dec/pos));
			dec-=pos;
		}
		else
		    printf("0");
		
		pos/=2;
	}
	
	printf("%d", dec);
}

