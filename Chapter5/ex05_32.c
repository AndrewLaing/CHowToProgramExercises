/*
 * Filename:	ex05_32.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/05/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNum( void );
void answerTheQuestion( int, int );
void askQuestions( int );


int main()
{	
	srand( (time(NULL)) );
	askQuestions(2);	

	return 0;
}


int getRandomNum()
{
	int res = 1 + rand()%12;
	return res;
}

void answerTheQuestion(int a, int b)
{
	int guess;
	int correct=0;
	int result = a*b;
	
	do {
	    printf("What is %d x %d? ",a, b);
		scanf("%d", &guess);
		
		if(guess==result) {
			correct = 1;
			printf("Well done!\n");
		} else {
			printf("No. Please try again.\n");
		}
		   	
	} while(!correct);
}

void askQuestions(int n)
{
	int i, a, b;
	for(i=0; i<n; i++) {
		a = getRandomNum();
		b = getRandomNum();
		answerTheQuestion(a, b); 
	}
}

