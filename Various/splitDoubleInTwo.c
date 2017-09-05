/*
 * Filename:    splitDoubleInTwo.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        04/06/2017.
 * Description: Input a double and split it into 2 char arrays
 *              Note Max 6 places decimal accuracy
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXINPUTLEN 9        /* Allows for sentinel value and nullbyte */
#define MAXFLOATLEN 15

int getLine( char [], int );
double getDouble( void );
int splitDouble(char [][MAXINPUTLEN], double );


int main()
{
    char sides[2][MAXINPUTLEN];
    double num1;
    
    printf("Enter double string (MAX 12 CHARS) > ");
    num1 = getDouble();
    
    printf("num1 = %f\n", num1);
    
    splitDouble(sides, num1);
    printf("lhs = %s\n", sides[0]);
    printf("rhs = %s\n", sides[1]);
    
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


/* Returns a valid double, sentinel value, or Error code */
double getDouble()
{
    char str[MAXFLOATLEN];
    double result;
    
    /* Input a string */
    getLine(str, MAXFLOATLEN);
    
    /* Convert to a float */
    sscanf(str, "%lf", &result); /* Note lf flag for double (long float)*/
    
    int test = result;
    /* If number is out of bounds return Error code */  
    if( (test<-999999 && test!=-9999999) || (test > 999999) )
        return -8888888;
    
    return result;
}



/* Splits a float string into lhs and rhs of decimal point */
int splitDouble(char floatSides[][MAXINPUTLEN], double num)
{
    char fStr[MAXFLOATLEN];
    
    sprintf(fStr, "%f", num);
    
    /* find index of floating point */
    int i=0, fpIndex = -1;
    
    do {
        if(fStr[i]=='.')
            fpIndex = i;
        i++;
    } while(i<MAXFLOATLEN && fpIndex==-1);
    
    /* Get number on rhs of fp */
    if(fpIndex >= 0) 
    {
        int k;

        for(i=0; i!=fpIndex && i<MAXINPUTLEN && fStr[i]!='\0' && fStr[i]!='\n'; i++)
            floatSides[0][i] = fStr[i];
        floatSides[0][i++]='\0';
        
        for(k=0; i<MAXFLOATLEN && fStr[i]!='\0' && fStr[i]!='\n'; i++, k++)
            floatSides[1][k] = fStr[i];
        floatSides[1][k]='\0';
    }
    else 
    {
        for(i=0; i!=fpIndex && i<MAXINPUTLEN && fStr[i]!='\0' && fStr[i]!='\n'; i++)
            floatSides[0][i] = fStr[i];
        floatSides[0][i++]='\0';

        for(i=0; i<6; i++)
            floatSides[1][i]='0';
        floatSides[1][i]='\0';
    }
        return 1;
}




