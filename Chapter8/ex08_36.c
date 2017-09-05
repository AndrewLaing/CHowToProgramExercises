/*
 * Filename:	ex08_36.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/07/2017.
 * Description: Printing dates in various formats. Dates are commonly printed
 *				in several different formats in business correspondance. Two
 *				of the more common formats are;
 *					07/21/2002 July 21, 2002
 *				Write a program that reads in a date in the first format 
 *				and prints that date in the second format.
 */

#include <stdio.h>
#include <string.h>

void printDate(char []);
int getLine( char [], int );
int asciiToInt(const char *);


const char months[12][11] = {"January",  "February","March",  "April",
                             "May",      "June",    "July",   "August",
							 "September","October", "November","December"};


int main()
{
    char dateEntered[11];
    
    printf("Enter date to convert in yankee format (MM/DD/YYYY): ");
    getLine(dateEntered, 11);
	
    printDate(dateEntered);
	return 0;
}


void printDate(char dateEntered[])
{
	char *tokenPtr; 
	int i=0;
	tokenPtr = strtok( dateEntered, "/" );
	
	while( tokenPtr != NULL ) {
		if(i==0) {
			printf("%s ", months[asciiToInt(tokenPtr)-1] );
		}
		else if(i==1) {
			printf("%s, ", tokenPtr);
		}
		else if(i==2) {
			printf("%s\n", tokenPtr);
		}
		i++;
    	tokenPtr = strtok( NULL, "/" );
	}
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

int asciiToInt(const char *str)
{
	int result;
    sscanf(str, "%d", &result);
    
    return result;
}
