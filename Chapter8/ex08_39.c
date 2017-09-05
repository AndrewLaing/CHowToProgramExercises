/*
 * Filename:	ex08_39.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        11/07/2017.
 */

#include <stdio.h>
#include <string.h>
#define MAXLENGTH 90

void convertToMorse( char [] );
int getLine( char [], int );


const char alphaMorse[][5] = {
		".-","-...","-.-.","-..",".","..-.",
		"--.","....","..",".---","-.-",".-..",
		"--","-.","---",".--.","--.-",".-.",
		"...","-","..-","...-",".--","-..-",
		"-.--","--.."
};

const char numMorse[][6] = {
		".----","..---","...--","....-",".....",
		"-....","--...","---..","----.","-----"
};

int main()
{
    char toCode[MAXLENGTH];
    
    printf("Enter line to code: ");
    getLine(toCode, MAXLENGTH+1);
	
    convertToMorse( toCode );
	
	return 0;
}


void convertToMorse(char toCode[])
{
	int i;
	char c;
	
	for(i=0; toCode[i]!='\0'; i++)
	{
		c = toCode[i];
		if(c==' ')
		    printf("  ");
		else if(c>=48 && c<=57)
		    printf("%s ",numMorse[c-48]);
		else if(c>=65 && c<=90)
		    printf("%s ",alphaMorse[c-65]);
		else if(c>=97 && c<=122)
		    printf("%s ",alphaMorse[c-97]);
	}
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

