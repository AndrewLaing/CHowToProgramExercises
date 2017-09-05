/*
 * Filename:    ex07_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/05/2017.
 *
 * TODO - This will contain the deck and shuffling algorithm
 *        which will be tested here before being added to
 *        the Poker program
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNumber( int );
void printDeck(const int [][13]);
void shuffle( int [][13] );
void reinitialiseDeck( int [][13] );



int main()
{
    srand( time(0));
    int deck[4][13] = { {0} };
    reinitialiseDeck( deck );
    
    printf("\n\n -- Before Shuffling ----\n\n");
    printDeck( deck );
    
    shuffle( deck );
    printf("\n\n -- After Shuffling ----\n\n");
    printDeck( deck );
    return 0;
}


int getRandomNumber( int max )
{
    return rand()%max;
}


/* Add a method to print out number stored in the deck */
void printDeck(const int wDeck[][13])
{
    int row, column;
    
    printf(" ");
    for(column=0; column<13; column++)
        printf("%4d",column);
    printf("\n");
    
    for( row=0; row<4; row++) {
        printf("%d", row);
        for(column=0; column<13; column++)
            printf("%4d",wDeck[row][column]);
        printf("\n");
    }
}


/* Add the shuffling algorithm */
/* Might be better to choose two random rumbers
 * for suit and face and swap with current iteration
 * through the deck */
/* Set all cards to 0 before shuffling */
void shuffle( int wDeck[][13] )
{
    int row, column;
    int randRow, randColumn, temp;
    int pass;
    
    for(pass=0; pass<4; pass++)
    {
        for( row=0; row<1; row++) {
            for(column=0; column<13; column++) {
                randRow    = getRandomNumber(4);
                randColumn = getRandomNumber(13);  
                temp = wDeck[row][column];
                wDeck[row][column] = wDeck[randRow][randColumn];
                wDeck[randRow][randColumn] = temp;
            }   
        }       
    }
}


/* Set all cards to 0 before shuffling */
void reinitialiseDeck( int wDeck[][13] )
{
    /* Deck is full again */
    //deckPosition = 1;
    
    int row, column;
    int startValue = 1;
    
    for( row=0; row<4; row++) {
        for(column=0; column<13; column++)
            wDeck[row][column] = startValue++;  
    }
}

