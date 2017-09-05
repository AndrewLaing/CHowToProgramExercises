/*
 * Filename:    ex02_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/04/2017
 * Description: Write a program that prints a box, an oval,
 *              an arrow, and a diamond.
 */

#include <stdio.h>

void printStar( int );
void printSpace( int );
void newline( void );
void lineOne( void );
void lineTwo( void );
void lineThree( void );
void lineFour( void );
void lineFive( void );
void lineSix( void );
void lineSeven( void );
void lineEight( void );
void lineNine( void );
void printFigure( void );


int main()
{
    printFigure();
    return 0;
}


void printStar(int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("*");
}

void printSpace(int n)
{
    int i;
    for(i=0; i<n; i++)
        printf(" ");
}

void newline()
{
    printf("\n");
}

void lineOne()
{
    /* First line*/
    printStar(9);
    printSpace(6);
    printStar(3);
    printSpace(8);  
    printStar(1);
    printSpace(10);  
    printStar(1);
    newline();  
}


void lineTwo()
{
    /* Second line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(3);  
    printStar(1);
    printSpace(6);  
    printStar(3);
    printSpace(8);  
    printStar(1);
    printSpace(1);  
    printStar(1);
    newline();  
}

void lineThree()
{
    /* Third line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(4);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(4);  
    printStar(5);
    printSpace(6);  
    printStar(1);
    printSpace(3);  
    printStar(1);
    newline();  
}

void lineFour()
{
    /* Fourth line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(4);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(6);  
    printStar(1);
    printSpace(7);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    newline();  
}

void lineFive()
{
    /* Fifth line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(4);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(6);  
    printStar(1);
    printSpace(6);  
    printStar(1);
    printSpace(7);  
    printStar(1);
    newline();  
}

void lineSix()
{
    /* Sixth line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(4);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(6);  
    printStar(1);
    printSpace(7);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    newline();  
}

void lineSeven()
{
    /* Seventh line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(4);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(6);  
    printStar(1);
    printSpace(8);  
    printStar(1);
    printSpace(3);  
    printStar(1);
    newline();  
}

void lineEight()
{
    /* Eighth line*/
    printStar(1);
    printSpace(7);
    printStar(1);
    printSpace(4);  
    printStar(1);
    printSpace(5);  
    printStar(1);
    printSpace(6);  
    printStar(1);
    printSpace(9);  
    printStar(1);
    printSpace(1);  
    printStar(1);
    newline();  
}

void lineNine()
{
    /* Ninth line*/
    printStar(9);
    printSpace(6);
    printStar(3);
    printSpace(8);  
    printStar(1);
    printSpace(10);  
    printStar(1);
    newline();  
}

void printFigure()
{
    lineOne();
    lineTwo();
    lineThree();
    lineFour();
    lineFive();
    lineSix();
    lineSeven();
    lineEight();
    lineNine();
}


