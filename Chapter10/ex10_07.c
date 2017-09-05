/*
 * Filename:    ex10_07.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/07/2017.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct card {
    unsigned face : 4;
    unsigned suit : 2;
    unsigned colour : 1;
};

typedef struct card Card;

void fillDeck( Card * const );
void shuffle( Card * const);
void deal( const Card * const );


int main()
{    
    srand(time(NULL));
    Card deck[52];
    
    fillDeck( deck );
    shuffle( deck );
    deal( deck );
     
    return 0;
}


void fillDeck( Card * const wDeck )
{
    int i;
    for( i=0; i<=51; i++ )
    {
        wDeck[i].face =  i % 13;
        wDeck[i].suit =  i / 13;
        wDeck[i].colour = i / 26;
    }
}


void shuffle( Card * const wDeck)
{
    int i, j;
    Card temp;
    
    for( i=0; i<=51; i++ )
    {
        j = rand()%52;
        temp = wDeck[i];
        wDeck[i] = wDeck[j];
        wDeck[j] = temp;
    }
}


void deal( const Card * const wDeck )
{
    int k1, k2;
    
    for( k1=0, k2=k1+26; k1<=25; k1++, k2++ )
    {
        printf("Colour:%2d  Card:%3d  Suit:%2d     ",
               wDeck[k1].colour, wDeck[k1].face, wDeck[k1].suit);
        printf("Colour:%2d  Card:%3d  Suit:%2d\n",
               wDeck[k2].colour, wDeck[k2].face, wDeck[k2].suit);
    }
}

