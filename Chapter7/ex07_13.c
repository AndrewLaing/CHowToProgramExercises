/*
 * Filename:	ex07_13.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        28/05/2017.
 * Description: Deal and check a poker hand
 *
 * TODO - Check for next highest card in compare hands etc
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HANDSIZE 5

/* /////////////////////////////////////////////////// */
/* //////////////// PROTOTYPES /////////////////////// */
/* /////////////////////////////////////////////////// */

void compareHands(const int *, const int *, const int *, const int * );
void dealAHand( const int [][13], int * );
void rankHand( const int [][13], const int *, int * );
void shuffle( int [][13]);
int dealACard( void );

void printHand(int * );
void printCardName( const int [][13], int );
void sortHand( const int [][13], int * );
int getCardFace( const int [][13], int );
int getCardSuit( const int [][13], int );

int isFourOFAKind( const int [][13], const int * );
int isThreeOFAKind( const int [][13], const int * );
int isFlush( const int [][13], const int * );
int isStraight( const int [][13], const int * );
int isFullHouse( const int [][13], const int * );
int isTwoPair( const int [][13], const int * );
int isOnePair( const int [][13], const int * );
int getHighCard( const int [][13], const int * );


/* /////////////////////////////////////////////////// */
/* ///////////////// VARIABLES /////////////////////// */
/* /////////////////////////////////////////////////// */


int deckPosition = 1;  /* 1 is the top card, 2 is the card below etc*/
const char *suit[4]  = { "Hearts", "Diamonds", "Clubs", "Spades"};
const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five",
	                     "Six", "Seven", "Eight", "Nine", "Ten",
						 "Jack", "Queen", "King" };

enum CARD { ACE, DEUCE, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
            NINE, TEN, JACK, QUEEN, KING
};


/* /////////////////////////////////////////////////// */
/* ///////////////// FUNCTIONS /////////////////////// */
/* /////////////////////////////////////////////////// */


int main()
{
	srand( time(0));
	int deck[4][13] = { {0} };	
	
	int playerHand[5], dealerHand[5];
	int playerHandRank[3] = {0};
	int dealerHandRank[3] = {0};


    /* Shuffle at start to initialise deck
	 * and when no cards left to deal */
	shuffle( deck );    
    
    printf("---- DEALER HAND ----\n");
    dealAHand( deck, dealerHand );  
    rankHand( deck, dealerHand , dealerHandRank ); 
    printHand( dealerHandRank ); 
    
    printf("\n---- PLAYER HAND ----\n");
    dealAHand( deck, playerHand  );
    rankHand( deck, playerHand , playerHandRank ); 
    printHand( playerHandRank ); 
    
    compareHands( dealerHand, playerHand, dealerHandRank, playerHandRank );
    
	return 0;
}


void compareHands( const int *dealerHand, const int *playerHand,
                   const int *dealerHandRank, const int *playerHandRank)
{
	int dRank0 = dealerHandRank[0];
	int pRank0 = playerHandRank[0];
	int dRank1 = dealerHandRank[1];
	int pRank1 = playerHandRank[1];
	
	/* First check if one player has a higher rank than the other */
	if( dRank0 < pRank0 )
	    printf("\nDEALER WINS\n");
	else if( pRank0 < dRank0 )
	    printf("\nPLAYER WINS\n");
	/* Next check if the player has a higher version of that rank */
	else if( dRank1==ACE && pRank1!=ACE )
	    printf("\nDEALER WINS\n");
	else if(pRank1==ACE && dRank1!=ACE )
	    printf("\nPLAYER WINS\n");
	else if( dRank1 > pRank1 )
	    printf("\nDEALER WINS\n");
	else if( pRank1 > dRank1 )
	    printf("\nPLAYER WINS\n");
	    
}



void dealAHand(const int wDeck[][13], int *wHand)
{
    int i;
	int playerHandRank[3] = {0};
	
	for(i=0; i<HANDSIZE; i++)
	    wHand[i] = dealACard();
	    
	sortHand(wDeck, wHand); 
	
	for(i=0; i<HANDSIZE; i++)
		printCardName(wDeck, wHand[i]);

    rankHand(wDeck, wHand, playerHandRank);
	
	
}



void rankHand(const int wDeck[][13], const int *hand, int *rank ) 
{
	int has4, hasFullHouse, hasStraight, hasFlush, 
	    has3, hasTwoPair, hasOnePair;
		
	hasStraight = isStraight(wDeck, hand);
	hasFlush = isFlush(wDeck, hand);
	
	/* Check for Royal Flush and Straight flush */
    if(hasStraight>=0 && hasFlush>=0) {
    	if(hasStraight==TEN)
    	    rank[0] = 1;
    	else
        	rank[0] = 2;
    	rank[1] = hasStraight;
    	return;
	}
	
    /* Check for Four of a Kind */
    if( (has4 = isFourOFAKind(wDeck, hand)) >= 0) {
    	rank[0] = 3;
    	rank[1] = has4;
    	return;
	}
    
    /* Check for Full House */
    if( (hasFullHouse = isFullHouse(wDeck, hand)) >= 0) {
    	rank[0] = 4;
    	rank[1] = hasFullHouse;
    	return;
	}
    
    /* Check for Straight */
    if(hasStraight >= 0) {
    	rank[0] = 5;
    	rank[1] = hasStraight;
    	return;
	}
    
    /* Check for Flush */
    if(hasFlush >= 0) {
    	rank[0] = 6;
    	rank[1] = hasFlush;
    	return;
	}
    
    /* Check for Three of a Kind */
    if( (has3 = isThreeOFAKind(wDeck, hand)) >= 0) {
    	rank[0] = 7;
    	rank[1] = has3;
    	return;
	}
	
	/* Check for Two Pair */
    if( (hasTwoPair = isTwoPair(wDeck, hand)) >= 0) {
    	rank[0] = 8;
    	rank[1] = hasTwoPair;
    	return;
	}
	
    /* Check for a Pair */
    if( (hasOnePair = isOnePair(wDeck, hand)) >= 0) {
    	rank[0] = 9;
    	rank[1] = hasOnePair;
    	return;
	}
	
	/* Otherwise player only has a High Card */
	rank[0] = 10;
	rank[1] = getHighCard(wDeck, hand);
	return;
}


/* Add all of the cards to a random position in the deck */
void shuffle( int wDeck[][13] )
{
	/* After shuffling the deck is full again */
	deckPosition = 1;
	
	int row, column, card;
	
	for( card=1; card<=52; card++)
	{
		do {
			row = rand()%4;
			column = rand()%13;
		} while( wDeck[row][column]!=0 );
		
		wDeck[row][column] = card; 	
	}
}


/* Return a card position in the deck */
int dealACard( void )
{
	int card = deckPosition;
	deckPosition++;
	return card;
}


void printHand(int *handRank) 
{
	switch(handRank[0]) 
	{
		case 1:
			printf("\nPlayer has a Royal Flush\n" );
			break;
		case 2:
			printf("\nPlayer has a Straight Flush\n" );
			break;
		case 3:
			printf("\nPlayer has Four %ss\n", face[ handRank[1] ] );
			break;
		case 4:
			printf("\nPlayer has a Full House\n" );
			break;
		case 5:
			printf("\nPlayer has a Straight\n" );
			break;
		case 6:
			printf("\nPlayer has a %s high Flush\n", face[ handRank[1]] );
			break;
		case 7:
			printf("\nPlayer has Three %ss\n", face[ handRank[1]] );
			break;
		case 8:
			printf("\nPlayer has Two Pairs\n" );
			break;
		case 9:
			printf("\nPlayer has a Pair of %ss\n", face[ handRank[1]] );
			break;
		default:
			printf("\nPlayer has %s high\n", face[ handRank[1]] );
			break;
	}	
}


void printCardName( const int wDeck[][13], int cardPosition)
{
	int row, column;
	
	for(row=0; row<=3; row++) {
		for(column=0; column<=12; column++)	{
			if(wDeck[row][column]==cardPosition) {
				printf( "%5s of %-8s\n", face[ column ], suit[ row ]);
				return;
			}
		}
	}

	printf( "CARD NOT FOUND!!!!\n");
}


/* Sort hand based upon the face values of its cards */
void sortHand( const int wDeck[][13], int *hand)
{
	int pass, card, temp;
	
	/* Sort hand based upon face value*/
	for(pass=0; pass<HANDSIZE; pass++) 
	{
		for(card=0; card<HANDSIZE-1; card++)
		{
			if( getCardFace( wDeck, hand[card]) > getCardFace( wDeck, hand[card + 1]) )
			{
				temp = hand[card];
				hand[card]=hand[card+1];
				hand[card+1]=temp;
			}			
		}
	}
}


/* Return the face value of the card */
int getCardFace( const int wDeck[][13], int cardPosition)
{
	int suit, face;
	
	for(suit=0; suit<=3; suit++) {
		for(face=0; face<=12; face++) {
			if(wDeck[suit][face]==cardPosition)
				return face;
		}
	}
    
    return -1;
}


/* Return the suit of the card */
int getCardSuit( const int wDeck[][13], int cardPosition)
{
	int suit, face;
	
	for(suit=0; suit<=3; suit++) {
		for(face=0; face<=12; face++) {
			if(wDeck[suit][face]==cardPosition)
				return suit;
		}
	}
    
    return -1;
}


/* Returns the face of the card if there are four of them
 * otherwise returns -1 */
int isFourOFAKind( const int wDeck[][13], const int *hand)
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int hasFourOfKind = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			if(++count==4)
				hasFourOfKind = card;
		}
		else
			count=1;
		
		prevCard = card;
	}

    return hasFourOfKind;
}


/* Returns the face of the card if there are three of them
 * otherwise returns -1 */
int isThreeOFAKind( const int wDeck[][13], const int *hand)
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int hasThreeOfKind = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			if(++count==3)
				hasThreeOfKind = card;
		}
		else
			count=1;
		
		prevCard = card;
	}

    return hasThreeOfKind;
}


/* Returns the face of the high card if hand is a flush
 * otherwise returns -1 */
int isFlush( const int wDeck[][13], const int *hand)
{
	int i, card;
	int suit = getCardSuit(wDeck, hand[0]);
	int isFlush=getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardSuit(wDeck, hand[i]);
		
		if(card!=suit) 
		{
			return -1;
		}
		else if(isFlush!=ACE) {
			isFlush = getCardFace(wDeck, hand[i]);
		} 
	}

    return isFlush;
}


/* Returns the face of the low card if hand is a straight
 * otherwise returns -1 */
int isStraight( const int wDeck[][13], const int *hand)
{
	int i, card;
	int prevFace = getCardFace(wDeck, hand[0]);
	int hasStraight = prevFace;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		if(hasStraight==ACE && i==1) 
		{
			/* Note ACE is high or low */
			if(card!=DEUCE && card!=TEN) {
		        return -1;		
			}
			else if(card==TEN)
			    hasStraight=9;
		}
		else if(card != prevFace+1)
		{
	        return -1;
		}
		
		prevFace = card;

	}

    return hasStraight;
}


/* Returns the face of the card if there are three of them
 * otherwise returns -1 */
int isFullHouse( const int wDeck[][13], const int *hand)
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int hasThreeOfKind = -1;
	int hasPair = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			if(++count==2) {
				hasPair = 1;
			}
			if(count==3) {
				hasThreeOfKind = card;
				hasPair = -1;
			}	
		}
		else
			count=1;
		
		prevCard = card;
	}
	
    if(hasPair>=0 && hasThreeOfKind>=0)
        return hasThreeOfKind;
    else
        return -1;
}


/* Returns the face of the card of the highest pair if there are two
 * otherwise returns -1 */
int isTwoPair( const int wDeck[][13], const int *hand)
{
	int i, card;
	int prevCard = getCardFace(wDeck, hand[0]);
	int pairs = 0;
	int hasPair = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) {
			pairs++;
				
			if( hasPair!=ACE && card>hasPair) 
				hasPair = card;	
		}
		
		prevCard = card;
	}
	
    if(pairs == 2)
        return hasPair;
    else
        return -1;
}


/* Returns the face of the card of the pair
 * otherwise returns -1 */
int isOnePair( const int wDeck[][13], const int *hand)
{
	int i, card;
	int prevCard = getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard)
			return card;	
		
		prevCard = card;
	}
	
    return -1;
}


/* Return the face value of the highest card */
int getHighCard( const int wDeck[][13], const int *hand)
{
    if(getCardFace(wDeck, hand[0]) == ACE )
        return ACE;
    else
        return getCardFace(wDeck, hand[ HANDSIZE-1]);
}

