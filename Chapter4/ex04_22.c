/*
 * Filename:	ex04_22.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/04/2017
 * Description: Modify the program of fig04_07 so that it calculates the
 *				average grade for the class.
 */

#include <stdio.h>

int main()
{
    int grade;
    int total = 0;
    int count = 0;
    
    printf( "Enter the letter grades.\n" );
    printf( "Enter the EOF character to end input.\n");

    while( (grade=getchar() ) != EOF )
    {
    	switch( grade )
    	{
    		case 'A': case 'a':
    			total += 5;
    			count++;
    			break;
    		case 'B': case 'b':
    			total += 4;
    			count++;
    			break;
    		case 'C': case 'c':
    			total += 3;
    			count++;
    			break;
    		case 'D': case 'd':
    			total += 2;
    			count++;
    			break;
    		case 'F': case 'f':
    			total += 0;
    			count++;
    			break;
    		case '\n': case ' ':
    			break;
    		default:
    			printf( "Incorrect letter grade entered.\n" );
                printf( "Enter a new grade.\n");
    			break;
		}
	}
	
	grade = total / count;
	
	printf( "The average grade for the class was " );
	
	switch( grade )
	{
		case 5:
            printf( "A.\n" );
			break;
		case 4:
			printf( "B.\n" );
			break;
		case 3:
			printf( "C.\n" );
			break;
		case 2:
			printf( "D.\n" );
			break;
		default:
			printf( "F.\n" );
			break;
	} 
    
	return 0;
}

