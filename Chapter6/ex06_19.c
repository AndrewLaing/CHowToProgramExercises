/*
 * Filename:	ex06_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/05/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIDES 6

int getRollResult(  );


int getRollResult()
{
    return 1 + rand()%SIDES;
}


int main()
{
    srand( (time(NULL)) );
    int totals[13] = {0};
    int i;
	
    for(i=0; i<=36000; i++)
        ++totals[( getRollResult() + getRollResult() )];
	
    for(i=2; i<=12; i++) {
    	printf("%d:\t%d\n", i, totals[i]);
    }
	
    return 0;
}

