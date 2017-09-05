/*
 * Filename:	ex04_32.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/04/2017
 */

#include <stdio.h>

#define printStar printf( "*" );
#define printSpace printf( " " ); 
#define newLine printf( "\n" );

int main()
{
    int i, j, k;
    int rows, max;
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    
    // Filter out out of bounds and rows==1
    if(rows<1 || rows>19)
        return 0;
    else if(rows==1) {
    	printStar;
    	newLine;
    	return 0;
	} 
    
    max = rows/2;
    
    // Adjust to work for an even number of rows
    if(rows%2==0)
        max-=1;
    
    // Print widening part of diamond
    for(i=0; i<=max; i++) 
    {
    	for(j=0; j<(max-i); j++)
    	    printSpace;
    	for(k=0; k<(1+(i*2)); k++)
    	    printStar;
    	newLine;
	}

    // Adjust to work for an even number of rows
    if(rows%2==0)
        max+=1;

    // Print narrowing part of diamond 
    for(i=max-1; i>=0; i--) 
    {
    	// This is included for printing even rows properly
    	if(rows%2==0)
    	    j=1;
    	else
    	    j=0;

    	for( ; j<(max-i); j++) {
    		printSpace;
		}
    	    
    	for(k=0; k<(1+(i*2)); k++)
    	    printStar;
    	newLine;
	}
    
	return 0;
}
