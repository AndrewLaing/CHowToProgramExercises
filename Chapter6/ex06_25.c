 /*
 * Filename:    ex06_25.c
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

/* To help when choosing squares - low=higher priority 
 * The accessibility number relates to how many squares
 * the square can be visited from */
int originalHeuristic[SIZE][SIZE] = {
    {2,3,4,4,4,4,3,2},
    {3,4,6,6,6,6,4,3},
    {4,6,8,8,8,8,6,4},
    {4,6,8,8,8,8,6,4},
    {4,6,8,8,8,8,6,4},
    {4,6,8,8,8,8,6,4},
    {3,4,6,6,6,6,4,3},
    {2,3,4,4,4,4,3,2}
};


int heuristic[SIZE][SIZE];


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
//      Sleep( 100 ); 
        
        if(movesAvailable)
        {
            choice = possibleMoves[ getRandomNum(movesAvailable) ];
            currentRow    += vertical[choice];
            currentColumn += horizontal[choice];
            board[currentRow][currentColumn] = 1;
            squaresVisited++;
            
// Uncomment to show board
//          system("cls");    
//          printBoard(currentRow, currentColumn);      
        }
    }    

    return squaresVisited;  
}



int main()
{
    srand(time( NULL ));
    int i, j, k;
    
    int currentRow; 
    int currentColumn; 
    int squaresVisited;
    int squaresVisitedArray[65] = {0};
    
    for(k=0; k<2000; k++)
    {
        for(currentRow=0; currentRow<SIZE; currentRow++) 
        {
            for(currentColumn=0; currentColumn<SIZE; currentColumn++) 
            {
                
                /* Re/initialise heuristic and board */
                for(i=0; i<SIZE; i++) {
                    for(j=0; j<SIZE; j++) {
                        heuristic[i][j] = originalHeuristic[i][j];
                        board[i][j]=0;
                    }   
                }
                
                squaresVisited = makeATour(currentRow, currentColumn);
    
                ++squaresVisitedArray[squaresVisited];  
            }
        }       
    }
    
    for(i=1; i<=64; i++)
    {
        printf("%d\t%d\n", i, squaresVisitedArray[i]);
    }
    
    return 0;
}
