/*
 * Filename:	ex04_34.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/04/2017
 */

#include <stdio.h>

void printDecimalAsBinary( int );


int main()
{   
    int i;
    for(i=0; i<=256; i++)
    {
    	printf("%-9d", i);
    	printDecimalAsBinary(i);
    	printf("%9o%9X\n", i, i);	
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

