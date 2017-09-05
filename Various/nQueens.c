 /*
 * Filename:	ex06_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/05/2017
 * This is an nQueens version (just change SIZE)
 *
 * Can be improved upon using a look forward method to eliminate
 * as much usage of random as possible
 * To improve this a look forward method could see if a square
 * choice would leave any cols/rows unusable in addition to the
 * ones correctly eliminated
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30

/* Current board state - ie record of squares the knight has visited */
int board[SIZE][SIZE];

int availableSquares[SIZE][SIZE];

/* To help when choosing squares - low=higher priority */
int heuristic[SIZE][SIZE];

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


/* tested and working */
int calculateHeuristic(int row, int col)
{
	int heur = 1;
	
	// update availableSquares array
	int i,j;
	for(i=0; i<SIZE; i++)
	{
		if(i!=col && isValidMove(row, i))
		    heur++;
		
		if(i!=row && isValidMove(i, col))
		    heur++;
	}
	
	// update diagonally up left
	j = col;
	for(i=row; i>=0 && j>=0; i--, j--)
		if(i!=row && j!=col && isValidMove(i,j))
		    heur++;
	    
	// update diagonally down left
	j = col;
	for(i=row; i<SIZE && j>=0; i++, j--)
		if(i!=row && j!=col && isValidMove(i,j))
		    heur++;
	    
	// update diagonally down right
	j = col;
	for(i=row; i<SIZE && j<SIZE; i++, j++)
		if(i!=row && j!=col && isValidMove(i,j))
		    heur++;
	    
	// update diagonally up right
	j = col;
	for(i=row; i>=0 && j<SIZE; i--, j++)
		if(i!=row && j!=col && isValidMove(i,j))
		    heur++;
	
	return heur;
}


void updateHeuristics()
{
	int i, j;
	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			if(isValidMove(i, j)==1)
			    heuristic[i][j]=calculateHeuristic(i,j);
			else
			    heuristic[i][j]=-1;
		}
	}
}


/* If no placement for a queen was found return zero
 * else return the number of best placements found */
int calculateMove()
{
	int availablePlacements = 0;
	int bestRow[SIZE*SIZE];
	int bestCol[SIZE*SIZE];
	int bestHeuristic = 1000;
	int randChoice;
	
	int row, col;
	
	/* Find the squares with the lowest heuristics */
	for(row=0; row<SIZE; row++)
	{
		for(col=0; col<SIZE; col++)
		{
			if(isValidMove(row, col))
			{
				if(heuristic[row][col] < bestHeuristic ) {
					availablePlacements = 0;
					bestHeuristic = heuristic[row][col]
;					bestRow[availablePlacements] = row;
					bestCol[availablePlacements] = col;
					availablePlacements++;
				}
				else if(heuristic[row][col] == bestHeuristic ) {
					bestRow[availablePlacements] = row;
					bestCol[availablePlacements] = col;
					availablePlacements++;
				}
			}
		}
	}
	
	if(availablePlacements == 1) {
		makeMove(bestRow[0], bestCol[0]);
	}
	else if(availablePlacements > 0)
	{
		randChoice = getRandomNum(availablePlacements);
		makeMove(bestRow[randChoice], bestCol[randChoice]);
	}
	
	return availablePlacements;
}


int main()
{
	srand( (time(NULL)) );
    int i, j, queens;
    int count, max=100;
    int solved = 0;
    
    for(count=0; count<max; count++)
    {
	    /* Initialise board state */
	    for(i=0; i<SIZE; i++)
	    {
	    	for(j=0; j<SIZE; j++) {
	    		board[i][j] = 0;
	    		availableSquares[i][j] = 1;
			}	    
		}
		
		updateHeuristics();
		
		
	    queens = 0;
	    system("cls");
	    printBoard();   
		 
	    for(i=0; i<SIZE; i++)
	    {	    
			if(calculateMove() > 0)
			    queens++; 
			else
			    break;
			
			/* Update board state */
			system("cls");
			printBoard(); 
	 		updateHeuristics();
	
	        // Sleep(200);
		}  
		
	    if(queens==SIZE)
	    {
	    	solved++;
	    	printf("\nSOLVED\n");
	    	Sleep(2000);
		}		  	
	}

    printf("Solved %d times from %d attempts\n", solved, max);

    return 0;
}

