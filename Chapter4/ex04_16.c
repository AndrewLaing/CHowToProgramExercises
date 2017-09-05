/*
 * Filename:	ex04_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 */

#include <stdio.h>
#include <math.h>

int main()
{
    int i, j;

    for(i=1; i<=10; i++) 
    {	
	    for(j=0; j<i; j++ )
	    {
	    	printf( "*");	
		}
		printf( "\n");	
	}

    for(i=12; i>=1; i--) 
    {	
        if(i==10 || i==8)
            continue;

	    for(j=0; j<i; j++ )
	    {
	    	printf( "*");	
		}
		printf( "\n");	
	}


    for(i=12; i>=1; i--) 
    {	
        if(i==8 || i==7)
            continue;

	    for(j=0; j<12-i; j++ )
	    {
	    	printf( " " );	
		}

	    for(j=0; j<i; j++ )
	    {
	    	printf( "*" );	
		}
		printf( "\n" );	
	}


    for(i=1; i<=10; i++) 
    {	
        for(j=0; j<10-i; j++)
	    {
	    	printf( " " );	
		}
    
	    for(j=0; j<i; j++ )
	    {
	    	printf( "*" );	
		}
		printf( "\n" );	
	}

	return 0;
}

