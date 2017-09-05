 /*
 * Filename:	ex06_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/05/2017
 * ToDo: Implement a simple solving algorithm
 *		 Implement a heuristic
 */

#include <windows.h> /* for Sleep() */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

/* Current board state - ie record of squares the knight has visited */
int board[SIZE][SIZE];

int availableSquares[SIZE][SIZE];

/* To help when choosing squares - low=higher priority */
int heuristic[SIZE][SIZE] = {
	{22,22,22,22,22,22,22,22},
	{22,24,24,24,24,24,24,22},
	{22,24,26,26,26,26,24,22},
	{22,24,26,28,28,26,24,22},
	{22,24,26,28,28,26,24,22},
	{22,24,26,26,26,26,24,22},
	{22,24,24,24,24,24,24,22},
	{22,22,22,22,22,22,22,22}
};


int getRandomNum( int );


int getRandomNum(int max)
{
	return rand()%max;
}


void printBoard() 
{
	int h, v;
	for(v=0; v<SIZE; v++)
	{
		for(h=0; h<SIZE; h++){
			if( board[v][h]==1 )
			    printf("@ ");
			else
			    printf(": ");
		}
		printf("\n");
	}
}


void printHeuristic() 
{
	int h, v;
	for(v=0; v<SIZE; v++)
	{
		for(h=0; h<SIZE; h++){
			printf("%2d ", heuristic[h][v]);
		}
		printf("\n");
	}
}


/*  Return 1 if move is a valid move otherwise return 0 */
int isValidMove(int row, int col)
{
	return availableSquares[row][col];
}


/* tested and working */
void makeMove(int row, int col)
{
	board[row][col]=1;
	
	// update availableSquares array
	int i,j;
	for(i=0; i<SIZE; i++)
	{
		availableSquares[row][i]=0;
		availableSquares[i][col]=0;
	}
	
	// update diagonally up left
	j = col;
	for(i=row; i>=0 && j>=0; i--, j--)
	    availableSquares[i][j]=0;
	    
	// update diagonally down left
	j = col;
	for(i=row; i<SIZE && j>=0; i++, j--)
	    availableSquares[i][j]=0;
	    
	// update diagonally down right
	j = col;
	for(i=row; i<SIZE && j<SIZE; i++, j++)
	    availableSquares[i][j]=0;
	    
	// update diagonally up right
	j = col;
	for(i=row; i>=0 && j<SIZE; i--, j++)
	    availableSquares[i][j]=0;
}


void initialiseBoard()
{
	int i, j;
    
    /* Initialise board state */
    for(i=0; i<SIZE; i++)
    {
    	for(j=0; j<SIZE; j++) {
    		board[i][j] = 0;
    		availableSquares[i][j] = 1;
		}	    
	}
}


int main()
{
    int choiceRow, choiceCol;
    
    /* Initialise board state */
    initialiseBoard();
    
    printBoard();   

    int x, y, queens;
    int solved = 0;
    
    for(y=0; y<2000; y++)
    {
    	queens = 0;
    	initialiseBoard();
    	
	    for(choiceRow=0; choiceRow<SIZE; choiceRow++)
	    {
	    	for(x=0;x<1000;x++)
	    	{
	    		choiceCol = getRandomNum(SIZE);
				if( isValidMove(choiceRow, choiceCol) ) {
					makeMove(choiceRow, choiceCol);
					queens++;
					break;
				}
			}
			if(x >= 1000)
			    break;
			
//			system("cls");
//			printBoard(); 
		} 
		
		system("cls");
		printBoard(); 
		
		if(queens==8)
			solved++;
			
		printf("\nSolved %d times\n", solved);
		 	
	}

    return 0;
}

