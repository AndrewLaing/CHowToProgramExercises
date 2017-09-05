/*
 * Filename:	ex04_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/04/2017
 * Description: Mail Order House program.
 */

#include <stdio.h>

float getPrice( int );

int main()
{
    int productNumber, quantitySold;
    float price;
    float totalSales = 0.0;
    
    do {
    	printf( "Enter the product number (or -1 to exit): " );
    	scanf( "%d", &productNumber );
    	
    	if(productNumber != -1)
    		price = getPrice(productNumber);
		else
		    price = -1;	
    	
    	if((int)price != -1) {
        	printf( "Enter number of items sold: " );
    	    scanf( "%d", &quantitySold );
    	    
    	    if(quantitySold > 0)
    	        totalSales += (price * quantitySold);
		}
	} while (productNumber != -1);
    
	printf( "\nThe total retail value of all products sold\n" );
	printf( "last week was $%.2f\n ", totalSales );

	return 0;
}


float getPrice(int productNumber)
{
	float price = 0.0;

	switch(productNumber) 
	{
		case 1:
			price = 2.98;
			break;
		case 2:
			price = 4.50;
			break;
		case 3:
			price = 9.98;
			break;
		case 4:
			price = 4.49;
			break;
		case 5:
			price = 6.87;
			break;
		default:
			printf("Invalid product number!");
			price = -1;
			break;
	}
	
	return price;
}

