/*
 * Filename:	ex07_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        09/06/2017.
 * Description: Creates a Maze with a Depth-first search Algorithm
 *
 * Pseudo code for Algorithm:
 *				Start at a random cell.
 *					Mark the current cell as visited, and get a list of its neighbors.
 * 					For each neighbor, starting with a randomly selected neighbor:
 *				    If that neighbor hasn't been visited, remove the wall between
 *					this cell and that neighbor, and then recurse with
 *					that neighbor as the current cell.
 *
 * TODO:        Add an entrance and exit point to the maze on an odd numbered square
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAUSE system("pause")
#define CLEARSCREEN system("cls")

#define MAX 13      /* MAx must be an odd number > 1*/


void shuffle( int *, size_t );
int getRandomNumber( int );
void removeWalls( int (*)[MAX], int (*)[MAX/2], int, int );
void initialiseMazeArray( int (*)[MAX] );
void drawMaze( int (*)[MAX] );
int squareVisited(int (*)[MAX/2], int, int );

void removeTopWall(int (*)[MAX], int , int );
void removeLeftWall(int (*)[MAX], int , int );
void removeBottomWall(int (*)[MAX], int , int );
void removeRightWall(int (*)[MAX], int , int );

void addRandomEntrances(int (*)[MAX]);

// Methods /////////////////////////////////

int main()
{
	int maze[MAX][MAX] = { {0} };        /* Used to hold the finished maze */
    int visited[MAX/2][MAX/2] = { {0} }; /* Used to hold the positiojns visited for use
										  * by the Depth-first Algorithm */
	
	srand(time(NULL));
	
	int startRow = getRandomNumber(MAX/2);
	int startCol = getRandomNumber(MAX/2);
	
	/* Create the visual representation of maze */
	initialiseMazeArray(maze);

	/* Call maze creator */
    removeWalls(maze, visited, startRow, startCol);
    addRandomEntrances(maze);
	CLEARSCREEN;
    drawMaze(maze);
	PAUSE;

	return 0;
}

/* Shuffle method randomly shuffles an array */
void shuffle(int *array, size_t n)
{
	size_t i, j;
    int t;
	
    if (n > 1)
	{
        for (i = 0; i < n - 1; i++)
		{
            j = i + rand() / (RAND_MAX / (n - i) + 1);
            t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}


/* Returns a random number in the range 0 to max-1*/
int getRandomNumber( int max )
{
	return rand()%max;
}


/* Recursive method which uses the depth-first algorithm
 * to create the maze */
void removeWalls(int (*maze)[MAX], int (*visited)[MAX/2],
                 int startRow, int startCol)
{
	/* Mark trhe start position as visited */
    visited[startRow][startCol] = 1;

	/* Remove walls between current square and adjacent visited squares
	 * in a random order */
    int i;
	int order[4] = {0,1,2,3};
	
	for(i=0; i<6; i++)
    	shuffle(order, 4);

    for(i=0; i<4; i++)
    {
    	if(order[i]==0)
		{
			/* If the position above has not been visited
			 * remove the wall between it and the start row */
			if(startRow>0 && (squareVisited(visited, startRow-1, startCol)==0) )
			{
				removeTopWall(maze, startRow, startCol);
				removeWalls(maze, visited, startRow-1, startCol);
			}
		}
    	if(order[i]==1)
		{
			/* If the position below has not been visited
			 * remove the wall between it and the start row */
			if( ( startRow<(MAX/2)-1 ) && ( squareVisited(visited, startRow+1, startCol)==0 ) )
			{
				removeBottomWall(maze, startRow, startCol);
				removeWalls(maze, visited, startRow+1, startCol);
			}
		}
    	if(order[i]==2)
		{
			/* If the position ato the left has not been visited
			 * remove the wall between it and the start row */
			if( ( startCol>0 ) && ( squareVisited(visited, startRow, startCol-1)==0) )
			{
				removeLeftWall(maze, startRow, startCol);
				removeWalls(maze, visited, startRow, startCol-1);
			}
		}
    	if(order[i]==3)
		{
			/* If the position to the right has not been visited
			 * remove the wall between it and the start row */
			if( (  startCol<(MAX/2)-1 ) && ( squareVisited(visited, startRow, startCol+1)==0) )
			{
				removeRightWall(maze, startRow, startCol);
				removeWalls(maze, visited, startRow, startCol+1);
			}
		}
	}
}


/* Add the positions and walls to the maze template */
void initialiseMazeArray(int (*maze)[MAX])
{
	int i, j;
	for(j=0; j<MAX; j++) {
		maze[0][j] = 1;
		maze[MAX-1][j] = 1;
	}
	
	for(i=1; i<MAX-1; i++) {
		for(j=0; j<MAX; j++)
		{
			if(i%2==0)
				maze[i][j] = 1;
			else {
				if(j%2==0)
	    			maze[i][j] = 1;
				else
	    			maze[i][j] = 0;
			}
		}
	}
}

/* Draw the maze to the terminal */
void drawMaze(int (*maze)[MAX])
{
	int i, j;
	// printf("{\n");
	for(i=0; i<MAX; i++) {
		// printf("{ ");
		for(j=0; j<MAX; j++) {
			if(maze[i][j]==1)
				printf("# "); // printf("'#',");
			else
				printf("  "); // printf("' ',");
		}
		printf("\n"); // printf("},\n");
	}
	printf("\n"); // printf("\n}\n");
}


/* Check whether the position has been visited before - 1=yes */
int squareVisited(int (*visited)[MAX/2], int row, int col )
{
	return visited[row][col];
}


/* Remove a wall from the maze array */
void removeTopWall(int (*maze)[MAX], int startRow, int startCol)
{
	int removeRow, removeCol;
	removeRow = ((startRow - 1)+1)*2;
	removeCol = (startCol)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}


/* Remove a wall from the maze array */
void removeLeftWall(int (*maze)[MAX], int startRow, int startCol)
{
	int removeRow, removeCol;

	removeCol = ((startCol - 1)+1)*2;
	removeRow = (startRow)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}


/* Remove a wall from the maze array */
void removeBottomWall(int (*maze)[MAX], int startRow, int startCol)
{
	int removeRow, removeCol;

	removeRow = (startRow + 1)*2;
	removeCol = (startCol)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}


/* Remove a wall from the maze array */
void removeRightWall(int (*maze)[MAX], int startRow, int startCol)
{
	int removeRow, removeCol;

	removeCol = (startCol + 1)*2;
	removeRow = (startRow)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}

/* Add Random Entrances at opposite sides of the maze */
void addRandomEntrances(int (*maze)[MAX])
{
	int rndStartRow=0, rndStartCol=0;
	int rndEndRow=MAX-1, rndEndCol=MAX-1;
	
	if((rand()%3)==1) {
		rndStartRow = (rand()%(MAX-2)+1);
		if(rndStartRow%2==0)
		    rndStartRow++;

		rndEndRow = (rand()%(MAX-2)+1);
		if(rndEndRow%2==0)
		    rndEndRow++;	
	}
	else {
		rndStartCol = (rand()%(MAX-2)+1);
		if(rndStartCol%2==0)
		    rndStartCol++;

		rndEndCol = (rand()%(MAX-2)+1);
		if(rndEndCol%2==0)
		    rndEndCol++;
	}
	
	maze[rndStartRow][rndStartCol]=0;
	maze[rndEndRow][rndEndCol]=0;
}

