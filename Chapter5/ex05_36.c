/*
 * Filename:	ex05_36.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/05/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNum( int, int );
int guessTheNumber();


int main()
{
	srand( (time(NULL)) );
	char c = 'y';
	
	int numberOfGuesses;
	
	while(c != 'n') 
	{
		numberOfGuesses = guessTheNumber();
		
		if(numberOfGuesses < 10) 
		    printf("\nEither you know the secret or you got lucky!\n");
		else if(numberOfGuesses == 10) 
		    printf("\nAhah! You know the secret!\n");
		else 
		    printf("\nYou should be able to do better!\n");
		
		/* clear the input stream*/
		while ((c = getchar()) != '\n' && c != EOF) {
			;
		}
		
		printf("Would you like to play again (y or n)? ");
		scanf("%c", &c);
	}	

	return 0;
}


int getRandomNum(int min, int max)
{
	int res = min + rand()%max;
	return res;
}


int guessTheNumber()
{
	int n, guess;
	int numberOfGuesses = 1;
	int correct=0;
	
	n = getRandomNum(1, 1000);
	
	printf("\nI have a number between 1 and 1000\n");
	printf("Can you guess my number?\n");
	printf("Please type your first guess: ");
	scanf("%d", &guess);
	
	while(!correct) {
		if(guess==n) {
			printf("Excellent! You guessed the number!\n");
			correct++;
		}
		else if(guess < n) {
			printf("Too low. Try again: ");
			numberOfGuesses++;
			scanf("%d", &guess);
		}
		else {
			printf("Too high. Try again: ");
			numberOfGuesses++;
			scanf("%d", &guess);
		}
	}
	
	return numberOfGuesses;
}

