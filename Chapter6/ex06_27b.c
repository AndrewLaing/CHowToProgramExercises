 /*
 * Filename:    ex06_27b.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/05/2017
 * Description: Exhaustive method of solving 8 Queens
 */

#include <windows.h> /* for Sleep() */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

/* Current board state - ie record of squares the knight has visited */
int board[SIZE][SIZE];

int availableSquares[SIZE][SIZE];


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
    /* Initialise board state */
    initialiseBoard();
    
    printBoard();   

    int solved = 0;

    int max=SIZE;
    int a, b, c, d, e, f, g, h;
    int i, j, k, l, m, n, o, p;
    
    for(a=0, b=0; b<max; b++) {
        for(c=1, d=0; d<max; d++)
            for(e=2, f=0; f<max; f++)
                for(g=3, h=0; h<max; h++)
                    for(i=4, j=0; j<max; j++) 
                        for(k=5, l=0; l<max; l++)
                            for(m=6, n=0; n<max; n++)
                                for(o=7, p=0; p<max; p++) 
                                {
                                    initialiseBoard();
                                    if(isValidMove(a,b)) 
                                    {
                                        makeMove(a, b);
                                        if(isValidMove(c,d)) 
                                        {
                                            makeMove(c, d);
                                            if(isValidMove(e,f)) 
                                            {
                                                makeMove(e, f);
                                                if(isValidMove(g,h)) 
                                                {
                                                    makeMove(g, h);
                                                    if(isValidMove(i,j)) 
                                                    {
                                                        makeMove(i, j);
                                                        if(isValidMove(k,l)) 
                                                        {
                                                            makeMove(k, l);
                                                            if(isValidMove(m,n)) 
                                                            {
                                                                makeMove(m, n);
                                                                if(isValidMove(o,p)) 
                                                                {
                                                                    makeMove(o, p);
                                                                    system("cls");
                                                                    printBoard();
                                                                    printf("\n");
                                                                    
                                                                    solved++;
                                                                }
                                                            }
                                                        } 
                                                    }
                                                }
                                            }
                                        }
                                    }   
                                }
    }
            
    printf("\nSolved %d times\n", solved);
    return 0;
}

