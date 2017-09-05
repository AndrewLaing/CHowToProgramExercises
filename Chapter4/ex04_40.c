/*
 * Filename:	ex04_40.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/04/2017
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
    	switch( grade )
    	{
    		case 'A': case 'a':
    			if(grade=='A' || grade=='a')
    			    ++aCount;
    		case 'B': case 'b':
    			if(grade=='B' || grade=='b')
    			    ++bCount;
    		case 'C': case 'c':
                if(grade=='C' || grade=='c')
    			    ++cCount;
    		case 'D': case 'd':
                if(grade=='D' || grade=='d')
    			    ++dCount;
    		case 'F': case 'f':
                if(grade=='F' || grade=='f')
    			    ++fCount;
    		default:
                if(grade!='\n' && grade!=' ' && 
				   grade!='A'  && grade!='a' && grade!='B' && grade!='b' && 
				   grade!='C'  && grade!='c' && grade!='D' && grade!='d' && 
				   grade!='F'  && grade!='f') 
				{
                	printf( "Incorrect letter grade entered.\n" );
                    printf( "Enter a new grade.\n");
				}
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
