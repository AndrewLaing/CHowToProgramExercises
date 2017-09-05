/*
 * Filename:    ex05_34.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/05/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int getRandomNum( void );
void correctAnswer();
void wrongAnswer();
int answerTheQuestion( int, int );
void askQuestions( int );


int main()
{
    srand( (time(NULL)) );
    askQuestions(10);   

    return 0;
}



int getRandomNum()
{
    int res = 1 + rand()%12;
    return res;
}

void correctAnswer() 
{
    int response = getRandomNum();
    
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
    int response = getRandomNum();
    
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


int answerTheQuestion(int a, int b)
{
    int guess;
    int wrongGuesses = 0;
    int correct=0;
    int result = a*b;
    
    do {
        printf("What is %d x %d? ",a, b);
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

void askQuestions(int n)
{
    int i, a, b;
    int wrong=0;
    for(i=0; i<n; i++) {
        a = getRandomNum();
        b = getRandomNum();
        wrong += answerTheQuestion(a, b); 
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

