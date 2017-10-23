/*
 * Filename:    StringMethods.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/08/2017.
 * Description: Various string and character related methods.
 */

#include "StringMethods.h"


/**
 * The function getline reads in a string of maximum length maxLength into 
 * the character array s, and returns the length of the string.
 * @param s[] A character array to store the string in.
 * @param maxLength The maximum length of the string.
 * @return The length of the string stored in the array.
 */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    fflush(stdin);  /* Clear any overflow*/
    
    return i;   
}


/**
 * The function startsWith returns 1 if the string passed to it starts
 * with the character c, otherwise false.
 * @param *s The string to test.
 * @param c The character to test the string for.
 * @return 1 if the string passed to it starts with the character c, 
 *           otherwise false.
 */
int startsWith( const char *s, char c )
{
    if(s!=NULL)
        return s[0] == c;
    return 0;
}


/**
 * The function endsWith returns 1 if the string passed to it ends
 * with the character c, otherwise false.
 * @param *s The string to test.
 * @param c The character to test the string for.
 * @return 1 if the string passed to it ends with the character c, 
 *           otherwise false.
 */
int endsWith( const char *s, char c )
{
    if(s==NULL)
       return 0;
    int i=0;
    
    while(s[i]!='\0')
        i++;
    
    return s[--i] == c;
}



/**
 * The function endsWith returns 1 if the string passed to it ends
 * with the suffix 'suffix', otherwise false.
 * @param *s The string to test.
 * @param suffix The suffix to test the string for.
 * @return 1 if the string passed to it ends with suffix, 
 *           otherwise false.
 */
int endsWithSuffix(const char *s, const char *suffix)
{
  int sLength = strlen(s);
  int suffixLength = strlen(suffix);

  return (sLength >= suffixLength) &&
         (strcmp(s + (sLength-suffixLength), suffix) == 0);
}


/**
 * The function isOperator tests whether the character c is an 
 * allowed operator.
 * @param c A character to test.
 * @return 1 if the character is an operator, otherwise 0.
 */
int isOperator( char c )
{
    int result = 0;

    switch( c )
    {
        case '^': case '*': case '/': case '%': case '+': 
        case '-': case '=': case '!': case '<': case '>':
            result = 1;
            break;
        default:
            break;
    }

    return result;
}



/**
 * The function removeFirstChar removes the first character from the string s. 
 * @param s A pointer to a string.
 */
void removeFirstChar( char *s1, const char *s2 )
{    
    size_t i=0, j=1;
    
    while( s2[j]!='\0' ) {
        s1[i]=s2[j];
        i++; j++;
    }
    
    s1[i]='\0';
}


/**
 * The function removeEndChar removes the final character from the string s. 
 * @param s A pointer to a string.
 */
void removeEndChar( char *s )
{
    if(s==NULL)
       return;
    int i=0;
    
    while(s[i]!='\0')
        i++;
    
    s[--i] = '\0';
}


/**
 * The function strToInt converts a string to an integer.
 * @param str A pointer to the string to convert.
 * @return The string converted to an integer.
 */
int strToInt(const char *str)
{
    int result;
    sscanf(str, "%d", &result);

    return result;
}


/***
 * The function removeQuotes removes the double quotes from 
 * a string, copying it from s2 into s1. If the operation
 * was successful it returns 0, otherwise -1.
 * @param s1 A character array to store the stripped string
 * @oaram s2 A string containing double quotes as the first 
             and last characters.
 * @return 0 if the operation was successful, otherwise -1. 
 */
int removeQuotes( char *s1, const char *s2 )
{
    if(s2[0]!='"')
        return -1;
    
    size_t i=0, j=1;
    
    while(s2[j]!='"' && s2[j]!='\0' ) {
        s1[i]=s2[j];
        i++; j++;
    }
    
    s1[i]='\0';
    
    return 0;  
}


/**
 * The function strlen2 returns the length of the string s. 
 * @param s A pointer to a string.
 * @return The length of the string s.
 */
int strlen2( const char* s )
{
    int i=0;
    
    while(*s++!='\0')
        i++;

    return i;
}


/**
 * The function strcpy2 copies the string s2 into s1 and returns a
 * pointer to the start of s1. 
 * @param s1 A pointer to the destination string.
 * @param s2 A pointer to the source string.
 * @return A pointer to the start of s1.
 */
char *strcpy2( char* s1, const char *s2 )
{   
    char *result = s1;
    
    while(*s2!='\0')
        *s1++=*s2++;
        
    *s1='\0';
    return result;  
}


/**
 * The function strcat2 copies the string s2 onto the end
 * of s1 and returns a pointer to the start of s1. 
 * @param s1 A pointer to the string to be concatenated to.
 * @param s2 A pointer to the string to concatenate to s1.
 * @return A pointer to the start of s1.
 */
char *strcat2( char *s1, const char *s2 )
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


/**
 * The function strcmp2 compares the string s1 with the string s2,and 
 * returns 0 if the strings are equal, -1 if s1 is less than s2, or 
 * 1 if s1 is greater than s2.
 * @param s1 A pointer to a string.
 * @param s2 A pointer to a string.
 * @return 0 if the strings are equal, -1 if s1 is less than s2, or 
 *         1 if s1 is greater than s2.
 */
int strcmp2( const char *s1, const char *s2 )
{      
    while(*s2!='\0') {
        if(*s1<*s2)
            return -1;
        else if(*s1>*s2)
            return 1;
        s1++;
        s2++;           
    }

    if(*s1!='\0')
        return 1;
    return 0;   
}


/**
 * The function strToLowercase converts the characters in
 * the char array str to lowercase.
 * @param str A char array to convert to lowercase.
 */
void strToLowercase( char str[] )
{
    int i;
    for( i=0; str[i]!='\0'; i++)
        str[i] = tolower(str[i]);
}


/**
 * The function strToLowercase converts the characters in
 * the char array str to lowercase.
 * @param strPtr A pointer to a char array to convert to lowercase.
 */
char * strToLowercase1( char *strPtr )
{
    char *retPtr = strPtr;
    
    for( ; *strPtr!='\0'; strPtr++)
        *strPtr = tolower(*strPtr);
    
    return retPtr;
}
