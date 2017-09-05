 /*
 * Filename:	ex06_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/05/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

/* Current board state - ie record of squares the knight has visited */
int board[SIZE][SIZE];

/* possible moves a move is h[i]v[i] */
const int horizontal[SIZE] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int vertical[SIZE]   = { -1, -2, -2, -1, 1, 2, 2, 1 };

/* To help when choosing squares - low=higher priority */
int heuristic[SIZE][SIZE] = {
	{2,3,4,4,4,4,3,2},
	{3,4,6,6,6,6,4,3},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{3,4,6,6,6,6,4,3},
	{2,3,4,4,4,4,3,2}
};



int getRandomNum( int );
void printBoard( int, int );
int isValidMove( int, int, int );



int getRandomNum(int max)
{
	return rand()%max;
}


void printBoard(int currentRow, int currentColumn) 
{
	int h, v;
	for(v=0; v<SIZE; v++)
	{
		for(h=0; h<SIZE; h++){
			if( v==currentRow && h==currentColumn )
			    printf("$ ");
			else if( board[v][h]==1 )
			    printf("x ");
			else
			    printf(": ");
		}
		printf("\n");
	}
}

/*  Return 1 if move is a valid move from the current position
 *  otherwise return 0 */
int isValidMove(int currentRow, int currentColumn, int move)
{
	currentRow    += vertical[move];
	currentColumn += horizontal[move];
	
	if(currentRow<0 || currentRow>7 ||
	   currentColumn<0 || currentColumn>7 ||
	   board[currentRow][currentColumn]==1)
	   return 0;
	else 
	    return 1;
}


int main()
{
	srand(time( NULL ));
	
	int squaresVisited = 1;
    int currentRow = getRandomNum(SIZE); 
	int currentColumn = getRandomNum(SIZE);      
    
    board[currentRow][currentColumn]=1;

    int choice;
    int move;
    
    int movesAvailable = 1;
    int possibleMoves[SIZE] = {0};
    
    printBoard(currentRow, currentColumn);
    
    while( movesAvailable )
    {
    	movesAvailable=0;
    	
	    for(move=0; move<8; move++)
	    {
	    	if(isValidMove( currentRow, currentColumn, move ) ) {
	    		possibleMoves[movesAvailable]=move;
	    		movesAvailable++;
			}  
		}

	    getchar();
	    
	    if(movesAvailable)
	    {
		    choice = possibleMoves[ getRandomNum(movesAvailable) ];
			currentRow    += vertical[choice];
			currentColumn += horizontal[choice];
			board[currentRow][currentColumn] = 1;
			squaresVisited++;
			system("cls");    
		    printBoard(currentRow, currentColumn); 	
			printf("Squares visited = %d\n", squaresVisited);    	
		}
	}    

    printf("\nNo more moves possible.\n");
    
    return 0;
}

