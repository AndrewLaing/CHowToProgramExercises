/*
 * Filename:	ex08_34a.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        05/07/2017.
 * Description: Write a program that read several lines of text and prints
 *				a table indicating the number of occurences of each letter
 *				of the alphabet in the text.
 */

#include <stdio.h>
#include <ctype.h>

void countLetters( int [], const char *, int );
void printResult(int count[]);
int getLine( char [], int );


int main()
{
	char str[80];
	int count[26] = {0};
    int i, length;

    for(i=0; i<3; i++)
    {
    	printf("Enter line #%d: ", i);
    	length = getLine(str, 80); 
    	countLetters( count, str, length);
	}
        
    printResult(count);
 	return 0;
}


void countLetters(int count[], const char *sentence, int length)
{
	int i, letter;
    for(i=0; i<length; i++)
	{
		letter = tolower(sentence[i]);
		letter -= 97;
		if(letter>=0 && letter<=26)
		    ++count[letter];	
	}	
}


void printResult(int count[])
{
	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	
	int i;
	
	printf("\n\n\t\t----- LETTER FREQUENCY -----\n\n");
	
	
	for(i=0; i<8; i++)
		printf("%8c", alphabet[i]);
	printf("\n");
	for(i=0; i<8; i++)
		printf("%8d", count[i]);
	printf("\n\n");
	for(i=8; i<16; i++)
		printf("%8c", alphabet[i]);
	printf("\n");
	for(i=8; i<16; i++)
		printf("%8d", count[i]);
	printf("\n\n");
	for(i=16; i<24; i++)
		printf("%8c", alphabet[i]);
	printf("\n");
	for(i=16; i<24; i++)
		printf("%8d", count[i]);
	printf("\n\n");
	for(i=24; i<26; i++)
		printf("%8c", alphabet[i]);
	printf("\n");
	for(i=24; i<26; i++)
		printf("%8d", count[i]);
	printf("\n");
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

