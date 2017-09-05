/*
 * Filename:	integerToBinaryString.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        12/06/2017.
 * Description: Convert integer to a binary string and
 *              converts a binary string to a decimal number.
 *              Note the first binary bit is left as zero 
 *				and it is two bytes long.
 */

#include <stdio.h>
#include <stdlib.h>
#define BINARYLENGTH 17   /* Include null byte */
#define MAXINPUTLEN 7
#define PAUSE system("pause")
#define CLEARSCREEN system("cls")

// Prototypes //////////////////////////////

void mainMenu( void );

int getLine( char [], int );
int getInteger( void );
void toBinaryString(char [BINARYLENGTH], int );
int binaryStringToInteger(char [BINARYLENGTH]);
// Methods /////////////////////////////////

int main()
{
	int i, result;
	char bin[BINARYLENGTH];
	printf("Enter a number ? ");
	i = getInteger(); 

	toBinaryString(bin, i);
	printf("Binary version = %s\n", bin);
	
	result = binaryStringToInteger(bin);
	printf("Result = %d\n", result);
	
	printf("Hex = %X\n", result);
	return 0;
}

/* converts a binary string to a decimal number */
int binaryStringToInteger(char bin[BINARYLENGTH])
{
	int i, result=0;
	int twos = 1;
	for(i=1; i<BINARYLENGTH-1; i++)
	    twos*=2;

	
	for(i=0; i<BINARYLENGTH; i++)
	{
		if(bin[i]=='1')
    		result+=twos;
		twos/=2;	
	}

	return result;
}



/* converts a decimal number to a binary string */
void toBinaryString(char bin[BINARYLENGTH], int decimal)
{
	int i;
	int twos = 1;
	for(i=2; i<BINARYLENGTH-1; i++)
	    twos*=2;

	bin[0]='0';
	
	for(i=1; i<BINARYLENGTH-1; i++)
	{
		if(twos-decimal <= 0) {
			bin[i]='1';
			decimal -= twos;
		}
		else
		    bin[i]='0';
		
		twos/=2;		
	}

	bin[i]='\0';
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


/* Returns a valid WORDLENGTH integer, sentinel value, or Error code */
int getInteger()
{
	char str[MAXINPUTLEN];
	int c, i=0, isNegative=0, result=0;
	
	/* Input a string */
    getLine(str, MAXINPUTLEN);
	
	/* Convert to an Integer */
	while( ( (c=str[i])!=EOF ) && ( i<MAXINPUTLEN ) )
	{
		if(c=='\0' || c=='\n')
		    break;
		 
		/* Allow signed numbers */ 
		if(i==0 && c=='-')
		    isNegative = 1;
		else if(i==0 && c=='+')
		    ;
		else {
			c -= 48; /* Convert ACSII code to number */
			
			/* If the character was not a number return error status */
			if(c<0 || c>9) 
				return -88888;
			else
				result = ( result * 10) + c;		
		}

		i++;
	}
	
	if(isNegative==1)
	    result -= result+result;
	
	/* If number is out of bounds return Error code */  
	if( (result<-999999 && result!=-9999999) || (result > 999999) )
		return -88888;

	return result;
}


