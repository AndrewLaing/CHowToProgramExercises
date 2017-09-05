/*
 * Filename:	ex06_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/05/2017
 */

#include <stdio.h>
#define SIZE 20

int main()
{
    short input[SIZE] = {10,20,51,66,10,88,66,45,46,99,
                         33,55,45,68,12,11,45,65,77,44};
    short alreadyRead[SIZE] = {0};
    int nextIndex = 0;
    int i, j, printNum;
	
    for(i=0; i<=SIZE-1; i++) {
	printNum = 1;
		
	for(j=0; j<nextIndex; j++) {
    	    if(alreadyRead[j]==input[i]) {
		printNum = 0;
		break;
	    }
	}
		
	if(printNum) {
	    printf("%d ", input[i]);
	    alreadyRead[nextIndex++] = input[i];
	}
    }
	
    return 0;
}
