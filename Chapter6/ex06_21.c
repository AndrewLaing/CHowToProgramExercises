/*
 * Filename:	ex06_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/05/2017
 */

#include <stdio.h>

#define MAXSEATS 10

/* Menu strings */
const char* MENU = 
    "\nPlease type 1 for \"first class\"\n"
    "Please type 2 for \"economy\"\n-> ";
    
const char* MENU1 = 
    "\nSorry first class is full\n"
    "Will you accept a seat in economy?\n"
    "Please type 1 for YES\n"
    "Please type 2 for NO\n-> ";

const char* MENU2 = 
    "\nSorry economy is full\n"
    "Will you accept a seat in first class?\n"
    "Please type 1 for YES\n"
    "Please type 2 for NO\n-> ";

/* PROTOTYPES */
void printPass( int );
int assignFirstClassSeat( int [] );
int assignEconomySeat( int [] );
int acceptAlternative( const char* );


void printPass( int seatNum )
{
	printf("\n---------------------------------------\n");
	if(seatNum < 5)
	    printf("              FIRST CLASS\n");
	else
	    printf("             ECONOMY CLASS\n");
	printf("---------------------------------------\n");
	printf("Flight LH907\tBoarding\tSeat No\n");
	printf("To Boston\t  9:10am\t%4d\n", seatNum+1);
	printf("\nDeparture 9:40am at Gate 15\n");
	printf("---------------------------------------\n\n");
}


/* Returns 1 if a seat was assigned else 0 */
int assignFirstClassSeat(int seats[])
{
	int seatAssigned = 0;
	int i;
	
	for(i=0; i<5; i++)
	{
		if(seats[i]==0)
		{
			seats[i]=1;
			seatAssigned = 1;
			printPass( i );
			break;
		} 
	}
	
	return seatAssigned;	
}


/* Returns 1 if a seat was assigned else 0 */
int assignEconomySeat(int seats[])
{
	int seatAssigned = 0;
	int i;
	
	for(i=5; i<10; i++)
	{
		if(seats[i]==0)
		{
			seats[i]=1;
			seatAssigned = 1;
			printPass( i );
			break;
		} 
	}
	
	return seatAssigned;	
}


int acceptAlternative(const char *menu)
{
	int choice;
	printf(menu);
	scanf("%d", &choice);
	
    return choice==1;
}


int main()
{
	int seatsTaken = 0;
	int choice;
	int seatsAvailable[ MAXSEATS ] = { 0 };
	
	while(seatsTaken < MAXSEATS )
    {
    	printf(MENU);
    	scanf("%d", &choice);
    	
    	if(choice==1)
    	{
    		if(assignFirstClassSeat(seatsAvailable) == 0 )
    		{
    			if(acceptAlternative(MENU1) == 1) {
    				assignEconomySeat(seatsAvailable); 
    				seatsTaken++;
				}
				else {
					printf("\nNext flight leaves in three hours!\n");
				}
			}
			else {
				seatsTaken++;
			}
		}
    	else if(choice==2)
    	{
    		if(assignEconomySeat(seatsAvailable) == 0 )
    		{
    			if(acceptAlternative(MENU2) == 1) {
    				assignFirstClassSeat(seatsAvailable); 
    				seatsTaken++;
				}
				else {
					printf("\nNext flight leaves in three hours!\n");
				}
			}
			else {
				seatsTaken++;
			}
		}
		else {
			printf("\nInvalid menu option!\n");	
		}
	}	
	printf("\nFlight is now fully booked.\n");
	
    return 0;
}

