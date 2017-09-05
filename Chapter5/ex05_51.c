/*
 * Filename:	ex05_51.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/04/2017
 * Description:	Craps
 * TODO = Add random comments (see spec.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int bankBalance = 1000;
int bet;

int placeBet( void );
int rollDice( void );
int getRandomNum( int, int );
void printRandomComment( void );


int main()
{
    int gameStatus, sum, myPoint;
    int choice;
    
    srand(time( NULL ));
        
	int continuePlaying = 1;
	
	while(continuePlaying > 0)
	{
		placeBet(); 
		
		gameStatus = 0;
	    sum = rollDice();
		
		switch(sum) 
		{
			case 7: case 11:
				gameStatus = 1;
				break;
			case 2: case 3: case 12:
				gameStatus = 2;
				break;
			default:
				gameStatus = 0;
				myPoint = sum;
				printf("Point is %d\n", myPoint );
				break;
		}
		
		while(gameStatus == 0)
		{
			sum = rollDice();
			
			if(sum == myPoint)
			    gameStatus = 1;
			else if(sum == 7)
			    gameStatus = 2; 
		}
		
		if(gameStatus == 1) {
			printf("Player wins\n");
			bankBalance += (bet * 2);
		} 
	    else
	        printf("Player loses\n");
	    
	    if(bankBalance > 0)
	    {
	    	printf("\nOptions\n1: Continue Playing\n2: Cash out\n\nEnter your choice: ");
	        scanf("%d", &choice);
	    
	        if(choice == 2) {
	        	continuePlaying = 0;
		    }
		} else {
			printf("\n\"Sorry we don't give credit! Game Over!\"\n");
			continuePlaying = 0;
		}
    }
    return 0;
}


int placeBet( void )
{
	int valid=1, getBet=1;
	
	printf("Your current bank balance is $%d\n\n", bankBalance);
	
	if(bankBalance > 0)
	{
		while(getBet) 
		{
			printf("How much do you want to bet?: ");
			scanf("%d", &bet);
			if(bankBalance-bet >= 0) {
				bankBalance -= bet;
			    getBet = 0;
			} else {
				printf("\n\"Sorry. You Only have $%d in your account! Try again.\"\n", bankBalance);
			}
		}
		if(getRandomNum(1,2)==2)
		    printRandomComment();
	}
	
	return valid;
}

int rollDice( void )
{
	int die1, die2, worksum;
	
	die1 = getRandomNum(1, 6);
	die2 = getRandomNum(1, 6);
	worksum = die1 + die2;
	printf("Player rolled %d + %d = %d\n", die1, die2, worksum );
	
	return worksum;
}


int getRandomNum(int min, int max)
{
	int res = min + rand()%max;
	return res;
}


void printRandomComment()
{
    int comment = getRandomNum(1,6);
	
	switch(comment)
	{
		case 1:
			printf("\n\"Oh, you're going for broke, huh?\"\n\n");
			break;
		case 2:
			printf("\n\"Aw cmon, take a chance.\"\n\n");
			break;
		case 3:
			printf("\n\"Are you shikkun?\"\n\n");
			break;
		case 4:
			printf("\n\"Last of the big betters, I don't think.\"\n\n");
			break;
		case 5:
			printf("\n\"You probably should have just cashed in your chips.\"\n\n");
			break;
		case 6:
			printf("\n\"Now that's better.\"\n\n");
			break;
		default:
			break;	
	} 	
}

