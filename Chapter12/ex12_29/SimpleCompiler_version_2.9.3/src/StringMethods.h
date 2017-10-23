/*
 * Filename:    StringMethods.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/08/2017.
 * Description: Various string and character related methods.
 */


#ifndef STRING_METHODS_H
#define STRING_METHODS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "IntStack.h"


int getLine( char [], int );

int startsWith( const char *, char );
int endsWith( const char *, char );
int endsWithSuffix(const char *s, const char *);
int isOperator( char c );
void removeFirstChar( char *, const char * );
void removeEndChar( char *s );
int strToInt( const char * );
int removeQuotes( char *, const char * );

int strlen2( const char* s );
char *strcpy2( char *, const char * );
char *strcat2( char *, const char * );
int strcmp2( const char *, const char * );
void strToLowercase( char [] );
char * strToLowercase1( char * );


#endif

