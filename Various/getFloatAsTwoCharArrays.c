/*
 * Filename:    getFloatAsTwoCharArrays.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        13/06/2017.
 * Description: Input a float and store it as two integers, one for
 *              the left hand side of the decimal point, and one for
 *              the right hand side.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXINTLEN 7
#define MAXFLOATLEN 14
#define MAXINTVAL 999999   /* Thus maxFloat = 999999.999999*/


int getLine( char [], int );
int getFloatAsTwoInts(char [][MAXINTLEN]);


int main()
{
    char num1[2][MAXINTLEN];
    
    printf("Enter float string (MAX 13 CHARS) > ");
    getFloatAsTwoInts(num1);
    
    printf("lhs = %6s\n", num1[0]);
    printf("rhs = %6s\n", num1[1]);
         
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
    
    fflush(stdin); /* Clear any overflow*/
    
    return i;   
}


/* Returns a 1 if valid, -1 if invalid */
int getFloatAsTwoInts(char floatSides[][MAXINTLEN])
{
    char str[MAXFLOATLEN];
    
    /* Input a float string */
    getLine(str, MAXFLOATLEN);
    

    /* find index of floating point */
    int i=0, fpIndex = -1;
    
    do {
        if(str[i]=='.')
            fpIndex = i;
        i++;
    } while(i<MAXFLOATLEN && fpIndex==-1);
    
    /* Get number on rhs of fp */
    if(fpIndex >= 0) 
    {
        int k;

        for(i=0; i!=fpIndex && i<MAXINTLEN && str[i]!='\0' && str[i]!='\n'; i++)
            floatSides[0][i] = str[i];
        floatSides[0][i++]='\0';
        
        for(k=0; i<MAXFLOATLEN && str[i]!='\0' && str[i]!='\n'; i++, k++)
            floatSides[1][k] = str[i];
        floatSides[1][k]='\0';
    }
    else 
    {
        for(i=0; i!=fpIndex && i<MAXINTLEN && str[i]!='\0' && str[i]!='\n'; i++)
            floatSides[0][i] = str[i];
        floatSides[0][i++]='\0';

        for(i=0; i<6; i++)
            floatSides[1][i]='0';
        floatSides[1][i]='\0';
    }
//    if(lhs > MAXINTVAL) {
//      printf("\n*** Fatal Error! Floating-point Accumulator overflow ***\n");
//      return -1;
//  }
//  else
        return 1;
}

