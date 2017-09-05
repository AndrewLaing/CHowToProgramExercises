/*
 * Filename:    ex08_28.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        30/06/2017.
 */

#include <stdio.h>

/* Using array subscripting */
char *strcpy1( char* s1, const char *s2 );
char *strncpy1( char* s1, const char *s2, size_t n );
char *strcat1( char* s1, const char *s2 );
char *strncat1( char* s1, const char *s2, size_t n );

/* Using pointer arithmetic */
char *strcpy2( char* s1, const char *s2 );
char *strncpy2( char* s1, const char *s2, size_t n );
char *strcat2( char* s1, const char *s2 );
char *strncat2( char* s1, const char *s2, size_t n );


int main()
{   
    char s1[15], s2[20];
    printf("---- strcpy1 ----\n"); 
    printf("Value returned = '%s'\n", strcpy1(s1, "Test String") ); 
    printf("Value of s1 = '%s'\n", s1 ); 
    
    printf("\n---- strncpy1 ----\n"); 
    printf("Value returned = '%s'\n", strncpy1(s2, "Test String", 4) ); 
    printf("Value of s2 = '%s'\n", s2 ); 
    
    printf("\n---- strcat1 ----\n"); 
    printf("Value returned = '%s'\n", strcat1(s2, "added") ); 
    printf("Value of s2 = '%s'\n", s2 ); 
    
    printf("\n---- strncat1 ----\n"); 
    printf("Value returned = '%s'\n", strncat1(s2, "onto", 2) ); 
    printf("Value of s2 = '%s'\n", s2 ); 
    
    
    char s3[15], s4[20];
    printf("\n---- strcpy2 ----\n"); 
    printf("Value returned = '%s'\n", strcpy2(s3, "Test String2") ); 
    printf("Value of s3 = '%s'\n", s3 ); 
    
    printf("\n---- strncpy2 ----\n"); 
    printf("Value returned = '%s'\n", strncpy2(s4, "New String", 3) ); 
    printf("Value of s4 = '%s'\n", s4 ); 
    
    printf("\n---- strcat2 ----\n"); 
    printf("Value returned = '%s'\n", strcat1(s4, "ts") ); 
    printf("Value of s4 = '%s'\n", s4 ); 
    
    printf("\n---- strncat2 ----\n"); 
    printf("Value returned = '%s'\n", strncat2(s4, " are gorgeous", 7) ); 
    printf("Value of s4 = '%s'\n", s4 ); 
    
    return 0;
}


/* Using array subscripting */
char *strcpy1( char* s1, const char *s2 )
{
    size_t i=0;
    
    while(s2[i]!='\0') {
        s1[i]=s2[i];
        i++;
    }
        
    s1[i]='\0';
    return s1;  
}



char *strncpy1( char* s1, const char *s2, size_t n )
{
    size_t i=0;
    
    while(s2[i]!='\0' && i<n) {
        s1[i]=s2[i];
        i++;
    }
    s1[i]='\0';
    return s1;
}


char *strcat1( char* s1, const char *s2 )
{
    size_t i=0, j=0;

    while(s1[i]!='\0')
        i++;
    
    while(s2[j]!='\0')
    {
        s1[i]=s2[j];
        i++;
        j++;
    }
    
    s1[i] = '\0';
    
    return s1;  
}


char *strncat1( char* s1, const char *s2, size_t n )
{
    size_t i=0, j=0;

    while(s1[i]!='\0')
        i++;
    
    while(s2[j]!='\0' && j<n)
    {
        s1[i]=s2[j];
        i++;
        j++;
    }
    
    s1[i] = '\0';
    
    return s1;  
}


/* Using pointer arithmetic */
char *strcpy2( char* s1, const char *s2 )
{   
    char *result = s1;
    
    while(*s2!='\0')
        *s1++=*s2++;
        
    *s1='\0';
    return result;  
}


char *strncpy2( char* s1, const char *s2, size_t n )
{
    size_t i=0;
    char *result = s1;
    
    while(*s2!='\0' && i++<n)
        *s1++=*s2++;
        
    *s1='\0';
    return result;      
}

char *strcat2( char* s1, const char *s2 )
{
    char *result = s1;
    
    while(*s1!='\0')
        ;
    
    while(*s2!='\0')
        *s1++=*s2++;
        
    *s1='\0';
    return result;      
}


char *strncat2( char* s1, const char *s2, size_t n )
{
    size_t i=0;
    char *result = s1;
    
    while(*s1++!='\0')
        ;
    
    s1--;
    
    while(*s2!='\0' && i++<n)
        *s1++=*s2++;
        
    *s1='\0';
    return result;  
}

