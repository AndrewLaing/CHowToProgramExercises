/*
 * Filename:	ex07_28.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/06/2017
 * TODO:        Add a getInteger method
 *              Add the function pointer array
 *              Add a mainMenu method that uses a switch-case
 *                  to call a method from the function pointer array
 */

#include <stdio.h>
#include <stdlib.h>

#define PAUSE system("pause")
#define CLEARSCREEN system("cls")
#define STUDENTS 3
#define EXAMS 4

int getLine( char [], int );
void minimum( const int[][ EXAMS ], int, int );
void maximum( const int[][ EXAMS ], int, int );
void average( const int[][ EXAMS ], int, int );
void printArray( const int[][ EXAMS ], int, int );


const char * MENU =
"Enter a choice:\n"
"   0  Print the array of grades\n"
"   1  Find the minimum grade\n"
"   2  Find the maximum grade\n"
"   3  Print the average on all tests for each student\n"
"   4  End program\n> ";


int main()
{	
    const int studentGrades[ STUDENTS ][ EXAMS ] =
        { {77, 68, 86, 73},
          {96, 87, 89, 78},
		  {70, 90, 86, 81} };
		  
	void (*f[4])( const int[][ EXAMS ], int, int ) = { printArray, minimum, maximum, average };
	
	char input[2];
	int choice = 0;

	while(choice!=4)
	{
		printf("%s", MENU);	  
		getLine(input, 2); 	  
		choice = input[0]-48;
	    CLEARSCREEN;
		
		switch(choice) {
			case 0:
			case 1:
			case 2:
			case 3:
				(*f[choice])( studentGrades, STUDENTS, EXAMS );
				break;
			case 4:
				printf("Quitting program ...\n");
				break;
			default:
				printf("*** Invalid option ***\n");
				break;
		}
		printf("\n");
		PAUSE;
		fflush(stdin);
		CLEARSCREEN;
	}
	
    return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
	int c, i=0;
	
	while(--maxLength > 0 && ( c=getchar())!=EOF && c!='\n')
	    s[i++]=c;
	if(c=='\n')
	    s[i++]=c;
	s[i] = '\0';
	
	return i;	
}


/* Print the lowest grade */
void minimum( const int grades[][ EXAMS ], int pupils, int tests )
{
	int i, j, lowGrade=100;
	
	for( i=0; i<=pupils-1; i++ )
	    for( j=0; j<=tests-1; j++ )
	        if(grades[i][j] < lowGrade)
	            lowGrade = grades[i][j];
	            
	printf( "Lowest grade: %d\n", lowGrade );
}


/* Print the highest grade */
void maximum( const int grades[][ EXAMS ], int pupils, int tests )
{
	int i, j, highGrade=0;
	
	for( i=0; i<=pupils-1; i++ )
	    for( j=0; j<=tests-1; j++ )
	        if(grades[i][j] > highGrade )
	            highGrade = grades[i][j];
	            
	printf( "Highest grade: %d\n", highGrade );
}


/* Print the average on all tests for each student */
void average( const int grades[][ EXAMS ], int pupils, int tests )
{
	int student;
	for(student=0; student<pupils; student++ )
	{
		int i, total=0;
	
		for( i=0; i<tests; i++)
		    total += grades[ student ][ i ];
		
		printf( "The average grade for student %d is %.2f\n", 
		        student, ( double ) total/tests);
	}
}

/* Print the array of grades */
void printArray( const int grades[][ EXAMS ], int pupils, int tests )
{
	int i, j;
	
	printf( "                 [0]  [1]  [2]  [3]" );
	
	for( i=0; i<=pupils-1; i++ )
	{
		printf("\nstudentGrades[%d] ", i);
		
		for( j=0; j<=tests-1; j++ )
	        printf("%-5d", grades[ i ][ j ]);
	}
	printf("\n");
}

