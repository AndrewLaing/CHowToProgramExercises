/*
 * Filename:	ex05_40.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/05/2017
 */

#include <stdio.h>

void towerOfHanoi( int );

/* Iterative binary towerOfHanoi function */
void towerOfHanoi(int numDisks)
{
	int i;
	int fromPeg, toPeg;
	int numPegs = 3;
	
    /* Note the left shift produces the number of moves necessary
	 * So 1 disk  would require 2-1 moves
	 *    3 disks would require 8-1 moves etc
	 */
    for (i=1; i < (1<<numDisks); i++) 
	{
        fromPeg = (i & i-1) % numPegs;                 /* 1&0=0; 0%3=0        */
        toPeg   = ( (i | i-1)+1 ) % numPegs;           /* 1|0=1; 1+1=2; 2%3=2 */
        printf( "%d --> %d\n", fromPeg+1, toPeg+1 );   /* Plus 1 otherwise 0-2*/
    }   
}

int main()
{
	/* Would this be able to handle as large numbers as the recursive version
	 * accurately 1<<17 == 131072 which is within the bounds of an integer but
	 * these numbers would overflow an integer pretty soon afterwards. */
	towerOfHanoi( 5 );

	return 0;
}


