/*
 * Filename:    SimpleTron.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/09/2017.
 * Description: Headers for the SimpleTron.
 */

#ifndef SIMPLETRON_H
#define SIMPLETRON_H


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

// Prototypes //////////////////////////////

void mainMenu( void );

int getInteger( void );
double getDouble( void );
void doubleToString( char [], double );
void intToString( char [], int );
int isValidInt( const char * );

void splitDouble( double, int [2] );
double reconstructDouble( int [2] );

void clearMemory( void );
int addInstructionToMemory( int, int );
int loadProgram( void );
void loadCodeFromFile( void );
void dumpMemoryAndRegistersToFile( void );
void dumpMemoryAndRegistersToScreen( void );
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

const char *INTROTEXT =
"***************************************\n"
"***                                 ***\n"
"***    Welcome to the Simpletron    ***\n"
"***         SML Interpreter         ***\n"
"***                                 ***\n"
"***************************************\n";



const char *MENU =
"***************************************\n"
"***         Simpletron MENU         ***\n"
"***************************************\n"
"*** 1: Type program into Memory.    ***\n"
"*** 2: Load file into Memory.       ***\n"
"*** 3: Execute Loaded Program.      ***\n"
"*** 4: Write Memory and Registers   ***\n"
"***    out to file.                 ***\n"
"*** 5: Write Memory and Registers   ***\n"
"***    to Screen.                   ***\n"
"*** 6: Display list of Opcodes.     ***\n"
"*** 0: EXIT.                        ***\n"
"***************************************\n"
"Enter choice ? ";


const char *OPCODELIST =
"***************************************\n"
"***         LIST OF OPCODES         ***\n"
"***************************************\n"
"*** Input and Output Operations     ***\n"
"*** ------------------------------- ***\n"
"*** 10 READ                         ***\n"
"*** 11 WRITE                        ***\n"
"*** 12 NEWLINE                      ***\n"
"*** 13 READFLOAT                    ***\n"
"*** 14 WRITEFLOAT                   ***\n"
"*** 15 READSTRING                   ***\n"
"*** 16 WRITESTRING                  ***\n"
"*** ------------------------------- ***\n"
"*** Memory Operations               ***\n"
"*** ------------------------------- ***\n"
"*** 20 LOAD                         ***\n"
"*** 21 STORE                        ***\n"
"*** 22 LOADFLOAT                    ***\n"
"*** 23 STOREFLOAT                   ***\n"
"*** ------------------------------- ***\n"
"*** Math Operations                 ***\n"
"*** ------------------------------- ***\n"
"*** 30 ADD                          ***\n"
"*** 31 SUBTRACT                     ***\n"
"*** 32 DIVIDE                       ***\n"
"*** 33 MULTIPLY                     ***\n"
"*** 34 MODULUS                      ***\n"
"*** 35 EXPONENTIATION               ***\n"
"*** 36 ADDFLOAT                     ***\n"
"*** 37 SUBTRACTFLOAT                ***\n"
"*** 38 DIVIDEFLOAT                  ***\n" 
"*** 39 MULTIPLYFLOAT                ***\n"
"*** 40 MODULUSFLOAT                 ***\n"
"*** ------------------------------- ***\n"
"*** Program Flow Operations         ***\n"
"*** ------------------------------- ***\n"
"*** 50 BRANCH                       ***\n" 
"*** 51 BRANCHNEG                    ***\n"
"*** 52 BRANCHZERO                   ***\n"
"*** 53 BRANCHPOS                    ***\n"
"*** 54 HALT                         ***\n" 
"***************************************\n\n";

#endif

