/*
 * Filename:	stringConversions.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        29/06/2017.
 */

#include <stdio.h>

double atof(const char *);
int atoi(const char *);
long atol(const char *);

double strtod(const char *, char ** );
long strtol(const char *, char **, int );
unsigned long strtoul(const char *, char **, int );

int isdigit( int );

int main()
{	    
    double d;
    int i;
    long l;
	unsigned long ul;  
	char *stringPtr;
	
    d = atof( "99.0" );
	printf("%s%.3f\n%s%.3f\n",
	       "The string \"99.0\" converted to double is ", d,
		   "The converted value divided by 2 is ", d/2.0); 
    
    i = atoi( "2593" );
	printf("\n%s%i\n%s%i\n",
	       "The string \"2593\" converted to int is ", i,
		   "The converted value minus 593 is ", i-593); 

    l = atol( "1000000" );
	printf("\n%s%ld\n%s%ld\n",
	       "The string \"1000000\" converted to long int is ", l,
		   "The converted value divided by 2 is ", l/2); 


    const char *string = "51.2% are admitted";    
    d = strtod(string, &stringPtr);
    
	printf("\nThe string \"%s\" is converted to the\n", string);
	printf("double value %.2f and the string \"%s\"\n", d, stringPtr); 


    const char *string1 = "51556 fans attended";    
    l = strtol(string1, &stringPtr, 0);
    
	printf("\nThe string \"%s\" is converted to the\n", string1);
	printf("long value %ld and the string \"%s\"\n", l, stringPtr); 


    const char *string2 = "655642 sheep in Sweden like pillows";    
    ul = strtoul(string2, &stringPtr, 0);
    
	printf("\nThe string \"%s\" is converted to the\n", string2);
	printf("unsigned long value %lu and the string \"%s\"\n", ul, stringPtr); 


 	return 0;
}


double atof(const char *str)
{
	double result;
    sscanf(str, "%lf", &result);
    
    return result;
}


int atoi(const char *str)
{
	int result;
    sscanf(str, "%d", &result);
    
    return result;
}


long atol(const char *str)
{
	long result;
    sscanf(str, "%ld", &result);
    
    return result;
}


double strtod(const char *str, char **stringPtr )
{
	int oneDecimalPoint = 1; /* Only allow doubles with one decimal point */
	
	// skip leading spaces
	while(str[0]==32)
	    str++;
	
	double result;
    sscanf(str, "%lf", &result);
    
    while(1)
    {
    	if(isdigit(str[0])==0) {
    		if( (str[0]=='.') && oneDecimalPoint==1 )
    		    oneDecimalPoint--;
    		else
			{
    			stringPtr[0] = str;
    			break;
			} 
		}
		str++;
	}
    
    return result;
}


long strtol(const char *str, char **stringPtr, int base)
{	
	// skip leading spaces
	while(str[0]==32)
	    str++;
	
	long result = 0;

	/* Used for string validation */
	char maxNum = '9';
	char minChar = '0', maxChar = '9';
	
    if(base==0)
        base=10; 
    else if(base<=10)
        maxNum = '0' + base - 1;
    else 
	{
    	minChar = 'A';
    	maxChar = 'A' + (base-11);
	}

	//Process characters in order from most significant to least significant
	while(*str)
	{
		/* break on non numeric or base character */
		if( !((*str>='0' && *str<=maxNum ) || (*str>=minChar && *str<=maxChar)) )
			break;

		// shift the number left a place
		result *= base;
		
		// add the current digit using ASCII math
		if('A' <= *str && *str <= maxChar)
			result += *str - 'A' + 10;
		else
			result += *str - '0';

		str++;
	}
    stringPtr[0] = str;
    
    return result;
}


unsigned long strtoul(const char *str, char **stringPtr, int base)
{	
	// skip leading spaces
	while(str[0]==32)
	    str++;
	
	unsigned long result = 0;

	/* Used for string validation */
	char maxNum = '9';
	char minChar = '0', maxChar = '9';
	
    if(base==0)
        base=10; 
    else if(base<=10)
        maxNum = '0' + base - 1;
    else 
	{
    	minChar = 'A';
    	maxChar = 'A' + (base-11);
	}

	//Process characters in order from most significant to least significant
	while(*str)
	{
		/* break on non numeric or base character */
		if( !((*str>='0' && *str<=maxNum ) || (*str>=minChar && *str<=maxChar)) )
			break;

		// shift the number left a place
		result *= base;
		
		// add the current digit using ASCII math
		if('A' <= *str && *str <= maxChar)
			result += *str - 'A' + 10;
		else
			result += *str - '0';

		str++;
	}
    stringPtr[0] = str;
    
    return result;
}



int isdigit( int c )
{
	if(c<48 || c >57)
	    return 0;
	return 1;
}
