/*
 * Filename:    SMLOpCodes.h
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/08/2017.
 * Description: Contains the Op Codes for SML instructions.
 */

#ifndef SMLOPCODES_H
#define SMLOPCODES_H


#define READ 10
#define WRITE 11
#define NEWLINE 12
#define READFLOAT 13
#define WRITEFLOAT 14
#define READSTRING 15
#define WRITESTRING 16

#define LOAD 20
#define STORE 21
#define LOADFLOAT 22
#define STOREFLOAT 23

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define MODULUS 34
#define EXPONENTIATION 35
#define ADDFLOAT 36
#define SUBTRACTFLOAT 37
#define DIVIDEFLOAT 38
#define MULTIPLYFLOAT 39
#define MODULUSFLOAT 40

#define BRANCH 50
#define BRANCHNEG 51
#define BRANCHZERO 52
#define BRANCHPOS 53
#define HALT 54

#endif

