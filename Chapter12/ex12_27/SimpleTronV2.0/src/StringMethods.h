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


// Prototypes //////////////////////////////

int getLine( char [], int );

int startsWith( const char *, char );
int endsWith( const char *, char );
int endsWithSuffix(const char *, const char * );
int isOperator( char c );
void removeEndChar( char *s );

int strlen2( const char* s );
char *strcpy2( char *, const char * );
int strcmp2( const char *, const char * );

#endif

