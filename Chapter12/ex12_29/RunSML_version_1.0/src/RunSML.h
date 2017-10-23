/*
 * Filename:    RunSML.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/10/2017.
 * Description: Headers for RunSML main file.
 */

#ifndef RUN_SML_H
#define RUN_SML_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "SMLOpCodes.h"
#include "StringMethods.h"


#define PAUSE system("pause")
#define CLEARSCREEN system("cls")
#define MEMORYSIZE 1000
#define WORDLENGTH 9         /* Allows for sentinel value and nullbyte */
#define MAXFLOATLEN 15       /* Allows for negative, decimal point and nullbyte */
#define MAXSTRINGLEN MEMORYSIZE/2
#define LINELENGTH 100
#define MAXLINELENGTH 100


// Prototypes //////////////////////////////

int getInteger( void );
double getDouble( void );
void doubleToString( char [], double );
void intToString( char [], int );
int isValidInt( const char * );

void splitDouble( double, int [2] );
double reconstructDouble( int [2] );

void clearMemory( void );
int addInstructionToMemory( int, int );
void loadCodeFromFile( char [ MAXLINELENGTH ]  );
int runProgram( void );
void loadInstruction( void );
int processInstruction( void );

/* INSTRUCTION METHODS */
int doRead( void );
int doWrite( void );
int doNewLine( void );
int doReadFloat( void );
int doWriteFloat( void );
int doReadString( void );
int doWriteString( void );

int doLoad( void );
int doStore( void );
int doLoadFloat( void );
int doStoreFloat( void );

int doAdd( void );
int doSubtract( void );
int doDivide( void );
int doMultiply( void );
int doModulus( void );
int doExponentiation( void );
int doAddFloat( void );
int doSubtractFloat( void );
int doDivideFloat( void );
int doMultiplyFloat( void );
int doModulusFloat( void );

int doBranch( void );
int doBranchNeg( void );
int doBranchZero( void );
int doBranchPos( void );

// Global Variables ////////////////////////

int MEMORY[MEMORYSIZE] = {0};

int ACCUMULATOR = 0;
float FLTACCUMULATOR = 0;

int INSTRUCTIONCOUNTER = 0;
int INSTRUCTIONREGISTER = 0;
int OPERATIONCODE = 0;
int OPERAND = 0;


#endif

