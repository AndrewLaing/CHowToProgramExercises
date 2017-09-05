/*
 * Filename:	ex07_27b.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        09/06/2017.
 * Description: Maze Traversal - Using the right hand against wall method
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // used for the clock methods
#define CLEAR system("cls")
#define MAXROWS 13
#define MAXCOLS 25

enum DIRECTIONS {
	SOUTH, EAST, NORTH, WEST
};


void wait( void );
int canMoveForwards(const char (*)[MAXCOLS], int, int, int );
void mazeTraverse(const char (*)[MAXCOLS], int, int, int );
void printMaze(const char (*)[MAXCOLS], int, int );


const char maze[MAXROWS][MAXCOLS] =
{
	{ '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
	{ ' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',},
	{ '#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#',},
	{ '#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',},
	{ '#','#','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#',},
	{ '#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',},
	{ '#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',},
	{ '#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#',},
	{ '#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',},
	{ '#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',},
	{ '#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#',},
	{ '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',},
	{ '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
};


const int STARTROW = 1;
const int STARTCOL = 0;
const int STARTFACING = 1;
const int ENDROW = 5;
const int ENDCOL = 24;


int main()
{
	CLEAR;
    mazeTraverse(maze, STARTROW, STARTCOL, STARTFACING);
	return 0;
}

void wait()
{
	clock_t start;
	int pauseLength = 300;
	
	start = clock();
	while( clock() < start + pauseLength )
		    ; // pause for pauseLength
}


int canMoveForwards(const char (*maze)[MAXCOLS], int xRow, int xCol, int facing)
{
	if( facing==SOUTH && xRow<MAXROWS-1 )
	    return maze[xRow+1][xCol]==' ';
	else if( facing==EAST && xCol<MAXCOLS-1 )
	    return maze[xRow][xCol+1]==' ';
	else if( facing==NORTH && xRow>0 )
	    return maze[xRow-1][xCol]==' ';
	else if( facing==WEST && xCol>0 )
	    return maze[xRow][xCol-1]==' ';
	return 0;
}



void mazeTraverse(const char (*maze)[MAXCOLS], int xRow, int xCol, int facing)
{
	int i;
	int canMove=0;
	
	printMaze(maze, xRow, xCol);
	
	if( xRow==ENDROW && xCol==ENDCOL ) {
		printf("\n---- MAZE SOLVED :) ----\n");
		return;
	}
	else if( xRow==STARTROW && xCol==STARTCOL && facing!=STARTFACING) {
		printf("\n---- CANNOT SOLVE MAZE :( ----\n");
		return;
	}
    
    wait();
    /* Face to the right and see if it is possible to
	 * move in that direction, because following right wall*/
	facing = (facing+3)%4;
    
    if(canMoveForwards(maze, xRow, xCol, facing) == 0 )
    {
    	facing = (facing+1)%4;
    	for(i=0; i<4; i++) 
		{
    		if(canMoveForwards(maze, xRow, xCol, facing) == 1 )
    		{
    			canMove = 1;
    			break;
			}
			else
    			facing = (facing+1)%4;
		}
	}
	else 
		canMove = 1;
	    
    if(canMove==0)
        printf("\nNo more moves available!\n");
	else if( facing == SOUTH )
	    mazeTraverse( maze, xRow+1, xCol, SOUTH );
	else if( facing == EAST )
	    mazeTraverse( maze, xRow, xCol+1, EAST );
	else if( facing == NORTH )
	    mazeTraverse( maze, xRow-1, xCol, NORTH );	
	else if( facing == WEST )
	    mazeTraverse( maze, xRow, xCol-1, WEST );
}


void printMaze(const char (*maze)[MAXCOLS], int xRow, int xCol)
{
	int i, j;
	
	CLEAR;
	
	for(i=0; i<MAXROWS; i++) {
		for(j=0; j<MAXCOLS; j++) {
			if(i==xRow && j==xCol)
			    printf("X ");
			else
    			printf("%c ",maze[i][j]);
		}
		printf("\n");
	}
}

