 /*
 * Filename:	ex06_30.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/05/2017
 * Description: Sieve of Eratosthenes
 */
 

#include <stdio.h>
#define SIZE 1000


int main()
{
	int array[ SIZE ];
	int i, j;
	
	for(i=0; i<SIZE; i++)
        array[i]=1;
    
    for(i=2; i<SIZE; i++) {
    	for(j=i+1; j<SIZE; j++) {
    		if(array[j]==1 && j%i==0)
    		    array[j]=0;
		}
	}
	
	for(i=0; i<SIZE; i++)
        if(array[i]==1)
            printf("%d ", i);
            
    printf("\n");
	
    return 0;
}

