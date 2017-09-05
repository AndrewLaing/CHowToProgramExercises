/*
 * Filename:    ex08_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/06/2017.
 */
 
 
#include <stdio.h>
#include <string.h>
#define SIZE 16

char *words[SIZE] = { "FRUITY", "PRETTIFIED", "MODE", "BOTTLED", 
                    "WALLABY", "PRICED", "WALLED", "LAKE", 
                    "FORM", "WOOLY", "LITHE", "BABE",
                    "LINGERED", "CROSS", "FRANKED", "THURSDAY"};
                    
int endsInED( char *toCheck);

int endsInED( char *toCheck)
{   
    int len = strlen(toCheck);
    if(len<=1)
        return -1;
        
    if(toCheck[len-2]=='E' && toCheck[len-1]=='D' )
        return 1;
    
    return -1;
}


int main()
{
    int i;
    for(i=0; i<SIZE; i++) {
        if(endsInED(words[i])==1)
            printf("%s\n", words[i]);   
    }

    return 0;
}


