 /*
 * Filename:    ex06_24a.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/05/2017
 * With heuristic implemented
 * TODO - Add a function which selects the best move from several options
 *        based upon the best heuristic available from the next possible
 *        move from that square
 *        int getBestMove(int possibleMoves[], int movesAvailable,
 *                       int currentRow, int currentColumn)
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


/*  Return heuristic value if move is a valid move from the current position
 *  otherwise return 0 */
int isValidMove(int currentRow, int currentColumn, int move)
{
    int h;
    currentRow    += vertical[move];
    currentColumn += horizontal[move];
    
    if(currentRow<0 || currentRow>7 ||
       currentColumn<0 || currentColumn>7 ||
       board[currentRow][currentColumn]==1)
       return 0;
       
    h = heuristic[currentRow][currentColumn];
    /* If this is the last square */
    if(h==0)
        return 1;
    else 
        return h;
}


/* Adjust the heuristics of the squares reacheable from
 * the current one to take into account the fact that they 
 * can no longer move to it */
void adjustHeuristic(int currentRow, int currentColumn, int move)
{
    currentRow    += vertical[move];
    currentColumn += horizontal[move];
    
    if(currentRow<0 || currentRow>7 ||
       currentColumn<0 || currentColumn>7 ||
       board[currentRow][currentColumn]==1)
       return;
    else 
        --heuristic[currentRow][currentColumn];
}


int makeATour(int currentRow, int currentColumn)
{
    int squaresVisited = 1;   
    int choice;
    int move;   
    int movesAvailable = 1;
    int possibleMoves[SIZE] = {0};
    int heuristic, bestHeuristic;   
 
    // system("cls");
 
    /* Add the first square and adjust the heuristics */
    board[currentRow][currentColumn]=1;
    for(move=0; move<8; move++)
    {
        adjustHeuristic(currentRow, currentColumn, move); 
    }

//    Uncomment to watch the board    
    printBoard(currentRow, currentColumn);
    
    while( movesAvailable )
    {
        movesAvailable = 0;
        bestHeuristic  = 10;
        
        /* find the move/s with the best heuristic 
         * and add to possibleMoves */
        for(move=0; move<8; move++)
        {
            heuristic = isValidMove( currentRow, currentColumn, move );
            if( heuristic != 0) 
            {
                if(heuristic < bestHeuristic ) {
                    movesAvailable = 0;
                    possibleMoves[movesAvailable]=move;
                    bestHeuristic = heuristic;
                    movesAvailable++     ;
                }
                else if( heuristic == bestHeuristic ) {
                    possibleMoves[movesAvailable]=move;
                    movesAvailable++;
                }
            }  
        }

        // Uncomment when watching the board
         Sleep( 100 ); 
        
        if(movesAvailable > 0)
        {
            if(movesAvailable == 1)
                choice = possibleMoves[ 0 ];
            else
                choice = possibleMoves[ getRandomNum(movesAvailable) ];

            currentRow    += vertical[choice];
            currentColumn += horizontal[choice];
            board[currentRow][currentColumn] = 1;
            squaresVisited++;
            
            for(move=0; move<8; move++)
            {
                adjustHeuristic(currentRow, currentColumn, move); 
            }

// Uncomment to watch the board         
            system("cls");    
            printBoard(currentRow, currentColumn);      
        }
    }    

    return squaresVisited;  
}


int main()
{
    srand(time( NULL ));
    int i, j;
    
    int currentRow; 
    int currentColumn; 
    int squaresVisited;
    int fullTours = 0; 
    
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
            printf("Total Squares visited = %d\n", squaresVisited); 
            printf("From Start position = %d,%d\n",currentRow, currentColumn);
            if(squaresVisited == 64)
                fullTours++;
            else
                Sleep( 2000 );
            //Sleep( 100 );         
        }
    }
    
    printf("%d fulltours made.\n", fullTours);
    getchar();
    
    return 0;
}

