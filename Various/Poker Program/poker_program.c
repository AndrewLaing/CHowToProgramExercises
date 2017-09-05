/*
 * Filename:	poker_program.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/06/2017.
 * Description: Deal and check a poker hand
 *
 * TODO - Add a start menu with intro and options
 *        As always factor the code
 *        As some randomness to dealerDiscards to add strategy
 *        Add a betting feature
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DeckOfCards.h"

#define HANDSIZE 5
#define CLEARSCREEN system("cls")
#define PAUSE system("pause")

/* /////////////////////////////////////////////////// */
/* //////////////// PROTOTYPES /////////////////////// */
/* /////////////////////////////////////////////////// */

int getLine( char [], int );
int getRandomNumber( int );
int playAGame( const int [][13]);
void dealerDiscards( const int [][13], int *, int * );
void playerDiscards( const int [][13], int *, int * );

int compareHands( const int [][13], const int *, const int *, 
                  const int *, const int * );
void dealAHand( const int [][13], int * );
void rankHand( const int [][13], const int *, int * );
void reinitialiseDeck( int [][13] );
void shuffle( int [][13]);
int dealACard( void );

void printBackOfHand( void );
void printHand( const int wDeck[][13], const int *hand);
void printHandRank(int * );
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


const char *LOGO = 
"\n\n   '|.   '|'             .|'''.|    .           '||\n"                 
"    |'|   |    ...       ||..  '  .||.   ....    ||  ..    ....   ....\n"  
"    | '|. |  .|  '|.      ''|||.   ||   '' .||   || .'   .|...|| ||. '\n"
"    |   |||  ||   ||   .      '||  ||   .|' ||   ||'|.   ||      . '|..\n"
"   .|.   '|   '|..|'    |'....|'   '|.' '|..'|' .||. ||.  '|...' |'..|'\n\n"
"'||''|.          '||                        .|''.|    .||    /|| .|''''.||\n"
" ||   ||   ...    ||  ..    ....  ... ..   '|   ./  .|''''|. .||      .//\n"
" ||...|' .|  '|.  || .'   .|...||  ||' ''     .//  .||   .|| .||     .//\n" 
" ||      ||   ||  ||'|.   ||       ||        .//   .||   .|| .||    .//\n"
".||.      '|..|' .||. ||.  '|...' .||.     .|'''''|  .|''|  .|''|  .||\n\n\n\n\t\t\t";



/* /////////////////////////////////////////////////// */
/* ///////////////// FUNCTIONS /////////////////////// */
/* /////////////////////////////////////////////////// */


int main()
{
	srand( time(0));
	
	int dealerWins=0, playerWins=0, draws=0;
	int winner;
	char playAgain = 'y';	
	int maxInput = 10;	
	
	int deck[4][13] = { {0} };
	char input[maxInput];
	
	
    /* Print the game logo */
    CLEARSCREEN;
	printf("%s", LOGO);
	PAUSE;
	//system("pause");
	
    /* Shuffle at start to initialise deck
	 * and when no cards left to deal */
	while(playAgain=='y' || playAgain=='Y') 
	{
		//system("cls");
		CLEARSCREEN;
		reinitialiseDeck( deck );
		shuffle( deck );  

		winner = playAGame( deck );
		
		if(winner==1)
		    dealerWins++;
		else if(winner==2)
		    playerWins++;
		else
		    draws++;

        PAUSE;
		//system("pause");
		CLEARSCREEN;
		//system("cls");
		printf("---- STATS ----\n\n");
		printf("Dealer wins = %d\n", dealerWins);
		printf("Player wins = %d\n", playerWins);
		printf("Draws       = %d\n\n", draws);
		
		printf("Would you like to play again (yes/no)?: ");
		getLine(input, maxInput);
		
		if(input[0]=='\n')
		    playAgain = 'y';
		else
    		playAgain = input[0];
	}

	return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
	int c, i=0;
	
	while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
	    s[i++]=c;

	if(c=='\n')
	    s[i++]=c;
	s[i] = '\0';
	
	/* Clear any overflow*/
	fflush(stdin);
	
	return i;	
}


/* Returns a random number in the range 0 to max-1*/
int getRandomNumber( int max )
{
	return rand()%max;
}


/* Play a game of poker between the computer and player */
int playAGame( const int deck[][13])
{	
	int playerHand[HANDSIZE], dealerHand[HANDSIZE];
	int playerHandRank[3] = {0};
	int dealerHandRank[3] = {0};
	int winner;
    
    /* Deal out the original hands and get their current rank */
    dealAHand( deck, dealerHand );  
    rankHand( deck, dealerHand , dealerHandRank );     
    
    dealAHand( deck, playerHand  );
    rankHand( deck, playerHand , playerHandRank );     
    
    /* Print out the hands*/
    printf("---- DEALER HAND ----\n");
	printBackOfHand(); // printHandRank( dealerHandRank );
    /* Calculate and make dealer's changes then update hand rank */
    dealerDiscards( deck, dealerHand , dealerHandRank );    
    rankHand( deck, dealerHand , dealerHandRank );

    printf("\n---- PLAYER HAND ----\n");
	printHand(deck, playerHand);
    printHandRank( playerHandRank ); 
     
    /* Player discards here */
    playerDiscards( deck, playerHand, playerHandRank ); 

    /* Print out the updated hands */
    CLEARSCREEN;
    //system("cls");     

    /* Print out dealer's hand and rank*/
    printf("---- DEALER HAND ----\n");
	printHand(deck, dealerHand);
    printHandRank( dealerHandRank ); 
    
    /* Print out player's hand and rank*/
    printf("\n---- PLAYER HAND ----\n");
	printHand(deck, playerHand);
    printHandRank( playerHandRank ); 
    
    /* Find out who won */
    winner = compareHands( deck, dealerHand, playerHand, 
	              dealerHandRank, playerHandRank );	
	
	if(winner==1)
	    printf("Dealer wins!\n");
	else if(winner==2)
	    printf("Player wins!\n");
	else
	    printf("NOBODY WINS!\n");
	    
	return winner;
}


/* Decides which cards the Dealer should discard, then draws new ones */
void dealerDiscards( const int wDeck[][13], int *dealerHand, int *dealerHandRank )
{
	int i, card, toDiscard=0;
	//int bluff1 = rand()%10000;
	//int bluff2 = rand()%1000;
	int bluff3 = rand()%100;
	
	int dealerToDiscard[HANDSIZE] = {0};
	
	/* Strategy is to stand on flush or higher */
	if(dealerHandRank[0] <= FLUSH) {
		;
	}
	/* Strategy is to keep trips */
	else if(dealerHandRank[0] == THREEOFAKIND ) 
	{
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
		int suit = isFourFlush(wDeck, dealerHand);
		int pair = dealerHandRank[1];
		
		/* if pair is less than ten and dealer has a
		 * four flush draw to the four flush*/
		if( (pair<TEN && pair!=ACE) && suit!=-1) {
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
		/* First check if dealer has a fourflush or an outside straight */
		int suit = isFourFlush(wDeck, dealerHand);
		int outsideStraight = isOutsideStraight(wDeck, dealerHand); 
		
		if(suit!=-1) {
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
		else {
			for(i=0; i<HANDSIZE; i++) {
				card = getCardFace(wDeck, dealerHand[i]);
				if( card<QUEEN && card!=ACE ) {
					dealerToDiscard[i]=1;
					toDiscard++;
				}	    
			}			
		}
	}
	
	if(toDiscard==1)
	    printf("Dealer draws 1 card!\n");
	else
    	printf("Dealer draws %d cards!\n", toDiscard);
    	
    /* discard and draw cards */
	for(i=0; i<HANDSIZE; i++)
	    if(dealerToDiscard[i]==1)
    	    dealerHand[i] = dealACard();
	    
	sortHand(wDeck, dealerHand); 
    rankHand(wDeck, dealerHand, dealerHandRank);
}


/* Player decides which cards to discard, then new ones are dealt */
void playerDiscards( const int wDeck[][13], int *playerHand, int *playerHandRank )
{
	int playerToDiscard[HANDSIZE] = {0};
	int arrLen = HANDSIZE*2+1; /* Allow for spaces between numbers if necessary */
	char input[arrLen]; 
	
	printf("Choose cards to throw (eg 145): ");
	
	arrLen = getLine(input, arrLen);
	
	char c;
	int cardPos, i=0;
	while( ((c=input[i++])!='\0') && (c!='\n') && (i<arrLen) )
	{
		cardPos = c-49;
		if(cardPos>=0 && cardPos<HANDSIZE)
		    playerToDiscard[cardPos] = 1;
	}
	
    /* discard and draw cards */
	for(i=0; i<HANDSIZE; i++) {
	    if(playerToDiscard[i]==1)
    	    playerHand[i] = dealACard();		
	}

	sortHand(wDeck, playerHand); 
    rankHand(wDeck, playerHand, playerHandRank);
}


/* Compare the two hands to see who won, if the dealer wins return 1,
 * if the player wins return 2, if nobody wins return -1*/
int compareHands( const int wDeck[][13], 
                   const int *dealerHand, const int *playerHand,
                   const int *dealerHandRank, const int *playerHandRank)
{
	int i, dealerCard, playerCard;
	
	int winner = -1;
	
	int dRank0 = dealerHandRank[0];
	int pRank0 = playerHandRank[0];
	int dRank1 = dealerHandRank[1];
	int pRank1 = playerHandRank[1];
	int dRank2 = dealerHandRank[2];
	int pRank2 = playerHandRank[2];
	
	/* First check if one player has a higher rank than the other */
	if( dRank0 < pRank0 )
	    winner = 1;				// Dealer wins
	else if( pRank0 < dRank0 )
	    winner = 2;				// Player wins
	/* Next check if the player has a higher version of that rank */
	else if( dRank1==ACE && pRank1!=ACE )
	    winner = 1;
	else if(pRank1==ACE && dRank1!=ACE )
	    winner = 2;	
	else if( dRank1 > pRank1 )
	    winner = 1;
	else if( pRank1 > dRank1 )
	    winner = 2;	
	else if(dRank0==TWOPAIRS && dRank2!=pRank2 ) 
	{
		if(dRank2 > pRank2)
		    winner = 1;
		else
		    winner = 2;	
	}
	else if( ( getCardFace(wDeck, dealerHand[0])==ACE ) && 
	         ( getCardFace(wDeck, playerHand[0])!=ACE) )
	    winner = 1;
	else if( ( getCardFace(wDeck, playerHand[0])==ACE ) &&
	         ( getCardFace(wDeck, dealerHand[0])!=ACE ) )
	    winner = 2;	 
	else {
		for(i=HANDSIZE-1; i>=0; i--) 
		{
			dealerCard = getCardFace(wDeck, dealerHand[i]);
			playerCard = getCardFace(wDeck, playerHand[i]);
			if( dealerCard > playerCard ) {
				winner = 1;
				break;
			} 
	        else if( playerCard > dealerCard ) {	
	        	winner = 2;
	        	break;
			}    
		}
	}
	return winner;
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


/* Determines the rank of the player's hand and sets the rank array */
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


/* Set all cards to 0 before shuffling */
void reinitialiseDeck( int wDeck[][13] )
{
	/* Deck is full again */
	deckPosition = 1;
	int startValue = 1;
	
	int row, column;
	
	for( row=0; row<4; row++) {
		for(column=0; column<13; column++)
    		wDeck[row][column] = startValue++; 	
	}
}


/* Add all of the cards to a random position in the deck */
void shuffle( int wDeck[][13] )
{
	/* After shuffling the deck is full again */
	deckPosition = 1;
	
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


/* Return a card position in the deck */
int dealACard( void )
{
	int card = deckPosition;
	deckPosition++;
	return card;
}


/* Used to display cards as hidden for dealer before reveal */
void printBackOfHand() 
{
    int lines=9, characters=12;
    int cards, i, j;
	
	for(i=0; i<lines; i++) 
	{
		/* Print out a line for each card in the hand */
		for(cards=0; cards<HANDSIZE; cards++) {
			for(j=0; j<characters; j++)
	    	    printf("%c",DECKPICS[ 4 ][ 0 ][ i ][ j ]);
		}
	    	
	    printf("\n");
	}   
}


/* Print out the players hand */
void printHand( const int wDeck[][13], const int *hand)
{
	int i;
		
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
		for(cards=0; cards<HANDSIZE; cards++) {
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


/* Sort hand based upon the face values of its cards 
 * uses a bubblesort algorithm */
void sortHand( const int wDeck[][13], int *hand)
{
	int pass, card, temp;
	
	/* Sort hand based upon face value*/
	for(pass=0; pass<HANDSIZE; pass++) {
		for(card=0; card<HANDSIZE-1; card++) {
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
	
	for(i=1; i<HANDSIZE; i++) 
	{
		card = getCardFace(wDeck, hand[i]);
		
		if(card==prevCard) {
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

    return -1;
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
		
		if(card==prevCard) {
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
			    hasStraight=TEN;
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
			count++;
			if(count==2 && hasPair==-1) {
				hasPair = card;
			}
			if(count==3) 
			{
				hasThreeOfKind = card;
				if(i==2) /* if 3 of kind has come first */
    				hasPair = -1;
			}	
		}
		else if( i==1 ) /* if the first two cards are not the same*/
		    return -1;  /* then this is not a Full House */
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
	int suit[4] = {0}; /* { "Hearts", "Diamonds", "Clubs", "Spades"} */
	
	/* Count the number of cards of each suit in the hand */
	for(i=0; i<HANDSIZE; i++) 
	{
		++suit[getCardSuit(wDeck, hand[i])];
	}

    /* Return a suit the hand has four of them */
    for(i=0; i<4; i++) {
    	if(suit[i]==4)
    		return i;
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
		/* Check for runs */
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
				return HANDSIZE-1;
			}
		}
		else
		    count++;
		
		prevFace = card;
	}
	
	if(count==HANDSIZE-1)
		return 0;
	else
	    return -1;
}

