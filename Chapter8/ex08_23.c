/*
 * Filename:	ex08_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/06/2017.
 */
 
 
#include <stdio.h>
#include <string.h>
#define SIZE 16


char *towns[SIZE] = { "liverpool", "southport", "birkenhead", "bootle", 
	                "wallasey", "prescott", "heswall", "hoylake", 
					"formby", "woolton", "litherland", "bebington",
	                "billinge", "crosby", "frankby", "thurstaston"};


void printBWords( char * [SIZE], int );


void printBWords( char *toPrint[SIZE], int arrLen )
{	
    int i;
    for(i=0; i<arrLen; i++)
    {	
        if(toPrint[i][0]=='b')
            printf("%s\n",toPrint[i]);
	}
}


int main()
{
    printBWords( towns, SIZE );

	return 0;
}


