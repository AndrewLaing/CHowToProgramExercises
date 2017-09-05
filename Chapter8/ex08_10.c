/*
 * Filename:    ex08_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: Compare strings 
 * TODO - convert to use strncmp
 */

#include <stdio.h>
#include <string.h> /* for strcmp */

int getLine( char [], int );
int stringToInt(char []);

int main()
{   
    char s1[20], s2[20], input[20];
    size_t result;
    int n;

    printf("Enter string s1: ");
    getLine(s1, 20);
    printf("Enter string s2: ");
    getLine(s2, 20);
    printf("Enter number of characters to compare: ");
    getLine(input, 20);
    n = stringToInt(input); 

    result = strncmp( s1, s2, n );
    
    if(result==0) {
        printf("The first %d characters in the two strings are the same\n", n);
    }
    else if(result==-1) {
        printf("%s is less than %s\n", s1, s2);
    }
    else
        printf("%s is greater than %s\n", s1, s2);
    
    return 0;
}


/* Convert a char array to an integer */
int stringToInt(char str[])
{
    int result;
    sscanf(str, "%d", &result);

    return result;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}

