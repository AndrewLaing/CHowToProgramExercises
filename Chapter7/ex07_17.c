/*
 * Filename:    ex07_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/06/2017.
 * Description: Hare and Tortoise simulation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLEARSCREEN system("cls")

int getRandomNumber( int );
void tickOneSecond( void );

void printField(int harePosition, int tortoisePosition );
int doWeHaveAWinner(int harePosition, int tortoisePosition);
int getHareMove( void );
int getTortoiseMove( void );



int main()
{
    srand( time(0));
    
    int harePosition=1, tortoisePosition=1;
    int weHaveAWinner = 0;
    
    printf("BANG !!!!!\n");
    tickOneSecond();
    printf("AND THEY'RE OFF !!!!!\n");
    tickOneSecond();
    printField(harePosition, tortoisePosition);
    tickOneSecond();

    while(weHaveAWinner==0)
    {
        harePosition += getHareMove();
        tortoisePosition  += getTortoiseMove();
        
        if(harePosition<1)
            harePosition = 1;
        if(tortoisePosition<1)
            tortoisePosition = 1;
        
        printField(harePosition, tortoisePosition);
        
        weHaveAWinner = doWeHaveAWinner(harePosition, tortoisePosition);
        tickOneSecond();
    }
    
    return 0;
}


/* Returns a random number in the range 0 to max-1*/
int getRandomNumber( int max )
{
    return rand()%max;
}


void tickOneSecond()
{
    clock_t start;
    int pauseLength = 1000;
    
    start = clock();
    while( clock() < start + pauseLength )
        ; // pause for pauseLength
}


void printField(int harePosition, int tortoisePosition )
{
    int i;
    CLEARSCREEN;
    
    for(i=1; i<=70; i++)
        printf("-");
    printf("\n");
    
    for(i=1; i<=harePosition; i++)
        printf(" ");
    
    if(harePosition == tortoisePosition ) {
        printf("OUCH!!!\n");
    }
    else
        printf("H\n");
    
    for(i=1; i<=tortoisePosition; i++)
        printf(" ");
    printf("T\n");
    
    for(i=1; i<=70; i++)
        printf("-");
    printf("\n");
}


int doWeHaveAWinner(int harePosition, int tortoisePosition)
{
    if( harePosition>=70 && tortoisePosition>=70 ) {
        printf("It's a tie. (How conventional!)\n");
        return 1;
    }
    else if( harePosition>=70 ) {
        printf("Hare Wins! Yuch.\n");
        return 1;
    }
    else if( tortoisePosition>=70 ) {
        printf("TORTOISE WINS!!! YAY!!!\n");
        return 1;
    }    
    else 
        return 0;
}


int getHareMove()
{
    int randomNum = rand()%1000;
    
    if(randomNum>=800)
        return 0;
    else if(randomNum>=600)
        return 9;   
    else if(randomNum>=500)
        return -12; 
    else if(randomNum>=200)
        return 1;
    else
        return -2;
}


int getTortoiseMove()
{
    int randomNum = rand()%1000;
    
    if(randomNum>=500)
        return 3;
    else if(randomNum>=200)
        return -6;  
    else
        return 1;
}


