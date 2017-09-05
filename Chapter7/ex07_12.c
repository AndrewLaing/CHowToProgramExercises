/*
 * Filename:	ex07_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/05/2017.
 * Description: Deal and check a poker hand
 *
 * TODO - replace arrays passed to functions with pointers
 *        using const where neccessary ie read only
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HANDSIZE 5


int dealAHand( void );
void rankHand( const int [][13], int [], int [] );
void shuffle( int [][13]);
int dealACard( void );

void printCardName( const int [][13], int );
void sortHand( const int [][13], int []);
int getCardFace( const int [][13], int );
int getCardSuit( const int [][13], int );

int isFourOFAKind( const int [][13], int []);
int isThreeOFAKind( const int [][13], int []);
int isFlush( const int [][13], int []);
int isStraight( const int [][13], int []);
int isFullHouse( const int [][13], int []);
int isTwoPair( const int [][13], int []);
int isOnePair( const int [][13], int []);
int getHighCard( const int [][13], int []);


/* GLOBAL VARIABLES FOR THE DECK TO USE */
/* 0 is the top card. 1 is the card below etc*/
int deckPosition = 1;
const char *suit[4]  = { "Hearts", "Diamonds", "Clubs", "Spades"};
const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five",
	                     "Six", "Seven", "Eight", "Nine", "Ten",
						 "Jack", "Queen", "King" };

enum CARD { ACE, DEUCE, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
            NINE, TEN, JACK, QUEEN, KING
};



int main()
{
	srand( time(0));
	
//    while(deckPosition < 45)
//        if(dealAHand()==1)
//            break;
    
    dealAHand();
    
	return 0;
}


int dealAHand()
{
	int producedHand = 0;
	
	int deck[4][13] = { {0} };
    int i, playerHand[5];
	int playerHandRank[3] = {0};

    
	shuffle( deck );
	
	for(i=0; i<HANDSIZE; i++)
	    playerHand[i] = dealACard();
	    
	sortHand(deck, playerHand); 
	
	for(i=0; i<HANDSIZE; i++) {
		printCardName(deck, playerHand[i]);
		//printf("---- %d ---- \n", getCardFace(deck, playerHand[i] ) );
	}

    rankHand(deck, playerHand, playerHandRank);
	
	switch(playerHandRank[0]) 
	{
		case 1:
			printf("\nPlayer has a Royal Flush\n" );
			break;
		case 2:
			printf("\nPlayer has a Straight Flush\n" );
			break;
		case 3:
			printf("\nPlayer has Four %ss\n", face[ playerHandRank[1] ] );
			break;
		case 4:
			printf("\nPlayer has a Full House\n" );
			break;
		case 5:
			printf("\nPlayer has a Straight\n" );
			break;
		case 6:
			printf("\nPlayer has a %s high Flush\n", face[ playerHandRank[1]] );
			break;
		case 7:
			printf("\nPlayer has Three %ss\n", face[ playerHandRank[1]] );
			break;
		case 8:
			printf("\nPlayer has Two Pairs\n" );
			break;
		case 9:
			printf("\nPlayer has a Pair of %ss\n", face[ playerHandRank[1]] );
			break;
		default:
			printf("\nPlayer has %s high\n", face[ playerHandRank[1]] );
			break;
	}	
	
	return producedHand;	
}



void rankHand(const int wDeck[][13], int hand[], int rank[] ) 
{
	int has4, hasFullHouse, hasStraight, hasFlush, 
	    has3, hasTwoPair, hasOnePair;
	
	
	hasStraight = isStraight(wDeck, hand);
	hasFlush = isFlush(wDeck, hand);
	
    if(hasStraight>=0 && hasFlush>=0) {
    	/* Check for royal flush first otherwise hand
		 * is a straight flush */ 
    	if(hasStraight==TEN)
    	    rank[0] = 1;
    	else
        	rank[0] = 2;
    	rank[1] = hasStraight;
    	return;
	}
	
	
	has4 = isFourOFAKind(wDeck, hand);
    if(has4 >= 0) {
    	rank[0] = 3;
    	rank[1] = has4;
    	return;
	}
    

    hasFullHouse = isFullHouse(wDeck, hand);
    if(hasFullHouse >= 0) {
    	rank[0] = 4;
    	rank[1] = hasFullHouse;
    	return;
	}
    
    
    if(hasStraight >= 0) {
    	rank[0] = 5;
    	rank[1] = hasStraight;
    	return;
	}
    
    
    if(hasFlush >= 0) {
    	rank[0] = 6;
    	rank[1] = hasFlush;
    	return;
	}
    
    
    has3 = isThreeOFAKind(wDeck, hand);
    if(has3 >= 0) {
    	rank[0] = 7;
    	rank[1] = has3;
    	return;
	}
	
	
	hasTwoPair = isTwoPair(wDeck, hand);
    if(hasTwoPair >= 0) {
    	rank[0] = 8;
    	rank[1] = hasTwoPair;
    	return;
	}
	
	
	hasOnePair = isOnePair(wDeck, hand);
    if(hasOnePair >= 0) {
    	rank[0] = 9;
    	rank[1] = hasOnePair;
    	return;
	}
	
	/* Otherwise player has a high card */
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


void printCardName( const int wDeck[][13], int cardPosition)
{
	int row, column, foundCard=0;
	
	for(row=0; row<=3; row++)
	{
		for(column=0; column<=12; column++)
		{
			if(wDeck[row][column]==cardPosition) {
				printf( "%5s of %-8s\n",
				face[ column ], suit[ row ]);
				
				foundCard = 1;
				break;
			}
			if(foundCard)
			    break;
		}
	}

}


/* Sort hand based upon the face values of its cards */
void sortHand( const int wDeck[][13], int hand[])
{
	int pass, j, temp;
	
	/* Sort hand based upon face value*/
	for(pass=0; pass<HANDSIZE; pass++) 
	{
		for(j=0; j<HANDSIZE-1; j++)
		{
			if( getCardFace( wDeck, hand[j]) > getCardFace( wDeck, hand[j + 1]) )
			{
				temp = hand[j];
				hand[j]=hand[j+1];
				hand[j+1]=temp;
			}			
		}
	}
}


/* Return the face value of the card */
int getCardFace( const int wDeck[][13], int cardPosition)
{
	int row, column, foundCard=0;
	int face = 0;
	
	for(row=0; row<=3; row++)
	{
		for(column=0; column<=12; column++)
		{
			if(wDeck[row][column]==cardPosition) {
				foundCard = 1;
				face = column;
				break;
			}
			if(foundCard)
			    break;
		}
	}
    
    return face;
}


/* Return the suit of the card */
int getCardSuit( const int wDeck[][13], int cardPosition)
{
	int row, column, foundCard=0;
	int suit = 0;
	
	for(row=0; row<=3; row++)
	{
		for(column=0; column<=12; column++)
		{
			if(wDeck[row][column]==cardPosition) {
				foundCard = 1;
				suit = row;
				break;
			}
			if(foundCard)
			    break;
		}
	}
    
    return suit;
}


/* Returns the face of the card if there are four of them
 * otherwise returns -1 */
int isFourOFAKind( const int wDeck[][13], int hand[])
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int hasFourOfKind = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			count++;
			if(count==4)
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
int isThreeOFAKind( const int wDeck[][13], int hand[])
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int hasThreeOfKind = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			count++;
			if(count==3)
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
int isFlush( const int wDeck[][13], int hand[])
{
	int i, card;
	int suit = getCardSuit(wDeck, hand[0]);
	int isFlush=getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardSuit(wDeck, hand[i]);
		
		if(card!=suit) 
		{
			isFlush=-1;
			break;
		}
		else if(isFlush!=0) {
			isFlush = getCardFace(wDeck, hand[i]);
		} 
	}

    return isFlush;
}


/* Returns the face of the low card if hand is a straight
 * otherwise returns -1 */
int isStraight( const int wDeck[][13], int hand[])
{
	int i, card;
	int prevFace = getCardFace(wDeck, hand[0]);
	int hasStraight = prevFace;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		if(hasStraight==ACE && i==1) 
		{
			/* Note ACE=0, 2=1, 3=2 etc*/
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
int isFullHouse( const int wDeck[][13], int hand[])
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
			count++;
			if(count==2) {
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
int isTwoPair( const int wDeck[][13], int hand[])
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int pairs = 0;
	int hasPair = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) {
			count++;
			if(count==2) {
				pairs++;
				
				if(card > hasPair) 
					hasPair = card;
			}	
		}
		else
			count=1;
		
		prevCard = card;
	}
	
    if(pairs == 2)
        return hasPair;
    else
        return -1;
}


/* Returns the face of the card of the pair
 * otherwise returns -1 */
int isOnePair( const int wDeck[][13], int hand[])
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) {
			count++;
			if(count==2) {
				return card;
			}	
		}
		else
			count=1;
		
		prevCard = card;
	}
	
    return -1;
}


/* Return the face value of the highest card */
int getHighCard( const int wDeck[][13], int hand[])
{
    if(getCardFace(wDeck, hand[0]) == ACE )
        return ACE;
    else
        return getCardFace(wDeck, hand[ HANDSIZE-1]);
}
