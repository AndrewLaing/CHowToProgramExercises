/*
 * Filename:    ex05_33.c
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
void answerTheQuestion( int, int );
void askQuestions( int );


int main()
{
    srand( (time(NULL)) );
    askQuestions(5);    

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
            correctAnswer();
        } else {
            wrongAnswer();
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

