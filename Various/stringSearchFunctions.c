/*
 * Filename:	ex08_31.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/07/2017.	
 */

#include <stdio.h>

char *strchr1( const char *, int );
size_t strcspn1( const char *, const char * );
size_t strspn1( const char *, const char * );
char *strpbrk1( const char *, const char * );
char *strrchr1( const char *, int );
char *strstr1( const char *, const char * );    /* uses strcmp2 */
char *strtok1( char *, const char * );

int main()
{	
    const char *test = "This is only a test string ok";

    printf("---- strchr1 ----\n");
    printf("result1 = %s\n", strchr1(test, 'o') );
    char *result2 = strchr1(test, '7');
    if(result2==NULL)
        printf("result2 = NULL\n");
    else
        printf("result2 != NULL\n");
        
    const char *test2 = "apy";
    size_t result = strcspn1( test, test2 );
    printf("\n---- strcspn1 ----\n");
    printf("Length of the initial segment of the\n");
    printf("string '%s' not\n", test);
	printf("containing characters from '%s'\n", test2);
	printf("is %d\n", result); 
        
    const char *test3 = "sith onT";
    result = strspn1( test, test3 );
    printf("\n---- strspn1 ----\n");
    printf("Length of the initial segment of the\n");
    printf("string '%s' only\n", test);
	printf("containing characters from '%s'\n", test3);
	printf("is %d\n", result); 
	
	
    printf("\n---- strpbrk1 ----\n");
    printf("result1 = %s\n", strpbrk(test, "lycra") );
    char *result3 = strchr1(test, "xzq");
    if(result3==NULL)
        printf("result3 = NULL\n");
    else
        printf("result3 != NULL\n");
	
	
    printf("\n---- strrchr1 ----\n");
    printf("result1 = %s\n", strrchr1(test, 's') );
    char *result4 = strrchr1(test, 'x');
    if(result4==NULL)
        printf("result4 = NULL\n");
    else
        printf("result4 != NULL\n");
	
	
    printf("\n---- strstr1 ----\n");
    printf("result1 = %s\n", strstr1(test, "tes") );
    char *result5 = strstr1(test, "frog");
    if(result5==NULL)
        printf("result5 = NULL\n");
    else
        printf("result5 != NULL\n");
	
	
    printf("\n---- strstr1 ----\n");	
    char string[] = "   This is a sentence, with 7 tokens";
    char *tokenPtr;

	printf("%s\n'%s'\n\n%s\n",
		   "The string to be tokenised is: ", string, 
		   "The tokens are:");
    
    tokenPtr = strtok1( string, " ," );
    
    while( tokenPtr != NULL ) {
    	printf("%s\n", tokenPtr);
    	tokenPtr = strtok1( NULL, " ," );
	}
	
	
 	return 0;
}


char *strchr1( const char *s, int c)
{
	while(*s!='\0') {
		if(*s==c)
		    return s;
		s++;			
	}
	return NULL;
}


size_t strcspn1( const char *s1, const char *s2 )
{
	size_t length = 0;
	char *copy = s2;
	
	while(*s1!='\0') 
	{
		while(*copy!='\0') {
		    if(*s1==*copy)
		        return length;
		    copy++;
        }
        copy = s2;
		length++;
		s1++;			
	}
	
	return length;
}


size_t strspn1( const char *s1, const char *s2 )
{
	size_t length=0, found=0;
	char *copy = s2;
	
	while(*s1!='\0') 
	{
		found=0;
		
		while(*copy!='\0') 
		{
		    if(*s1==*copy) {
		        found++;
				break;	
			}
		    copy++;
        }
        
        if(found==0)
            return length;
            
        copy = s2;
		length++;
		s1++;			
	}
	
	return length;
}


char *strpbrk1( const char *s1, const char *s2 )
{
	char *copy = s2;
	
	while(*s1!='\0') 
	{
		while(*copy!='\0') 
		{
		    if(*s1==*copy)
		        return s1;	

		    copy++;
        }

        copy = s2;
		s1++;			
	}
	
	return NULL;
}


char *strrchr1( const char *s, int c )
{
	size_t length=0;
	while(*s++!='\0') 
		length++;			
	    
	while(length-- >= 0) {
		if(*s==c)
		    return s;
		s--;
	}
	
	return NULL;
}


int *strcmp2( const char* s1, const char *s2 )
{      
    while(*s2!='\0') 
	{
		if(*s1<*s2)
		    return -1;
		else if(*s1>*s2)
		    return 1;
		s1++;
		s2++;			
	}

	return 0;	
}


char *strstr1( const char *s1, const char *s2 )
{
	while(*s1!='\0') 
	{
		if(strcmp2(s1, s2) == 0 )
		    return s1;	

		s1++;			
	}
	
	return NULL;
}


char *strtok1( char *s1, const char *s2 )
{
	static char* tokenSource;
	char *copy = s2;
	
	if(s1!=NULL)
	    tokenSource = s1;
	    
	if(tokenSource==NULL || *tokenSource=='\0')
	    return NULL;
	
	/* skip any delimiters at the beginning of the string */
	size_t found=1;
    while(found!=0)
    {
    	found=0;
    	while(*copy!='\0') {
    		
    		if(*tokenSource==*copy) {
    			found++;
    			tokenSource++;
    			break;
			}
			copy++;
		}
		copy = s2;
	}
	
	
	char *token = tokenSource;
	size_t i=0;

	/* Next look through for first delimiter or nullbyte
	 * and set to nullbyte then return token or use i to add it at index
	 * of token */
	while(*tokenSource!='\0') 
	{
		copy = s2;
		
		while(*copy!='\0') 
		{
			if(*tokenSource==*copy) {
				tokenSource++;
				token[i]='\0';
				return token;
			}
			copy++;
		}	
		
		tokenSource++;
		i++;
	}

	return token;
}

