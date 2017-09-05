/*
 * Filename:	ex08_07.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: Convert strings to ints
 */

#include <stdio.h>


int stringToInt(char []);
int getLine( char [], int );

int main()
{	
    char input[10];
    int i, sum=0;
    
    for(i=1; i<=4; i++) {
    	printf("Enter number #%d: ", i);
    	getLine(input, 10);
		sum += stringToInt(input);
	}
    
    printf("The sum of the 4 values is %d\n", sum);

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


/* Convert a char array to an integer */
int stringToInt(char str[])
{
	int result;
    sscanf(str, "%d", &result);

	return result;
}
