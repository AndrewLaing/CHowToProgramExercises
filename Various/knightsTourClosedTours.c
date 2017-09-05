 /*
 * Filename:    ex06_29.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/05/2017
 * With heuristic implemented and lookahead in the event of a tie
 * Note this has so far never found 64 full tours because sometimes the 
 *      best heuristic move will result in a dead end
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

int firstRow, firstCol;
int lastRow, lastCol;


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
int getBestMove(int[], int, int, int );
void adjustHeuristic(int, int, int );
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


/* Return the move which will lead to the best heuristic from
 * the move following it */
int getBestMove(int possibleMoves[], int movesAvailable,
                int currentRow, int currentColumn)
{
    int i, possibleMove, move, bestMove;
    int moveRow, moveColumn;
    int heuristic, bestHeuristic;
    
    for(i=0; i<movesAvailable; i++)
    {
        bestHeuristic = 10;
        
        possibleMove = possibleMoves[i];
        // calculate position after move
        moveRow    = currentRow + vertical[possibleMove];
        moveColumn = currentColumn + horizontal[possibleMove];
        
        // calculate best heuristic after move
        for(move=0; move<8; move++)
        {
            heuristic = isValidMove( moveRow, moveColumn, move );
            if( heuristic != 0) 
            {
                if(heuristic < bestHeuristic ) {
                    bestHeuristic = heuristic;
                    bestMove = possibleMove;
                }
            }  
        }
    }
    
    // return best move
    return bestMove;
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
 
    firstRow = currentColumn;
    firstCol = currentRow;
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
        // Sleep( 50 ); 
        
        if(movesAvailable > 0)
        {
            if(movesAvailable == 1)
                choice = possibleMoves[ 0 ];
            else
                choice = getBestMove(possibleMoves, movesAvailable,
                                     currentRow, currentColumn);

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
        
        lastRow = currentRow;
        lastCol = currentColumn;
    }    

    return squaresVisited;  
}


int isClosedTour()
{
    if(lastCol == firstCol) {
        if(lastRow-1 == firstRow)
            return 1;
        if(lastRow+1 == firstRow)
            return 1;
    }

    if(lastRow-1 == firstRow || lastRow+1 == firstRow || lastRow == firstRow) 
    {
        if(lastCol-1 == firstCol)
            return 1;
        if(lastCol+1 == firstCol)
            return 1;
    }
    
    return 0;
}


int main()
{
    srand(time( NULL ));
    int i, j;
    
    int currentRow; 
    int currentColumn; 
    int squaresVisited;
    int fullTours = 0, closedTours = 0; 
    
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
            printf("From Start position = %d,%d\n",firstRow, firstCol);
            printf("To end position     = %d,%d\n",lastRow, lastCol);
            if(squaresVisited == 64)
            {
                fullTours++;
                if(isClosedTour()) {
                    printf("\nCLOSED TOUR DETECTED\n");
                    closedTours++;
                    getchar();
                }
            }
                
            else
                Sleep( 200 );
            Sleep( 100 );           
        }
    }
    
    printf("%d fulltours made.\n", fullTours);
    printf("%d closed tours made.\n", closedTours);
    getchar();
    
    return 0;
}

