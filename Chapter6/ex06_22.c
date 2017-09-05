/*
 * Filename:	ex06_22.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/05/2017
 */

#include <stdio.h>
#define DAYSINMONTH 2
#define SP 5     /* Sales people + 1*/
#define PROD 6   /* Products + 1*/


void printTable( int [][PROD] );


void printTable(int sales[][PROD])
{
	printf("\n=== Sales Information table for the last %d days ===\n\n", DAYSINMONTH);
	printf("SP No\tProd 1\tProd 2\tProd 3\tProd 4\tProd 5\t TOTAL\n");
	
	int salesperson, product;
	int prodTotals[PROD] = {0};
	int salesPersonTotal = 0;
	int allSales = 0;
	
	for(salesperson=1; salesperson<SP; salesperson++)
	{
		salesPersonTotal = 0;
		
		for(product=1; product<PROD; product++) 
		{
			prodTotals[product] += sales[salesperson][product];
			salesPersonTotal += sales[salesperson][product];
		}
		
		allSales += salesPersonTotal;
		    
		printf("%5d", salesperson);
		
		for(product=1; product<PROD; product++) 
		{
			printf("\t%6d", sales[salesperson][product]);
		}
		printf("\t%6d\n", salesPersonTotal);
		                                              
	}
	
	printf("\nTOTAL");
	for(product=1; product<PROD; product++) 
	{
		printf("\t%6d", prodTotals[product]);
	}
	printf("\t%6d\n", allSales);
}

int main()
{	
    int day, salesperson, product;
    int sales;
    
    int totalSales[SP][PROD] = { {0} };
    
    for(day=1; day<=DAYSINMONTH; day++) 
	{
    	for(salesperson=1; salesperson<SP; salesperson++) {
    		printf("\nEnter product details of day %d for salesperson %d\n", day, salesperson );
    		for(product=1; product<PROD; product++) {
    			printf("Sales of product %d: ", product);
    			scanf("%d", &sales);
    			totalSales[salesperson][product] += sales;
			}
		}
	}
	
    printTable(totalSales);	
	
    return 0;
}

