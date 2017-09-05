 /*
 * Filename:	ex06_28.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/05/2017
 */

#include <windows.h> /* for Sleep() */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

int getRandomNum( int );


int main()
{
	srand( (time(NULL)) );

    int i;
    int noDuplicates[SIZE] = {0};
    
    for(i=0; i<SIZE; i++)
    	++noDuplicates[getRandomNum(SIZE)];

    for(i=0; i<SIZE; i++) {
    	if(noDuplicates[i] > 0)
		    printf("%d ",i+1);
	}
	printf("\n");
    
    return 0;
}


int getRandomNum(int max)
{
	return rand()%max;
}

