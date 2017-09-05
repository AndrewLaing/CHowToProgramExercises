/*
 * Filename:	ex06_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/05/2017
 */

#include <stdio.h>
#define SIZE 20


/* Menu strings */
const char* HELPMESSAGE = 
    "\n1 - Pen up\n"
      "2 - Pen down\n"
      "3 - Turn right\n"
      "4 - Turn left\n"
      "5 - Move\n"
      "6 - Print array\n"
      "7 - Help - print this message\n"
      "9 - Exit\n"
      "0 - Clear array\n\n";


void resetArray( int [][SIZE] );
void printTurtleMoves( int [][SIZE] );
int drawLine( int [][SIZE], int, int, int, int );



void resetArray(int turtleMoves[][SIZE])
{
    int i, j;
    
    for(i=0; i<SIZE; i++)
    {
	for(j=0; j<SIZE; j++)
	    turtleMoves[i][j]=0;
    }
}


void printTurtleMoves(int turtleMoves[][SIZE])
{
    int i, j;
    
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
    	    if(turtleMoves[i][j]==1)
	        printf("*");
	    else
	        printf(" ");
	}
       printf("\n");
    }
}

/* Return the new position on the x or y axis*/
int drawLine(int turtleMoves[][SIZE], int facing, int pen, int x, int y)
{
    int numMoves = 0;
    int i, newPos;
	
    printf("Enter number of spaces to move: ");
    scanf("%d", &numMoves);
    if(facing==0)
    {
	newPos = y;
	for(i=0; i<=numMoves; i++) {
	    if(y-i >= 0) {
		if(pen==1)
		    turtleMoves[y-i][x] = 1;
	    	if(i>0) 
		    newPos--;
	    }
	}
    }
    else if(facing==1)
    {
	newPos = x;
	for(i=0; i<=numMoves; i++) {
	    if(x+i < SIZE) {
		if(pen==1)
		    turtleMoves[y][x+i] = 1; 
		if(i>0) 
	            newPos++;
	    }
	}
    }
    else if(facing==2)
    {
	newPos = y;
	for(i=0; i<=numMoves; i++) {
	    if(y+i < SIZE) {
		if(pen==1)
	            turtleMoves[y+i][x] = 1; 
		if(i>0) 
		    newPos++;
	    }
	}
    }
    else if(facing==3)
    {
	newPos = x;
	for(i=0; i<=numMoves; i++) {
	    if(x-i >= 0) {
		if(pen==1)
		    turtleMoves[y][x-i] = 1; 
		if(i>0) 
		    newPos--;
	    }
	}
    }
	
    return newPos;
}


int main()
{
    int input = 1;
    int command;
    int posX=0, posY=0;
	
    int pen=0;  /* 0=pen up, 1=pen down */
    int facing = 0; /* 0=N, 1=E, 2=S, 3=W */
		
    int turtleMoves[SIZE][SIZE] = { {0} };
        
    while(input==1) 
    {
    	printf("Enter command or 9 to exit: ");
    	scanf("%d", &command);
    	
    	switch(command) {
    	    /* Pen up*/
    	    case 1:
    		pen = 0;
    		break;
    	    /* Pen down */
    	    case 2:
    		pen = 1;
    		break;
    	    /* Turn right */
    	    case 3:
    		facing++;
    		if(facing>3)
    		    facing=0;
    		break;
    	    /* Turn left */
    	    case 4:
    		facing--;
    		if(facing<0)
    		    facing=3;
    		break;
    	    /* Move */
    	    case 5:
    		if(facing==0 || facing==2)
    		    posY = drawLine(turtleMoves, facing, pen, posX, posY );
		else
		    posX = drawLine(turtleMoves, facing, pen, posX, posY );
    		break;
    	    /* Print array */
    	    case 6:
    		printTurtleMoves(turtleMoves);
		break;
    	    /* Help message */
    	    case 7:
    		printf( HELPMESSAGE );
		break;
    	    /* Exit */
	    case 9:
    	        input=0;
		break;
	    /* Clear array */
	    case 0:
		resetArray(turtleMoves);
		posX=0;
		posY=0;
		pen=0;
		facing=0;
		printf("\nTurtle reset.\n");
		break;
	    default:
	        printf("\n<< Illegal Command >>\n");
		break; 
	}
    }
	
    return 0;
}
