/*
 * Filename:    ex05_39.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/05/2017
 */

#include <stdio.h>

void towerOfHanoi( int, int, int, int );


/* Recursive towerOfHanoi function */
void towerOfHanoi(int numDisks, int startPeg, int endPeg, int tempPeg )
{
    if(numDisks > 0) {
        towerOfHanoi(numDisks-1, startPeg, tempPeg, endPeg );
        printf("%d --> %d\n", startPeg, endPeg);
        towerOfHanoi(numDisks-1, tempPeg, endPeg, startPeg );
    }
    
}

int main()
{
    towerOfHanoi( 17, 1, 3, 2 );

    return 0;
}

