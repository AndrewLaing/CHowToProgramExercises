/*
 * Filename:	ex08_08.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        20/06/2017.
 * Description: Convert strings to doubles
 */

#include <stdio.h>

double stringToDouble(char []);
int getLine( char [], int );

int main()
{	
    char input[10];
    int i;
	double sum=0.0;
    
    for(i=1; i<=4; i++) {
    	printf("Enter number #%d: ", i);
    	getLine(input, 10);
		sum += stringToDouble(input);
	}
    
    printf("The sum of the 4 values is %lf\n", sum);

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
double stringToDouble(char str[])
{
	double result;
    sscanf(str, "%lf", &result);

	return result;
}
