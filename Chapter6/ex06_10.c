/*
 * Filename:	ex06_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/05/2017
 */

#include <stdio.h>

#define STAFF 20

void calculateWages( int[], int[], int );
void calculateRange( int[], int );

int main()
{
	// Array of weekly sales figures
	int sales[STAFF] = { 2000, 2400, 1500, 10600, 1552, 2120,
	                     1875, 7500, 4690,  9000, 2130, 4000,
				         5800,  500, 1250,  3000 };
				   
	// Array for calculated wages
	int wages[STAFF] = { 0 };
	
	calculateWages( sales, wages, STAFF );
	calculateRange( wages, STAFF );
	
    return 0;
}


void calculateWages( int sales[], int wages[], int employees)
{
	int i, pay;
	
    for( i=0; i<=employees-1; i++ )
	{
	    pay = 200;
		pay += sales[i] * 0.09;
		wages[i] = pay;
	}	
}


void calculateRange( int wages[], int employees)
{
	int range[10] = { 0 };
	int i;
	
    for( i=0; i<=employees-1; i++ )
	{
        if(wages[i] >= 1000)
            ++range[9];
        else if(wages[i] >= 900)
            ++range[8];
        else if(wages[i] >= 800)
            ++range[7];
        else if(wages[i] >= 700)
            ++range[6];
        else if(wages[i] >= 600)
            ++range[5];
        else if(wages[i] >= 500)
            ++range[4];
        else if(wages[i] >= 400)
            ++range[3];
        else if(wages[i] >= 300)
            ++range[2];
        else if(wages[i] >= 200)
            ++range[1];
	}
	
	int sum=200;
	
	for(i=1; i<=9; i++)
	{
		if(i<9)
    		printf("%d. $%d-$%d\t\t- %d\n",
			       i, sum, sum+99, range[i]);
		else
    		printf("%d. $%d and over\t- %d\n",
			       i, sum, range[i]);
		sum+=100;
	}
}

