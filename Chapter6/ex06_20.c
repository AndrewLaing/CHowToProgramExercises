/*
 * Filename:	ex06_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/05/2017
 * Description:	Craps
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAMES 5000

int rollDice( void );
int getRandomNum( int, int );


int main()
{
    int gameStatus, sum, myPoint;
    
    int winRolls[22]  = {0};
    int loseRolls[22] = {0};
    int totalWon=0, totalLost=0;
    
    srand(time( NULL )); 
        
    int rollNumber;
    int totalRolls = 0;
	
    int i;
	
    for(i=1; i<=GAMES; i++)
    {	
	gameStatus = 0;
        sum = rollDice();
	rollNumber = 1;
		
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
		break;
	}
		
	while(gameStatus == 0)
	{
	    ++rollNumber;	
	    sum = rollDice();
			
	    if(sum == myPoint)
	        gameStatus = 1;
	    else if(sum == 7)
	        gameStatus = 2; 
	}
	    
        // add rolls made during the game to totalRolls
	totalRolls += rollNumber;
		
	if(gameStatus == 1) {
	    // printf("Player wins\n");
	    if(rollNumber <= 20)
	        ++winRolls[rollNumber];
	    else
	        ++winRolls[21];
	}	    
        else {
	    // printf("Player loses\n");
	    if(rollNumber <= 20)
	        ++loseRolls[rollNumber];
	    else
	        ++loseRolls[21];
	}
    }
    
    printf("WINNING ROLLS\n");
	
    for(i=1; i<21; i++) {
    	if(i<10)
    	    printf("%4d", i);
    	else
    	    printf("%3d", i);
	}
    printf(" >20\n");

    for(i=1; i<=21; i++) {
    	totalWon += winRolls[i];
    	
    	if(i<10)
        	printf("%4d", winRolls[i]);
    	else
        	printf("%3d", winRolls[i]);
	}

    printf("\n\nLOSING ROLLS\n");
    for(i=1; i<21; i++) {
    	if(i<10)
    	    printf("%4d", i);
    	else
    	    printf("%3d", i);
	}
    printf(" >20\n");

    for(i=1; i<=21; i++) {
    	totalLost += loseRolls[i];
    	
    	if(i<10)
            printf("%4d", loseRolls[i]);
    	else
            printf("%3d", loseRolls[i]);
    }

    printf("\n\nTotal games won:\t%3d\n", totalWon);
    printf("Total games lost:\t%3d\n", totalLost);
    printf("Average game length:\t%3d\n", totalRolls/GAMES);

    return 0;
}


int rollDice( void )
{
    int die1, die2, worksum;
	
    die1 = getRandomNum(1, 6);
    die2 = getRandomNum(1, 6);
    worksum = die1 + die2;
    // printf("Player rolled %d + %d = %d\n", die1, die2, worksum );
	
    return worksum;
}


int getRandomNum(int min, int max)
{
    int res = min + rand()%max;
    return res;
}
