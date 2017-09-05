/*
 * Filename:    ex05_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 */

#include <stdio.h>


void fillCharacter( int, char );


int main()
{
    fillCharacter(5, '#'); 
    return 0;
}


void fillCharacter(int n, char c)
{
    int i, j;
    
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("%c", c);
        }
        printf("\n");
    }
    
    printf("\n");
}

