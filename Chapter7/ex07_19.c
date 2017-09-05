/*
 * Filename:	ex07_19.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        02/06/2017.
 * Description: Simpletron Program
 * TODO - 		Todo - use overflow protected readline for input
 *                     add an ATOI (takes a pointer to int returns a status code)
 *                     add an error check which does not allow non numeric input
 */

#include <stdio.h>
#include <stdlib.h>

#define PAUSE system("pause")
#define CLEARSCREEN system("cls")
#define MEMORYSIZE 100

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

// Prototypes //////////////////////////////

int loadProgram();
void dumpMemoryAndRegisters( void );
int runProgram( void );
void loadInstruction( void );
int processInstruction( void );

int doRead( void );
int doWrite( void );
int doLoad( void );
int doStore( void );
int doAdd( void );
int doSubtract( void );
int doDivide( void );
int doMultiply( void );
int doBranch( void );
int doBranchNeg( void );
int doBranchZero( void );


// Global Variables ////////////////////////

int MEMORY[MEMORYSIZE] = {0};
int ACCUMULATOR = 0;
int INSTRUCTIONCOUNTER = 0;
int INSTRUCTIONREGISTER = 0;
int OPERATIONCODE = 0;
int OPERAND = 0;

const char *INTROTEXT =
"*** Welcome to Simpletron! ***\n"
"*** Please enter your program one instruction ***\n"
"*** (or data word) at a time. I will type the ***\n"
"*** location number and a question mark (?).  ***\n"
"*** You then type the word for that location. ***\n"
"*** Type the sentinel -99999 to stop entering ***\n"
"*** your program. ***\n";


// Methods /////////////////////////////////

int main()
{
	int validLoad;
	
	printf("%s\n", INTROTEXT);
    validLoad = loadProgram();
    
	if(validLoad == 1)
        runProgram();
            
	return 0;
}

/* loadProgram allows the user to type a prgram directly into MEMORY */
int loadProgram()
{
	int address = 0;
	int input;
	int isValidLoad = 1;
	
	printf("00 ? ");
	scanf("%d", &input);
	
	while( ( input != -99999 ) && ( address < MEMORYSIZE ) ) 
	{
		if( (input > 9999) || (input<-9999 && input != -99999)) 
		{
		    printf("\nWarning - Invalid instruction\nPlease try again!\n");
		    printf("%02d ? ", address);
		    scanf("%d", &input);
		}
		else if( address >= MEMORYSIZE )
		{
			printf("*** Fatal Error - Memory Overflow ***\n");
			PAUSE;
			isValidLoad = -1;
			input = -99999;
		}
		else
		{
			MEMORY[address++] = input;

			printf("%02d ? ", address);
			scanf("%d", &input);
		}
	}
	
	printf("*** Program loading completed ***\n");
	return isValidLoad;
}

/* Dump the current contents of the Registers and Memory to STDOUT */
void dumpMemoryAndRegisters()
{
    int i, value, row=0;
    
    CLEARSCREEN;
    
    /* Print out REGISTER Contents*/
    printf("REGISTERS:\n");
    if(ACCUMULATOR >= 0)
    	printf("accumulator:\t\t +%04d\n", ACCUMULATOR );
	else
		printf("accumulator:\t\t %05d\n", ACCUMULATOR);
    
    printf("instructionCounter:\t    %02d\n", INSTRUCTIONCOUNTER);
    
    if(INSTRUCTIONREGISTER  >= 0)
        printf("instructionRegister:\t +%04d\n", INSTRUCTIONREGISTER);
	else
		printf("instructionRegister:\t %04d\n", INSTRUCTIONREGISTER);

    printf("operationCode:\t\t    %02d\n", OPERATIONCODE);
    printf("operand:\t\t    %02d\n", OPERAND);
	 
	 
    /* Print out MEMORY Contents*/
    printf("\nMEMORY:\n");
    
    printf("%11s", "0");
    for(i=1; i<10; i++)
        printf("%7d", i);
    
    printf("\n%02d  ", row++);
    for(i=0; i<MEMORYSIZE; i++) 
	{
		value = MEMORY[i];
		if(value==0)
		    printf("%7s", "+0000");
        else
        {
        	if(value>0)
        	    printf("  %s%d", "+", MEMORY[i]);
        	else
        		printf("%7d", MEMORY[i]);
		}
    	
    	if( (i+1)%10==0 && (i+1 < MEMORYSIZE ) )
    	    printf("\n%02d  ", i+1);
	}
    printf("\n");
}

/* Execute the program currently loaded into memory */
int runProgram()
{
	int programState=1; /* O=Halt, -1=ERROR*/
	
	printf("*** Program execution begins ***\n");
	
	while( ( programState==1 ) && ( INSTRUCTIONCOUNTER < MEMORYSIZE ) ) 
	{
		loadInstruction();
		programState = processInstruction();
	}
	
	if(programState==0)
	    printf("*** Simpletron execution terminated normally ***\n");
	else
	{
		dumpMemoryAndRegisters();
		printf("*** Simpletron execution terminated abnormally at line %02d ***\n", INSTRUCTIONCOUNTER);
	}
	
	return programState;
}

/* Load the instruction pointed to by the INSTRUCTIONCOUNTER
 * into the Registers */
void loadInstruction()
{
	INSTRUCTIONREGISTER = MEMORY[INSTRUCTIONCOUNTER];
	OPERATIONCODE = INSTRUCTIONREGISTER / 100;
	OPERAND = INSTRUCTIONREGISTER % 100;
}

/* Decode and execute the currently loaded instruction */
int processInstruction()
{
	int isValidInstruction = 1;
	
	switch(OPERATIONCODE)
	{
		case READ:
			isValidInstruction = doRead();
			break;
		case WRITE:
			isValidInstruction = doWrite();
			break;
		case LOAD:
			isValidInstruction = doLoad(); 
			break;
		case STORE:
			isValidInstruction = doStore(); 
			break;
		case ADD:
			isValidInstruction = doAdd(); 
			break;
		case SUBTRACT:
			isValidInstruction = doSubtract(); 
			break;
		case DIVIDE:
			isValidInstruction = doDivide();
			break;
		case MULTIPLY:
			isValidInstruction = doMultiply(); 
			break;
		case BRANCH:
			isValidInstruction = doBranch(); 
			break;
		case BRANCHNEG:
			isValidInstruction = doBranchNeg(); 
			break;
		case BRANCHZERO:
			isValidInstruction = doBranchZero(); 
			break;
		case HALT:
			isValidInstruction = 0;
			break;
		default:
			printf("*** Unknown instruction at line %02d ***\n", INSTRUCTIONCOUNTER);
			PAUSE;
			isValidInstruction = -1;
	}
	
	return isValidInstruction;
}

/* Read from STDIN to MEMORY address OPERAND */
int doRead( void )
{
	printf("? ");
	scanf("%d", &MEMORY[OPERAND]);
	
	if(MEMORY[OPERAND]>9999 || MEMORY[OPERAND]<-9999)
	{
		printf("*** Fatal Error! Overflow at address %02d ***\n", OPERAND );
		printf("*** after executing line %02d!            ***\n", INSTRUCTIONCOUNTER );
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Write value from MEMORY address Operand to STDOUT */
int doWrite( void )
{
	printf( "%d\n", MEMORY[OPERAND] );
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Load value at MEMORY address Operand to Accumulator */
int doLoad( void )
{
	ACCUMULATOR = MEMORY[OPERAND];
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Store value in Accumulator to MEMORY address Operand */
int doStore( void )
{
	MEMORY[OPERAND] = ACCUMULATOR;
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Add value at MEMORY address Operand to Accumulator */
int doAdd( void )
{
	ACCUMULATOR += MEMORY[OPERAND];
	
	if(ACCUMULATOR>9999 || ACCUMULATOR<-9999)
	{
		printf("*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Subtract value at MEMORY address Operand from Accumulator */
int doSubtract( void )
{
	ACCUMULATOR -= MEMORY[OPERAND];
	
	if(ACCUMULATOR>9999 || ACCUMULATOR<-9999)
	{
		printf("*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Divide value in Accumulator by value at MEMORY address Operand */
int doDivide( void )
{
	if(MEMORY[OPERAND]==0)
	{
		printf("*** Attempt to Divide by Zero! ***\n");
		PAUSE;
		return -1;
	}
	else
	{
		ACCUMULATOR -= MEMORY[OPERAND];
		INSTRUCTIONCOUNTER++;
		return 1;		
	}
}

/* Multiply value in Accumulator by value at MEMORY address Operand*/
int doMultiply( void )
{
	ACCUMULATOR *= MEMORY[OPERAND];
	
	if(ACCUMULATOR>9999 || ACCUMULATOR<-9999)
	{
		printf("*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Branch to MEMORY address Operand */
int doBranch( void )
{
	INSTRUCTIONCOUNTER = OPERAND;
	return 1;
}

/* Branch to MEMORY address Operand if value in Accumulator is negative */
int doBranchNeg( void )
{
	if(ACCUMULATOR < 0)
	    INSTRUCTIONCOUNTER = OPERAND;
	else
	    INSTRUCTIONCOUNTER++;
	
	return 1;
}

/* Branch to MEMORY address Operand if value in Accumulator is zero */
int doBranchZero( void ) 
{
	if(ACCUMULATOR == 0)
	    INSTRUCTIONCOUNTER = OPERAND;
	else
	    INSTRUCTIONCOUNTER++;
	    
	return 1;
}

