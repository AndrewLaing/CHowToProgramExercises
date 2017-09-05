/*
 * Filename:	ex08_35.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/07/2017.
 * Description: Read in sentences and print them out justified
 *				to fit in a 65 character space
 */

#include <stdio.h>

#define SCREENWIDTH 65
#define MARGINWIDTH 10

void printJustifiedText(char [], int );
int getLine( char s[], int maxLength );


int main()
{
    int lengths[3];
    int i;
    char sentences[3][SCREENWIDTH];
    
    
    for(i=0; i<3; i++) {
	    printf("Enter line #%d: ", i);
	    lengths[i] = getLine( sentences[i], SCREENWIDTH );     	
	}

    
    printf("\n---- The Justified text ----\n\n");
    for(i=0; i<3; i++) {
        printJustifiedText(sentences[i], lengths[i]);	
	}

	return 0;
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


void printJustifiedText(char s[], int length)
{
	int spacesNeeded = SCREENWIDTH - length;
	int spacesUsed=0, addNum, remainder;
	int i, j;
	
	for(i=0; i<length; i++)
		if(s[i]==' ')
		    spacesUsed++;
	
	addNum = spacesNeeded / spacesUsed;
	remainder = spacesNeeded - (addNum * spacesUsed ); 
	
    /* Print the margin */
	for(i=0; i<MARGINWIDTH; i++)
		printf(" ");
    
    /* Print the justified text */
	for(i=0; i<length; i++)
	{
		printf("%c", s[i]);
		if(s[i]==' ') 
		{
			for(j=0; j<addNum; j++)
		        printf(" ");
		        
		    spacesUsed--;
		    
		    if(remainder > 0) {
		    	printf(" ");
		        remainder--;
			}
		}		    
	}
	printf("\n");
}

