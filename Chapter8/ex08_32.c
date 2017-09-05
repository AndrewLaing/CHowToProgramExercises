/*
 * Filename:    ex08_32.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        02/07/2017.
 */

#include <stdio.h>

void *memcpy1( void *, const void *, size_t );
void *memmove1( void *, const void *, size_t );
int memcmp1( const void *, const void *, size_t );
void *memchr1( const void *, int, size_t );
void *memset1( void *, int, size_t );

int main()
{   
    char *test = "This is only a test string ok";
    char result[] = "The original string was longer";

    printf("---- memcpy1 ----\n");
    printf("memcpy1( result, test, 19 ) = %s\n", (char *)memcpy1( result, test, 19 ));
    printf("result = %s\n", result);
    
    /* This could cause undefined behaviour */
    printf("\nmemcpy1( result+2, result, 6 ) = %s\n", (char *)memcpy1( result+2, result, 6 ));
    printf("result = %s\n", result);
    
    printf("\n");
    
    
    char *test1 = "This is only a test string ok";
    char result1[] = "The original string was longer";

    printf("---- memmove1 ----\n");
    printf("memmove1( result, test, 19 ) = %s\n", (char *)memmove1( result1, test1, 19 ));
    printf("result = %s\n", result1);
    
    /* This could cause undefined behaviour */
    printf("\nmemmove1( result+2, result, 6 ) = %s\n", (char *)memmove1( result1+2, result1, 6 ));
    printf("result+2 = %s\n", result1+2);
    printf("result   = %s\n", result1);
    
    printf("\n");
    
    printf("---- memcmp1 tests ----\n"); 
    const char *a1 = "appletart";
    const char *b1 = "applepie";
    const char *c1 = "apply";
    
    int result2 = memcmp1(a1,b1,5);
    
    if(result2 < 0 )
        printf("5 characters of %s is less than %s\n",a1, b1);
    else if(result2 == 0 )
        printf("5 characters of %s is equal to %s\n",a1, b1);
    else if(result2 > 0 )
        printf("5 characters of %s is greater than %s\n",a1, b1);
    
    result2 = memcmp1(a1,c1,5);
    
    if(result2 < 0 )
        printf("5 characters of %s is less than %s\n",a1, c1);
    else if(result2 == 0 )
        printf("5 characters of %s is equal to %s\n",a1, c1);
    else if(result2 > 0 )
        printf("5 characters of %s is greater than %s\n",a1, c1);
        
    result2 = memcmp1(a1,b1,6);
    
    if(result2 < 0 )
        printf("6 characters of %s is less than %s\n",a1, b1);
    else if(result2 == 0 )
        printf("6 characters of %s is equal to %s\n",a1, b1);
    else if(result2 > 0 )
        printf("6 characters of %s is greater than %s\n",a1, b1);
        
    printf("\n");
    
    const char *test2 = "This is only a test string ok";

    printf("---- memchr1 ----\n");
    printf("memchr1(test2, 'o', 29) = %s\n", (char *)memchr1(test2, 'o', 29) );
    char *result3 = memchr1(test2, '7', 29);
    if(result3==NULL)
        printf("memchr1(test2, '7', 29) = NULL\n");
    else
        printf("memchr1(test2, '7', 29) != NULL\n");
            
    printf("\n");
    
    
    char test3[] = "This is only a test string ok";

    printf("---- memset1 ----\n");
    printf("memset1(test3, 'A', 12) = %s\n", (char *)memset1(test3, 'A', 12) );
    printf("test3 = %s\n", test3);
    
    return 0;
}


void *memcpy1( void *s1, const void *s2, size_t n )
{
    /* Cannot dereference a void pointer so cast contents to
     * an unsigned char pointer which allows it to copy
     * one byte at a time from unknown data types */
    const unsigned char *toCopy = (const unsigned char *)s2;
    unsigned char *result = (unsigned char *)s1;
    
    for( ; n > 0; n-- ) 
        *result++ = *toCopy++;
        
    return s1;
}


/* memmove works even if the objects overlap */
void *memmove1( void *s1, const void *s2, size_t n)
{
    unsigned char temp[n];
    memcpy1( temp, s2, n );
    
    unsigned char *result = (unsigned char *)s1;
    size_t i;
    for(i=0 ; n > 0; n--, i++ ) 
        *result++ = temp[i];
        
    return s1;
    
}


int memcmp1( const void *s1, const void *s2, size_t n)
{
    /* Use copies because cannot dereference void pointers */
    const unsigned char *s1Copy = (const unsigned char *)s1;
    const unsigned char *s2Copy = (const unsigned char *)s2;
    
    for( ; n > 0; n-- ) 
    {
        if(*s1Copy < *s2Copy)
            return -1;
        else if(*s1Copy > *s2Copy)
            return 1; 
            
        s1Copy++;
        s2Copy++;
    }
       
    return 0; 
}


void *memchr1( const void *s, int c, size_t n )
{
    /* Use copies because cannot dereference void pointers */
    const unsigned char *sCopy = (const unsigned char *)s;
    
    for( ; n > 0; n-- ) 
    {
        if(*sCopy==c)
            return sCopy;
        sCopy++;            
    }
    return NULL;
}


void *memset1( void *s, int c, size_t n )
{
    /* Use copies because cannot dereference void pointers */
    unsigned char *sCopy = (unsigned char *)s;
    
    for( ; n > 0; n-- ) {
        *sCopy++=c;
    }               
    
    return s;
}
