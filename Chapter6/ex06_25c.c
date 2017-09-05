 /*
 * Filename:	ex06_25c.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/05/2017
 */
 
#include <windows.h> /* for Sleep() */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

/* Current board state - ie record of squares the knight has visited */
int board[SIZE][SIZE];

/* possible moves a move is h[i]v[i] */
const int horizontal[SIZE] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int vertical[SIZE]   = { -1, -2, -2, -1, 1, 2, 2, 1 };

int getRandomNum( int );
void printBoard( int, int );
int isValidMove( int, int, int );
int makeATour( int, int );


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



int makeATour(int currentRow, int currentColumn)
{
	int squaresVisited = 1;   
	
    board[currentRow][currentColumn]=1;

    int choice;
    int move;
    
    int movesAvailable = 1;
    int possibleMoves[SIZE] = {0};

// Uncomment to show board
//    printBoard(currentRow, currentColumn);
    
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
// Uncomment to show board
//	    Sleep( 100 ); 
	    
	    if(movesAvailable)
	    {
		    choice = possibleMoves[ getRandomNum(movesAvailable) ];
			currentRow    += vertical[choice];
			currentColumn += horizontal[choice];
			board[currentRow][currentColumn] = 1;
			squaresVisited++;
			
// Uncomment to show board
//			system("cls");    
//		    printBoard(currentRow, currentColumn); 	  	
		}
	}    

    return squaresVisited;	
}

int main()
{
	srand(time( NULL ));
	int i, j, keepGoing=1;
	
	int currentRow; 
	int currentColumn; 
	int squaresVisited; 
	
	while(keepGoing>0)
	{
		for(currentRow=0; currentRow<SIZE; currentRow++) 
		{
			for(currentColumn=0; currentColumn<SIZE; currentColumn++) 
			{
				system("cls");
				printf("%d",keepGoing++);
				/* Re/initialise heuristic and board */
				for(i=0; i<SIZE; i++) {
					for(j=0; j<SIZE; j++) {
						board[i][j]=0;
					}	
				}
				
				squaresVisited = makeATour(currentRow, currentColumn);
	
			    if(squaresVisited==64) {
			    	keepGoing=0;
			    	break;
				}
			}
			if(squaresVisited==64) {
			    	break;
			}
		}		
	}

	printf("64 squares visited\n");

    return 0;
}

