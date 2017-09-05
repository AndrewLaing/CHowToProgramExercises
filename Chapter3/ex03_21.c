/*
 * Filename:	ex03_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	/* Initialisation phase */
	int hoursWorked;
	float hourlyRate, salary;
	
	printf( "Enter # of hours worked (-1 to end): " );
	scanf( "%d", &hoursWorked );
	
	/* Processing phase */
	while( hoursWorked != -1 ) 
	{
		salary = 0;
		printf( "Enter hourly rate of the worker ($00.00): " );
		scanf( "%f", &hourlyRate );

        if(hoursWorked > 40) {
        	salary += (hoursWorked - 40) * (hourlyRate * 1.5);
        	hoursWorked = 40;
		}
		
        salary += hoursWorked *hourlyRate;
        
        printf( "Salary is $%.2f\n", salary );
        
       	printf( "\n\nEnter # of hours worked (-1 to end): " );
	    scanf( "%d", &hoursWorked );
	}

    /* Termination phase */
	return 0;
}

