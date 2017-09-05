/*
 * Filename:    reverseString.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/06/2017.
 */
 
 
#include <stdio.h>
#include <string.h>

                    
void reverse( char []);

/* reverse a string in place */
void reverse( char s[])
{   
    int c, i, j;
    for(i=0, j=strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int main()
{
    char word[] = "forwards";
    
    printf("word = %s\n", word);
    reverse(word);  
    printf("word = %s\n", word);
    
    return 0;
}


