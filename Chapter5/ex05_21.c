/*
 * Filename:    ex05_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 */

#include <stdio.h>


void drawLine( int, char );
void drawSquare( int, char );
void drawTriangle( int, char );
void drawDiamond( int, char );


int main()
{
    drawLine(5, '#');
    drawSquare(5, '#'); 
    drawTriangle(5, '#');
    drawDiamond(5, '#');

    return 0;
}


void drawLine(int n, char c)
{
    int i;
    
    for(i=0; i<n; i++) {
        printf("%c", c);;
    }
    
    printf("\n\n");
}



void drawSquare(int n, char c)
{
    int i, j;
    
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("%c", c);
        }
        printf("\n");
    }
    
    printf("\n");
}


void drawTriangle(int n, char c)
{
    int i, j;
    
    for(i=0; i<n; i++) {
        for(j=0; j<n-i-1; j++) {
            printf(" ");
        }
        for(j=0; j<i+1+i; j++) {
            printf("%c", c);
        }
        printf("\n");
    }
    
    printf("\n");
}


void drawDiamond(int n, char c)
{
    int i, j;
    
    for(i=0; i<n; i++) {
        for(j=0; j<n-i-1; j++) {
            printf(" ");
        }
        for(j=0; j<i+1+i; j++) {
            printf("%c", c);
        }
        printf("\n");
    }
    
    for(i=n-1; i>=0; i--) {
        for(j=0; j<n-i-1; j++) {
            printf(" ");
        }
        for(j=0; j<i+1+i; j++) {
            printf("%c", c);
        }
        printf("\n");
    }
    
    printf("\n");
}

