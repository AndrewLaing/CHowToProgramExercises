/*
 * Filename:    SimpleCompiler.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/08/2017.
 * Description: Contains the headers and defines and imports for
 *              the Simple Compiler.
 */

#ifndef SIMPLE_COMPILER_H
#define SIMPLE_COMPILER_H

#define ADDINSTRUCTION(instruction)  if( addInstructionToMemory( instruction ) == FAIL ) \
                return FAIL;  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SMLOpCodes.h"
#include "ForLoopStack.h"
#include "IntStack.h"
#include "StringMethods.h"

#define MEMORYSIZE 1000
#define MAXLINELENGTH 100
#define MAXTOKENLENGTH 20
#define MAXTABLESIZE 100
#define NUMBEROFCOMPOPERATORS 6
#define MAXARRAYSIZE 50
#define SUCCESS 1
#define FAIL -1

/* /// CONTAINERS ///*/

struct tableEntry {
    int symbol;
    char type;
    int location;
};

struct tableEntry Table[MAXTABLESIZE];


enum ComparisonOperators {
    LTOPERATOR, GTOPERATOR, 
    LTEOPERATOR, GTEOPERATOR,
    EQOPERATOR, NEOPERATOR
};

const char compOperators[ NUMBEROFCOMPOPERATORS ][3] = { "<", ">", "<=", ">=", "==", "!=" };

ForLoopNodePtr ForLoopStackPtr;


/* Used to store string literal details so they do not need to be recreated */
char stringLiteralArray[MAXARRAYSIZE][MAXLINELENGTH];
int stringLiteralAddresses[MAXARRAYSIZE];
int numberOfStringLiterals;



/* /// PROTOTYPES /// */

void initialiseFlags( void );

void printFlags();         /* For DEBUGging*/
void printInstructions();   /* For DEBUGging*/

int addInstructionToMemory( int );
int writeInstructionsToFile( const char * );

void addLineNumberToTable( int );
int updateStringVariableAddress( char, int );
int addVariableToTable( char );
int addConstantToTable( int );
int runFirstPass( const char * );
int runSecondPass( void );
int createTokenArray( const char *, char [][ MAXTOKENLENGTH ] );
int addSymbolsToTable( char [][MAXTOKENLENGTH], int );

int getElementAddressFromStr(char [], int );

int createInputInstruction( char [][MAXTOKENLENGTH], int );
int stringLiteralExistsInMemory( const char * );
int addStringLiteralToMemory( char [][MAXTOKENLENGTH], int, int );
int createPrintInstruction( char [][MAXTOKENLENGTH], int );
int createGotoInstruction( char [][MAXTOKENLENGTH], int );
int createEndInstruction( char [][MAXTOKENLENGTH], int );
int addStringToVariableMemorySpace( char [][MAXTOKENLENGTH], int ); 
int createLetInstruction( char [][MAXTOKENLENGTH], int );
int createDimInstruction( char [][MAXTOKENLENGTH], int );
int createIfInstruction( char [][MAXTOKENLENGTH], int );
int createGosubInstruction( char [][MAXTOKENLENGTH], int );
int createReturnInstruction( char [][MAXTOKENLENGTH], int );

int findStepValueIndex( char [][MAXTOKENLENGTH], int );
int findToValueIndex( char [][MAXTOKENLENGTH], int );
int createForInstruction( char [][MAXTOKENLENGTH], int );
int createNextInstruction( char [][MAXTOKENLENGTH], int );

int createNewlineInstruction( char [][MAXTOKENLENGTH], int );
int createFirstSML( char [][MAXTOKENLENGTH], int );


void dumpTableEntries( void ); /* For DEBUGging*/
int strcmp2( const char *, const char * );
int variableExistsInTable( char );
int constantExistsInTable( int );
int lineNumberExistsInTable( int );


/* For expression evaluation (infix->postfix using stack)*/
int convertToPostfix( char [][MAXTOKENLENGTH], char [][MAXTOKENLENGTH], int, int );
int precedence( char operator1, char operator2 );


/* For if and let statements */
int evaluatePostfixExpression( char [][MAXTOKENLENGTH], int );
int calculate( int, int, char );

/* For if statements */
int getComparisonOperatorIndex( char [ ][ MAXTOKENLENGTH ], int );
int isComparisonOperator( char * );

int doLTJMP( char [][MAXTOKENLENGTH], int, int );
int doGTJMP( char [][MAXTOKENLENGTH], int, int );
int doLTEJMP( char [][MAXTOKENLENGTH], int, int );
int doGTEJMP( char [][MAXTOKENLENGTH], int, int );
int doEQJMP( char [][MAXTOKENLENGTH], int, int );
int doNEJMP( char [][MAXTOKENLENGTH], int, int );

int doSTRCMP( char [][MAXTOKENLENGTH], int, int );
int doSTREQ( char [][MAXTOKENLENGTH], int, int );

/* /// VARIABLES /// */

int TABLEPOSITION = 0;
int Flags[MEMORYSIZE];

int MEMORY[MEMORYSIZE] = {0}; // sml instructions stored here

int PREVIOUSLINENUMBER = 0;
int INSTRUCTIONCOUNTER = 0;
int VARCONSTADDRESS = MEMORYSIZE-1;    /* The position in the Simpletron Memory 
                              * where a Variable or Constant can be placed */


#endif

