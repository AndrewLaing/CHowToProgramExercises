/*
 * Filename:	ex04_30.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/04/2017
 * Description: Rewrite the program of fig04_07 by replacing the switch
 *				statement with a nested if/else statement; be careful 
 *				to deal with the default case properly.
 */

#include <stdio.h>

int main()
{
    int grade;
    int aCount = 0, bCount = 0, cCount = 0,
        dCount = 0, fCount = 0;
    
    printf( "Enter the letter grades.\n" );
    printf( "Enter the EOF character to end input.\n");

    while( (grade=getchar() ) != EOF )
    {
    	if(grade=='A' || grade=='a')
    	{
    		++aCount;
		}
		else if(grade=='B' || grade=='b')
    	{
    		++bCount;
		}
		else if(grade=='C' || grade=='c')
    	{
    		++cCount;
		}
		else if(grade=='D' || grade=='d')
    	{
    		++dCount;
		}
		else if(grade=='F' || grade=='f')
    	{
    		++fCount;
		}
		else if(grade=='\n' || grade==' ')
    	{
		}
		else {
			printf( "Incorrect letter grade entered.\n" );
            printf( "Enter a new grade.\n");
		}
	}
	printf( "Totals for each letter grade are:\n" );
    printf( "A: %d\n", aCount );	
    printf( "B: %d\n", bCount );
    printf( "C: %d\n", cCount );
    printf( "D: %d\n", dCount );    
    printf( "F: %d\n", fCount );    
    
	return 0;
}
