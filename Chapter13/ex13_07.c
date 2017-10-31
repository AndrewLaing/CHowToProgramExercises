/*
 * Filename:    ex13_07.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/10/2017
 * Description: Macro
 */
 
#include <stdio.h>
#define MAXLEN 7
#define MINIMUM2(a,b) ( (a < b) ? a : b )
#define MINIMUM3(a,b,c) ( ( a < b ) ? ( MINIMUM2(a,c) ) : ( MINIMUM2(b,c) ) )

int getLine( char [], int );
int getInteger( void );

int main()
{
    int x, y, z, smallest;
    
    printf("Enter the value of x > ");
    x = getInteger();
    
    printf("Enter the value of y > ");
    y = getInteger();
    
    printf("Enter the value of z > ");
    z = getInteger();
    
    smallest = MINIMUM3(x, y, z);
    
    printf("Smallest = %d\n", smallest);
    return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    if(c=='\n')
        s[i++]=c;
    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


/* Returns a valid integer */
int getInteger()
{
    char str[MAXLEN];
    int result=0;
    
    /* Input a string */
    getLine(str, MAXLEN);
    
    /* Convert to a float */
    sscanf(str, "%d", &result);

    return result;
}

