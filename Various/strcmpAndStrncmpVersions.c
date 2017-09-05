/*
 * Filename:	ex08_30.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        30/06/2017.
 */

#include <stdio.h>

/* Using array subscripting */
int strcmp1( const char* s1, const char *s2 );
int strncmp1( const char* s1, const char *s2, size_t n );

/* Using pointer arithmetic */
int strcmp2( const char* s1, const char *s2 );
int strncmp2( const char* s1, const char *s2, size_t n );


int main()
{	
    printf("---- strcmp1 tests ----\n"); 
    const char *a = "apple";
    const char *b = "bread";
    const char *c = "apple";
    
    int result = strcmp1(a,b);
    
    if(result < 0 )
        printf("%s is less than %s\n",a, b);
    else if(result == 0 )
        printf("%s is equal to %s\n",a, b);
    else if(result > 0 )
        printf("%s is greater than %s\n",a, b);
    
	result = strcmp1(b, a);
    if(result < 0 )
        printf("%s is less than %s\n",b, a);
    else if(result == 0 )
        printf("%s is equal to %s\n",b, a);
    else if(result > 0 )
        printf("%s is greater than %s\n",b, a);
        
	result = strcmp1(a, c);
    if(result < 0 )
        printf("%s is less than %s\n",a, c);
    else if(result == 0 )
        printf("%s is equal to %s\n",a, c);
    else if(result > 0 )
        printf("%s is greater than %s\n",a, c);
        
    
    
    printf("\n---- strncmp1 tests ----\n"); 
    const char *a1 = "appletart";
    const char *b1 = "applepie";
    const char *c1 = "apply";
    
    result = strncmp1(a1,b1,5);
    
    if(result < 0 )
        printf("5 characters of %s is less than %s\n",a1, b1);
    else if(result == 0 )
        printf("5 characters of %s is equal to %s\n",a1, b1);
    else if(result > 0 )
        printf("5 characters of %s is greater than %s\n",a1, b1);
    
    result = strncmp1(a1,c1,5);
    
    if(result < 0 )
        printf("5 characters of %s is less than %s\n",a1, c1);
    else if(result == 0 )
        printf("5 characters of %s is equal to %s\n",a1, c1);
    else if(result > 0 )
        printf("5 characters of %s is greater than %s\n",a1, c1);
        
    result = strncmp1(a1,b1,6);
    
    if(result < 0 )
        printf("6 characters of %s is less than %s\n",a1, b1);
    else if(result == 0 )
        printf("6 characters of %s is equal to %s\n",a1, b1);
    else if(result > 0 )
        printf("6 characters of %s is greater than %s\n",a1, b1);
    
    
    
    printf("\n---- strcmp2 tests ----\n"); 
    
    result = strcmp2(a,b);
    
    if(result < 0 )
        printf("%s is less than %s\n",a, b);
    else if(result == 0 )
        printf("%s is equal to %s\n",a, b);
    else if(result > 0 )
        printf("%s is greater than %s\n",a, b);
    
	result = strcmp2(b, a);
    if(result < 0 )
        printf("%s is less than %s\n",b, a);
    else if(result == 0 )
        printf("%s is equal to %s\n",b, a);
    else if(result > 0 )
        printf("%s is greater than %s\n",b, a);
        
	result = strcmp2(a, c);
    if(result < 0 )
        printf("%s is less than %s\n",a, c);
    else if(result == 0 )
        printf("%s is equal to %s\n",a, c);
    else if(result > 0 )
        printf("%s is greater than %s\n",a, c);
        
        
    printf("\n---- strncmp1 tests ----\n"); 
    result = strncmp2(a1,b1,5);
    
    if(result < 0 )
        printf("5 characters of %s is less than %s\n",a1, b1);
    else if(result == 0 )
        printf("5 characters of %s is equal to %s\n",a1, b1);
    else if(result > 0 )
        printf("5 characters of %s is greater than %s\n",a1, b1);
    
    result = strncmp2(a1,c1,5);
    
    if(result < 0 )
        printf("5 characters of %s is less than %s\n",a1, c1);
    else if(result == 0 )
        printf("5 characters of %s is equal to %s\n",a1, c1);
    else if(result > 0 )
        printf("5 characters of %s is greater than %s\n",a1, c1);
        
    result = strncmp2(a1,b1,6);
    
    if(result < 0 )
        printf("6 characters of %s is less than %s\n",a1, b1);
    else if(result == 0 )
        printf("6 characters of %s is equal to %s\n",a1, b1);
    else if(result > 0 )
        printf("6 characters of %s is greater than %s\n",a1, b1);
        
 	return 0;
}


/* Using array subscripting */
int strcmp1( const char* s1, const char *s2 )
{
    size_t i=0;
    
	while(s2[i]!='\0') {
		if(s1[i]<s2[i])
		    return -1;
		else if(s1[i]>s2[i])
		    return 1;
		i++;
	}

	/* If s1 is longer than s2 and equal to its characters so far
	*  it is greater than it (filing wise)*/
    if( s1[i] != '\0')
        return 1;

	return 0;	
}


int strncmp1( const char* s1, const char *s2, size_t n )
{
    size_t i=0;
    
	while(s2[i]!='\0' && i<n)  {
		if(s1[i]<s2[i])
		    return -1;
		else if(s1[i]>s2[i])
		    return 1;
		i++;
	}

	return 0;
}


/* Using pointer arithmetic */
int strcmp2( const char* s1, const char *s2 )
{      
	while(*s2!='\0') {
		if(*s1<*s2)
		    return -1;
		else if(*s1>*s2)
		    return 1;
		s1++;
		s2++;			
	}
	/* If s1 is longer than s2 and equal to its characters so far
	*  it is greater than it (filing wise)*/
    if(*s1!='\0')
        return 1;
	return 0;	
}


int strncmp2( const char* s1, const char *s2, size_t n )
{
    size_t i=0;
    
	while(*s2!='\0' && i++<n) {
		if(*s1<*s2)
		    return -1;
		else if(*s1>*s2)
		    return 1;
		s1++;
		s2++;
	}

	return 0;		
}

