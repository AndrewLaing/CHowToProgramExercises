/*
 * Filename:	ex04_35.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/04/2017
 */

#include <stdio.h>

int getFirstDayOfYear( int );
int printMonth( int, int, char* );
void printYear( int );


int main()
{   
    int year;
    printf("Enter a year from 1994 upwards: ");
    scanf("%d", &year);

    printYear(year);
	
	return 0;
}


int getFirstDayOfYear(int year) 
{
	int currentDay=7;

	while(year>1994) 
	{
		if(year==1997 || ((year-1-1996)%4==0) ) {
			currentDay+=366;
		}
		else
		    currentDay+=365;
		
		year--;
	}
	
    currentDay = currentDay % 7;
    if(currentDay == 0)
        currentDay = 7;
    
    return currentDay;
}



int printMonth(int startDay, int daysInMonth, char* month) 
{
    int i;
    int currentDay=startDay;
    
    printf("---------------------------------------------------\n");
	printf("\t\t%s\n", month);   
    printf("---------------------------------------------------\n");
    
    printf("SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n\n");
    
    for(i=1;i<startDay;i++) {
    	printf("\t");
	}
    
    for(i=1; i<=daysInMonth; i++)
    {
    	printf("%d\t",i);
    	if(currentDay%7==0)
    	    printf("\n");
    	currentDay++;
	}
	
    printf("\n\n");	
    
    currentDay = currentDay % 7;
    if(currentDay == 0)
        currentDay = 7;
    
    return currentDay;
}


void printYear(int year)
{
    int currentDay = getFirstDayOfYear(year); 

    printf("---------------------------------------------------\n");
	printf("\tCALENDER FOR THE YEAR %d\n", year);   
    printf("---------------------------------------------------\n");

	currentDay = printMonth(currentDay, 31, "JANUARY");
	
	if(year==1996 || ((year-1996)%4==0) ) {
		printf("%d is a leap year\n", year);
        currentDay = printMonth(currentDay, 29, "FEBRUARY");
	}
	else
    	currentDay = printMonth(currentDay, 28, "FEBRUARY");
    	
	currentDay = printMonth(currentDay, 31, "MARCH");
	currentDay = printMonth(currentDay, 30, "APRIL");
	currentDay = printMonth(currentDay, 31, "MAY");
	currentDay = printMonth(currentDay, 30, "JUNE");
	currentDay = printMonth(currentDay, 31, "JULY");
	currentDay = printMonth(currentDay, 31, "AUGUST");
	currentDay = printMonth(currentDay, 30, "SEPTEMBER");
	currentDay = printMonth(currentDay, 31, "OCTOBER");
	currentDay = printMonth(currentDay, 30, "NOVEMBER");
	currentDay = printMonth(currentDay, 31, "DECEMBER");
}

