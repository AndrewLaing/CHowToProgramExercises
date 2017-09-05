/*
 * Filename:	ex07_27a.c
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

#define MAXROWS 13      /* MAx must be an odd number > 1*/
#define MAXCOLS 25

void shuffle( int *, size_t );
int getRandomNumber( int );
void removeWalls( int (*)[MAXCOLS], int (*)[MAXCOLS/2], int, int );
void initialiseMazeArray( int (*)[MAXCOLS] );
void drawMaze( int (*)[MAXCOLS] );
int squareVisited(int (*)[MAXCOLS/2], int, int );

void removeTopWall(int (*)[MAXCOLS], int , int );
void removeLeftWall(int (*)[MAXCOLS], int , int );
void removeBottomWall(int (*)[MAXCOLS], int , int );
void removeRightWall(int (*)[MAXCOLS], int , int );

void addRandomEntrances(int (*)[MAXCOLS]);

// Methods /////////////////////////////////

int main()
{
	int maze[MAXROWS][MAXCOLS] = { {0} };        /* Used to hold the finished maze */
    int visited[MAXROWS/2][MAXCOLS/2] = { {0} }; /* Used to hold the positiojns visited for use
										  * by the Depth-first Algorithm */
	
	srand(time(NULL));
	
	int startRow = getRandomNumber(MAXROWS/2);
	int startCol = getRandomNumber(MAXCOLS/2);
	
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
void removeWalls(int (*maze)[MAXCOLS], int (*visited)[MAXCOLS/2],
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
			if( ( startRow<(MAXROWS/2)-1 ) && ( squareVisited(visited, startRow+1, startCol)==0 ) )
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
			if( (  startCol<(MAXCOLS/2)-1 ) && ( squareVisited(visited, startRow, startCol+1)==0) )
			{
				removeRightWall(maze, startRow, startCol);
				removeWalls(maze, visited, startRow, startCol+1);
			}
		}
	}
}


/* Add the positions and walls to the maze template */
void initialiseMazeArray(int (*maze)[MAXCOLS])
{
	int i, j;
	for(j=0; j<MAXCOLS; j++) {
		maze[0][j] = 1;
		maze[MAXROWS-1][j] = 1;
	}
	
	for(i=1; i<MAXROWS-1; i++) {
		for(j=0; j<MAXCOLS; j++)
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
void drawMaze(int (*maze)[MAXCOLS])
{
	int i, j;
	printf("{\n");
	for(i=0; i<MAXROWS; i++) {
		printf("{ ");
		for(j=0; j<MAXCOLS; j++) {
			if(maze[i][j]==1)
				printf("'#',");// printf("# "); 
			else
				printf("' ',"); // printf("  ");
		}
		printf("},\n"); // printf("\n");
	}
	printf("\n}\n"); // printf("\n");
}


/* Check whether the position has been visited before - 1=yes */
int squareVisited(int (*visited)[MAXCOLS/2], int row, int col )
{
	return visited[row][col];
}


/* Remove a wall from the maze array */
void removeTopWall(int (*maze)[MAXCOLS], int startRow, int startCol)
{
	int removeRow, removeCol;
	removeRow = ((startRow - 1)+1)*2;
	removeCol = (startCol)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}


/* Remove a wall from the maze array */
void removeLeftWall(int (*maze)[MAXCOLS], int startRow, int startCol)
{
	int removeRow, removeCol;

	removeCol = ((startCol - 1)+1)*2;
	removeRow = (startRow)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}


/* Remove a wall from the maze array */
void removeBottomWall(int (*maze)[MAXCOLS], int startRow, int startCol)
{
	int removeRow, removeCol;

	removeRow = (startRow + 1)*2;
	removeCol = (startCol)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}


/* Remove a wall from the maze array */
void removeRightWall(int (*maze)[MAXCOLS], int startRow, int startCol)
{
	int removeRow, removeCol;

	removeCol = (startCol + 1)*2;
	removeRow = (startRow)*2 - 1 + 2;
	maze[removeRow][removeCol] = 0;
}

/* Add Random Entrances at opposite sides of the maze */
void addRandomEntrances(int (*maze)[MAXCOLS])
{
	int rndStartRow=0, rndStartCol=0;
	int rndEndRow=MAXROWS-1, rndEndCol=MAXCOLS-1;
	
	if((rand()%3)==1) {
		rndStartRow = (rand()%(MAXROWS-2)+1);
		if(rndStartRow%2==0)
		    rndStartRow++;

		rndEndRow = (rand()%(MAXROWS-2)+1);
		if(rndEndRow%2==0)
		    rndEndRow++;	
	}
	else {
		rndStartCol = (rand()%(MAXCOLS-2)+1);
		if(rndStartCol%2==0)
		    rndStartCol++;

		rndEndCol = (rand()%(MAXCOLS-2)+1);
		if(rndEndCol%2==0)
		    rndEndCol++;
	}
	
	maze[rndStartRow][rndStartCol]=0;
	maze[rndEndRow][rndEndCol]=0;
}

