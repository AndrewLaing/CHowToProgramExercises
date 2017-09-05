/*
 * Filename:	ex05_44.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        07/05/2017
 */

#include <stdio.h>
#include <time.h>
#include <math.h>

int getRandomNum( int );
void correctAnswer();
void wrongAnswer();
int answerTheQuestion( int, int, int );
void askQuestions( int, int, int ); 


int getRandomNum(int max)
{
	int res = 1 + rand()%max;
	return res;
}

void correctAnswer() 
{
	int response = getRandomNum(12);
	
	switch(response) {
		case 1: case 2: case 3:
			printf("Very good!\n");
			break;
		case 4: case 5: case 6:
			printf("Excellent!\n");
			break;
		case 7: case 8: case 9:
			printf("Nice Work!\n");
			break;
		case 10: case 11: case 12:
			printf("Keep up the good work!\n");
			break;
		default:
			printf("Congrats!\n");
	}
}

void wrongAnswer() 
{
	int response = getRandomNum(12);
	
	switch(response) {
		case 1: case 2: case 3:
			printf("No. Please try again!\n");
			break;
		case 4: case 5: case 6:
			printf("Wrong. Try once more!\n");
			break;
		case 7: case 8: case 9:
			printf("Don't give up!\n");
			break;
		case 10: case 11: case 12:
			printf("No. Keep trying!\n");
			break;
		default:
			printf("So wrong, dude!\n");
	}
}

int answerTheQuestion(int a, int b, int typeOfQuestions)
{
	int guess;
	int wrongGuesses = 0;
	int correct=0;
	int result;
	
	if(typeOfQuestions > 4)
	    typeOfQuestions = getRandomNum(4);
	
	switch(typeOfQuestions)
	{
		case 1:
			result = a+b;
			break;
		case 2:
			result = a-b;
			break;
		case 3:
			result = a*b;
		    break;
		case 4:
			result = a/b;
		    break;
		default:
			printf("Something went wrong\n");
			break;
	}
	
	do {
		switch(typeOfQuestions)
		{
			case 1:
				printf("What is %d + %d? ",a, b);
				break;
			case 2:
				printf("What is %d - %d? ",a, b);
				break;
			case 3:
				printf("What is %d x %d? ",a, b);
			    break;
			case 4:
				printf("What is %d / %d? ",a, b);
			    break;
			default:
				printf("Something went wrong\n");
				break;
		}

		scanf("%d", &guess);
		
		if(guess==result) {
			correct = 1;
			correctAnswer();
		} else {
			wrongAnswer();
			wrongGuesses++;
		}
		   	
	} while(!correct);
	
	return wrongGuesses;
}

void askQuestions(int n, int level, int problemType)
{
	int i, a, b;
	int right=10;
	int wrong=0;
	
	int max = (int)(pow(10, level)-1);
	
	for(i=0; i<n; i++) {
		a = getRandomNum(max);
		b = getRandomNum(max);
		wrong += answerTheQuestion(a, b, problemType); 
	}
	
	float percentage = (10.0/(10.0 + wrong)) * 100.0;
	
	if(percentage < 75.0) {
		printf("\nOnly %.2f%% of your guesses were correct\n", percentage);
		printf("Please ask your instructor for extra help\n");
	}
	else {
		printf("\nCongratulations %.2f%% of your guesses were correct\n", percentage);
	}
}

int main()
{
	srand( (time(NULL)) );
	int level, problemType;
	printf("Enter the level of the student: ");
	scanf("%d", &level);
	
	int getOption = 1;
	
	while(getOption)
	{
		printf("\nProblem Options\n");
		printf("\n1: Addition Problems Only");
		printf("\n2: Subtraction Problems Only");
		printf("\n3: Multiplication Problems Only");
		printf("\n4: Division Problems Only");
		printf("\n5: Random mix of problems\n");
		printf("\nEnter your choice: ");
		scanf("%d", &problemType);
	    
		if(problemType>0 && problemType<5) {
			getOption = 0;
		} else {
			printf("\n<< Illegal Option - try again! >>\n\n");
		}
	}
	
	askQuestions(10, level, problemType);	

	return 0;
}

