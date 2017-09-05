/*
 * Filename:	ex07_13.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        28/05/2017.
 * Description: Deal and check a poker hand
 *
 * TODO - Implement the draw more cards
 *        Implement the Ascii graphics
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DeckOfCards.h"

#define HANDSIZE 5

/* /////////////////////////////////////////////////// */
/* //////////////// PROTOTYPES /////////////////////// */
/* /////////////////////////////////////////////////// */

void playAGame( const int [][13]);
void dealerDiscards( const int [][13], int *, int * );

void compareHands( const int [][13], const int *, const int *, 
                  const int *, const int * );
void dealAHand( const int [][13], int * );
void rankHand( const int [][13], const int *, int * );
void shuffle( int [][13]);
int dealACard( void );

void printHand( const int wDeck[][13], const int *hand);
void printHandRank(int * );
void printCardName( const int [][13], int );
void sortHand( const int [][13], int * );
int getCardFace( const int [][13], int );
int getCardSuit( const int [][13], int );

int isFourOFAKind( const int [][13], const int *, int * );
int isFullHouse( const int [][13], const int *, int * );

int isFlush( const int [][13], const int * );
int isStraight( const int [][13], const int * );
int isThreeOFAKind( const int [][13], const int *, int * );
int isTwoPair( const int [][13], const int *, int * );
int isOnePair( const int [][13], const int *, int * );
void getHighCard( const int [][13], const int *, int * );

int isFourFlush( const int [][13], const int * );
int isOutsideStraight( const int [][13], const int * );


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

enum HANDRANKINGS {
    ROYALFLUSH=1, STRAIGHTFLUSH=2, FOUROFAKIND=3, FULLHOUSE=4,
	STRAIGHT=5, FLUSH=6, THREEOFAKIND=7, TWOPAIRS=8, ONEPAIR=9, HIGHCARD=10
};


/* /////////////////////////////////////////////////// */
/* ///////////////// FUNCTIONS /////////////////////// */
/* /////////////////////////////////////////////////// */


int main()
{
	srand( time(0));
	int deck[4][13] = { {0} };	
	
    /* Shuffle at start to initialise deck
	 * and when no cards left to deal */
	shuffle( deck );  
	
	playAGame(deck);
    
	return 0;
}


void playAGame( const int deck[][13])
{	
	int playerHand[HANDSIZE], dealerHand[HANDSIZE];
	int playerHandRank[3] = {0};
	int dealerHandRank[3] = {0};
	
	// int result;

    
    printf("---- DEALER HAND ----\n");
    dealAHand( deck, dealerHand );  
    rankHand( deck, dealerHand , dealerHandRank ); 
    
    /* Print out the hand and rank*/
	printHand(deck, dealerHand);
    printHandRank( dealerHandRank );
    
    
    printf("\n---- PLAYER HAND ----\n");
    dealAHand( deck, playerHand  );
    rankHand( deck, playerHand , playerHandRank ); 

    /* Print out player's hand and rank*/
	printHand(deck, playerHand);
    printHandRank( playerHandRank ); 
    
    system("pause");
    system("cls");    
    dealerDiscards( deck, dealerHand , dealerHandRank ); 
    rankHand( deck, dealerHand , dealerHandRank );
    
    /* Print out dealer's hand and rank*/
    printf("---- DEALER HAND ----\n");
	printHand(deck, dealerHand);
    printHandRank( dealerHandRank ); 
    

    /* Print out player's hand and rank*/
    printf("\n---- PLAYER HAND ----\n");
	printHand(deck, playerHand);
    printHandRank( playerHandRank ); 
    
    
    compareHands( deck, dealerHand, playerHand, 
	              dealerHandRank, playerHandRank );	
}



void dealerDiscards( const int wDeck[][13], int *dealerHand, int *dealerHandRank )
{
	int i, card, toDiscard=0;
	int bluff1 = rand()%10000;
	int bluff2 = rand()%1000;
	int bluff3 = rand()%100;
	
	int dealerToDiscard[HANDSIZE] = {0};
	
	/* Strategy is to stand on flush or higher */
	if(dealerHandRank[0] <= FLUSH) {
		//printf("\nDealer stands on these cards!\n");
	}
	/* Strategy is to keep trips */
	else if(dealerHandRank[0] == THREEOFAKIND ) {
		//printf("\nDealer draws to 3 of a kind!\n");
		
		for(i=0; i<HANDSIZE; i++) {
			if( getCardFace(wDeck, dealerHand[i]) != dealerHandRank[1]) {
				dealerToDiscard[i]=1;
				toDiscard++;
			}    
		}
	}
	/* Strategy is to keep the high pair with a 60% chance of discarding
	 * the low pair if it is below 8s */
	else if(dealerHandRank[0] == TWOPAIRS ) 
	{
		int highPair = dealerHandRank[1];
		int lowPair = dealerHandRank[2];
		
		//printf("\nDealer draws to 2 Pairs!\n");
		for(i=0; i<HANDSIZE; i++) 
		{
			card = getCardFace(wDeck, dealerHand[i]);
			if( card != highPair )
		    {
		    	/* 60% chance of discarding low pair */
		    	if(card==lowPair && bluff3<60) {
		    		if( lowPair < EIGHT ) {
		    			dealerToDiscard[i]=1;
		    			toDiscard++;
					}  	
				}
				else if(card!=lowPair) {
					dealerToDiscard[i]=1;
					toDiscard++;
				}     
			}		    
		}
	}
	/* Strategy is to keep pair */
	else if(dealerHandRank[0] == ONEPAIR ) 
	{
		//printf("\nDealer draws to 1 Pair!\n");
		int suit = isFourFlush(wDeck, dealerHand);
		int pair = dealerHandRank[1];
		
		/* if pair is less than ten and dealer has a
		 * four flush draw to the four flush*/
		if( (pair<TEN && pair!=ACE) && suit!=-1) 
		{
			for(i=0; i<HANDSIZE; i++) 
			{
				card = getCardSuit(wDeck, dealerHand[i]);
				if( card != suit ) {
					dealerToDiscard[i]=1;
					toDiscard++;
				}	    
			}
		}
		/* Otherwise keep pair */
		else {
			for(i=0; i<HANDSIZE; i++) {
				if( getCardFace(wDeck, dealerHand[i]) != dealerHandRank[1]) {
					dealerToDiscard[i]=1;
					toDiscard++;
				}	    
			}			
		}

	}
	/* High card strategy keep four flushes, Queen and above */
	else 
	{
		//printf("\nDealer draws to a high card!\n");
		
		/* First check if dealer has a fourflush or an outside straight */
		int suit = isFourFlush(wDeck, dealerHand);
		int outsideStraight = isOutsideStraight(wDeck, dealerHand); 
		if(suit!=-1) 
		{
			for(i=0; i<HANDSIZE; i++) {
				card = getCardSuit(wDeck, dealerHand[i]);
				if( card != suit ) {
					dealerToDiscard[i]=1;
					toDiscard++;
				}	    
			}
		}
		else if(outsideStraight!=-1) {
			dealerToDiscard[outsideStraight]=1;
			toDiscard++;
		}
		/* Otherwise keep Queen and above */
		else 
		{
			for(i=0; i<HANDSIZE; i++) {
				card = getCardFace(wDeck, dealerHand[i]);
				if( card<QUEEN && card!=ACE ) {
					dealerToDiscard[i]=1;
					toDiscard++;
				}	    
			}			
		}
	}
	
//	printf("Dealer to discard = ");
//	for(i=0; i<HANDSIZE; i++) {
//		printf("%d ", dealerToDiscard[i]);
//	}		
//	printf("\n");	
	
	if(toDiscard==1)
	    printf("Dealer draws 1 card!\n\n");
	else
    	printf("Dealer draws %d cards!\n\n", toDiscard);
    	
    /* discard and draw cards */
	for(i=0; i<HANDSIZE; i++)
	    if(dealerToDiscard[i]==1)
    	    dealerHand[i] = dealACard();
	    
	sortHand(wDeck, dealerHand); 
    rankHand(wDeck, dealerHand, dealerHandRank);
}


void compareHands( const int wDeck[][13], 
                   const int *dealerHand, const int *playerHand,
                   const int *dealerHandRank, const int *playerHandRank)
{
	int i, dealerCard, playerCard;
	
	int dRank0 = dealerHandRank[0];
	int pRank0 = playerHandRank[0];
	int dRank1 = dealerHandRank[1];
	int pRank1 = playerHandRank[1];
	int dRank2 = dealerHandRank[2];
	int pRank2 = playerHandRank[2];
	
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
	else if(dRank0==TWOPAIRS && dRank2!=pRank2 ) 
	{
		if(dRank2 > pRank2)
		    printf("\nDEALER WINS\n");
		else
		    printf("\nPlayer WINS\n");
	}
	else if(dealerHand[0]==ACE && playerHand[0]!=ACE)
	    printf("\nDEALER WINS\n");
	else if(playerHand[0]==ACE && dealerHand[0]!=ACE)
	    printf("\nPLAYER WINS\n"); 
	else {
		for(i=HANDSIZE-1; i>=0; i--) 
		{
			dealerCard = getCardFace(wDeck, dealerHand[i]);
			playerCard = getCardFace(wDeck, playerHand[i]);
			if( dealerCard > playerCard ) {
				printf("\nDEALER WINS\n");
				return;
			} 
	        else if( playerCard > dealerCard ) {
	        	printf("\nPLAYER WINS\n");
	        	return;
			}    
		}
		
		printf("\nNOBODY WINS - THE HANDS ARE EQUAL\n");
	    return;
	}
}


void dealAHand(const int wDeck[][13], int *hand)
{
    int i;
	int playerHandRank[3] = {0};
	
	for(i=0; i<HANDSIZE; i++)
	    hand[i] = dealACard();
	    
	sortHand(wDeck, hand); 
    rankHand(wDeck, hand, playerHandRank);
}



void rankHand(const int wDeck[][13], const int *hand, int *rank ) 
{
	int hasStraight, hasFlush;
		
	hasStraight = isStraight(wDeck, hand);
	hasFlush = isFlush(wDeck, hand);
	
	/* Check for Royal Flush and Straight flush */
    if(hasStraight>=0 && hasFlush>=0) {
    	if(hasStraight==TEN)
    	    rank[0] = ROYALFLUSH;
    	else
        	rank[0] = STRAIGHTFLUSH;
    	rank[1] = hasStraight;
    	return;
	}
	
    /* Check for Four of a Kind */
    if( isFourOFAKind(wDeck, hand, rank) == 1)
    	return;
    
    /* Check for Full House */
    if(isFullHouse(wDeck, hand, rank) == 1)
    	return;
    
    /* Check for Straight */
    if(hasStraight >= 0) {
    	rank[0] = STRAIGHT;
    	rank[1] = hasStraight;
    	return;
	}
    
    /* Check for Flush */
    if(hasFlush >= 0) {
    	rank[0] = FLUSH;
    	rank[1] = hasFlush;
    	return;
	}
    
    /* Check for Three of a Kind */
    if( isThreeOFAKind(wDeck, hand, rank) == 1)
    	return;
	
	/* Check for Two Pair */
    if( isTwoPair(wDeck, hand, rank) == 1)
    	return;
	
    /* Check for a Pair */
    if(isOnePair(wDeck, hand, rank) == 1)
    	return;
	
	/* Otherwise player only has a High Card */
	getHighCard(wDeck, hand, rank);
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


/* Print out the players hand */
void printHand( const int wDeck[][13], const int *hand)
{
	int i;
//    /* Print out the hand*/
//	for(i=0; i<HANDSIZE; i++)
//		printCardName(wDeck, hand[i]);
		
	/* Get the suits and faces from the players hand */
    int suits[HANDSIZE], faces[HANDSIZE];
	for(i=0; i<HANDSIZE; i++) {
		suits[i] = getCardSuit(wDeck, hand[i]);
		faces[i] = getCardFace(wDeck, hand[i]);  
	}

    int lines=9, characters=12;
    int cards, j;
	
	for(i=0; i<lines; i++) 
	{
		/* Print out a line for each card in the hand */
		for(cards=0; cards<HANDSIZE; cards++)
		{
			for(j=0; j<characters; j++)
	    	    printf("%c",DECKPICS[ suits[cards] ][ faces[cards] ][ i ][ j ]);
		}
	    	
	    printf("\n");
	}   
	  
}

/* Prints out the rank of the hand */
void printHandRank( int *handRank) 
{
	switch(handRank[0]) 
	{
		case ROYALFLUSH:
			printf("Player has a Royal Flush\n" );
			break;
		case STRAIGHTFLUSH:
			printf("Player has a Straight Flush\n" );
			break;
		case FOUROFAKIND:
			printf("Player has Four %ss\n", face[ handRank[1] ] );
			break;
		case FULLHOUSE:
			printf("Player has a Full House - %ss and %ss\n", 
			        face[ handRank[1]] , face[ handRank[2]] );
			break;
		case STRAIGHT:
			printf("Player has a Straight\n" );
			break;
		case FLUSH:
			printf("Player has a %s high Flush\n", face[ handRank[1]] );
			break;
		case THREEOFAKIND:
			printf("Player has Three %ss\n", face[ handRank[1]] );
			break;
		case TWOPAIRS:
			printf("Player has Two Pairs - %ss and %ss\n", 
			        face[ handRank[1]] , face[ handRank[2]] );
			break;
		case ONEPAIR:
			printf("Player has a Pair of %ss\n", face[ handRank[1]] );
			break;
		default:
			printf("Player has %s high\n", face[ handRank[1]] );
			break;
	}	
}


/* Prints the name of the card at the position passed */
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


/* Return the face value of the card at the position passed */
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


/* Return the suit of the card at the position passed */
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


/* If hand is Four of a kind it sets rank[0] to 3 and 
 * rank[1] to the face value of the four of a kind then returns 1,
 * otherwise returns -1 */
int isFourOFAKind( const int wDeck[][13], const int *hand, int *rank)
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	int hasFourOfKind = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			if(++count==4) {
				rank[0] = FOUROFAKIND;
    	        rank[1] = card;
    	        return 1;
			}
		}
		else
			count=1;
		
		prevCard = card;
	}

    return hasFourOfKind;
}


/* If hand is Three of a kind it sets rank[0] to 7 and 
 * rank[1] to the face value of the three of a kind then returns 1,
 * otherwise returns -1 */
int isThreeOFAKind( const int wDeck[][13], const int *hand, int *rank)
{
	int i, card, count=1;
	int prevCard = getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) 
		{
			if(++count==3) {
				rank[0] = THREEOFAKIND;
    	        rank[1] = card;
    	        return 1;
			}
		}
		else
			count=1;
		
		prevCard = card;
	}

    return -1;
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


/* If hand is Full House it sets rank[0] to 4 and 
 * rank[1] to the face value of the three of a kind, and rank[2] 
 * to the value of the pair then returns 1,
 * otherwise returns -1 */
int isFullHouse( const int wDeck[][13], const int *hand, int *rank)
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
				hasPair = card;
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
	
    if(hasPair>=0 && hasThreeOfKind>=0) {
    	rank[0] = FULLHOUSE;
    	rank[1] = hasThreeOfKind;
    	rank[2] = hasPair;
    	return 1;
	} 
    else
        return -1;
}


/* If hand is Two it sets rank[0] to 8, rank[1] to the face value 
 * of the high pair, and rank[2] to the fgace value of th elow pair
 * then returns 1, otherwise returns -1 */
int isTwoPair( const int wDeck[][13], const int *hand, int *rank)
{
	int i, card;
	int prevCard = getCardFace(wDeck, hand[0]);
	int pairs = 0;
	int highPair = -1;
	int lowPair = -1;
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) {
			pairs++;
			
			if(pairs==1)
			    highPair = card;
			
			else if( highPair!=ACE && card>highPair) {
				lowPair = highPair;
				highPair = card;
			}
			else
			    lowPair = card;
		}
		
		prevCard = card;
	}
	
    if(pairs == 2) {
    	rank[0] = TWOPAIRS;
    	rank[1] = highPair;
    	rank[2] = lowPair;
    	return 1;
	}
    else
        return -1;
}


/* If hand is a pair it sets rank[0] to 9 and 
 * rank[1] to the face value of the pair then returns 1,
 * otherwise returns -1 */
int isOnePair( const int wDeck[][13], const int *hand, int *rank)
{
	int i, card;
	int prevCard = getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) {
	    	rank[0] = ONEPAIR;
	    	rank[1] = card;
	    	return 1;			
		}	
		
		prevCard = card;
	}
	
    return -1;
}


/* Sets rank[0] to 10 and rank[1] to the face value of the highest card */
void getHighCard( const int wDeck[][13], const int *hand, int *rank)
{
    rank[0] = HIGHCARD;

    if(getCardFace(wDeck, hand[0]) == ACE )
        rank[1] = ACE;
    else
        rank[1] = getCardFace(wDeck, hand[HANDSIZE-1]); 
}


/* Returns the suit if hand has a four flush
 * otherwise returns -1 */
int isFourFlush( const int wDeck[][13], const int *hand)
{
	int i;
	//suit[4]  = { "Hearts", "Diamonds", "Clubs", "Spades"};
	int suit[4] = {0};
	
	/* Count the number of each suit*/
	for(i=0; i<HANDSIZE; i++) 
	{
		++suit[getCardSuit(wDeck, hand[i])];
	}

    /* Return a suit if it has 4 in the hand */
    for(i=0; i<4; i++) {
    	if(suit[i]==4) {
    		//printf("Has a FourFlush\n");
    		return i;
		}
	}
	/* Otherwise no four flush */
    return -1;
}


/* Returns the position of the card to discard to go for an 
 * outside straight, otherwise returns -1 */
int isOutsideStraight( const int wDeck[][13], const int *hand)
{
	int i, card, count=1;
	int prevFace = getCardFace(wDeck, hand[0]);
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		/* Check for runs with ACES */
		if( (i==1 || i==2) && prevFace==ACE ) 
		{
			/* Note ACE is high or low */
			if(card!=DEUCE && card!=JACK)
			    count=1;	
			else
			    count++;;
		}
		/* Check for runs with Non-ACES */
		else if(card != prevFace+1)
		{
			if(i==1)
			    count=1;
		    /* Never draw to an inside straight */
		    else if(i!=1 && i!=HANDSIZE-1)
 	            return -1;
			/* If the last card is outside of the run and the previous
			 * cards have ran correctly */
			else if(i==HANDSIZE-1 && count==HANDSIZE-1) {
				//printf("Has an Outside Straight\n");
				return HANDSIZE-1;
			}
		}
		else
		    count++;
		
		prevFace = card;
	}
	
	if(count==HANDSIZE-1) {
		//printf("Has an Outside Straight\n");
		return 0;
	}
	    
	else
	    return -1;
}

