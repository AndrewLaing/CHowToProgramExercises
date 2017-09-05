/*
 * Filename:	ex08_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/06/2017.
 */
 
 
#include <stdio.h>
#include <string.h>
#define SIZE 16


char *towns[SIZE] = { "liverpool", "southport", "birkenhead", "bootle", 
	                "wallasey", "prescott", "heswall", "hoylake", 
					"formby", "woolton", "litherland", "bebington",
	                "billinge", "crosby", "frankby", "thurstaston"};


void selectionSort( char * [SIZE], int );


void selectionSort( char *toSort[SIZE], int arrLen )
{
	int i, j, index;
	char *smallest, *temp;
	
    for(i=0; i<arrLen; i++)
    {	
        smallest = toSort[i];
        
    	for(j=i; j<arrLen; j++) 
		{
    		if( strcmp(toSort[j], smallest) < 0 ) {
				smallest = toSort[j];
				index = j;
			}
		}

		if( strcmp(smallest, toSort[i]) < 0 ) {
			temp = toSort[i];
			toSort[i] = smallest;
			toSort[index] = temp;			
		}
	}
}


int main()
{
    int i;

    printf("----- TOWNS IN MERSEYSIDE UNSORTED -----\n");
	for(i=0; i<SIZE; i++)
	    printf("%s ",towns[i]);
	printf("\n");

    selectionSort(towns, SIZE);

    printf("\n----- TOWNS IN MERSEYSIDE SORTED -----\n");
	for(i=0; i<SIZE; i++)
	    printf("%s ",towns[i]);
	printf("\n");

	return 0;
}


