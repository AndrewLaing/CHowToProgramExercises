/*
 * Filename:	ex11_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        30/07/2017.
 * Description: Simpletron Interpreter		
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PAUSE system("pause")
#define CLEARSCREEN system("cls")
#define MEMORYSIZE 1000
#define WORDLENGTH 9         /* Allows for sentinel value and nullbyte */
#define MAXFLOATLEN 15       /* Allows for negative, decimal point and nullbyte */

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
#define HALT 53

// Prototypes //////////////////////////////

void mainMenu( void );

int getLine( char [], int );
int getInteger( void );
double getDouble( void );
void doubleToString(char [], double );
void intToString(char [], int );
int stringToInt(char []);

void splitDouble(double, int [2] );
double reconstructDouble(int [2]);

int isHexString(char []);
void getHexString(char []);

int loadProgram();
void dumpMemoryAndRegisters( void );
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


// Global Variables ////////////////////////

int MEMORY[MEMORYSIZE] = {0};
int ACCUMULATOR = 0;

float FLTACCUMULATOR = 0;

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
"*** Type the sentinel -9999999 to stop entering ***\n"
"*** your program. ***\n";


const char *MENU =
"***************************************\n"
"***         Simpletron MENU         ***\n"
"***************************************\n"
"*** 1: Load program into Memory     ***\n"
"*** 2: Execute Loaded Program       ***\n"
"*** 3: Dump Memory and Registers    ***\n"
//"*** 4: Edit Memory Location         ***\n"
"*** 0: EXIT                         ***\n"
"***************************************\n"
"Enter choice ? ";


// Methods /////////////////////////////////

int main()
{
	printf("%s\n", INTROTEXT);
	PAUSE;

    mainMenu();
    PAUSE;
    
	return 0;
}


void mainMenu()
{
	char choice, c;
	int showMenu = 1;
	while(showMenu == 1)
	{
		CLEARSCREEN;
		printf("%s", MENU);
		
		/* Get input and consume any other characters */
		choice = getchar();
		while( (c = getchar()) != EOF && c != '\n') ;
		
		switch(choice)
		{
			case '1':
				loadProgram();
				break;
			case '2':
	            runProgram();
	            break;
			case '3':
				dumpMemoryAndRegisters();
				break;
			case '4':
				printf("Not implemented yet.\n");
				break;
			case '0':
				printf("QUITTING\n");
				return;
				break;
			default:
				printf("\n*** Invalid option ***\n");
				break;
		}
		fflush(stdin);
		PAUSE;
	}
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
	int c, i=0;
	
	while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
	    s[i++]=c;

	if(c=='\n')
	    s[i++]=c;
	s[i] = '\0';
	
	/* Clear any overflow*/
	fflush(stdin);
	
	return i;	
}

/* Returns a valid WORDLENGTH integer, sentinel value, or Error code */
int getInteger()
{
	char str[WORDLENGTH];
	int result=0;
	
	/* Input a string */
    getLine(str, WORDLENGTH);
	
	/* Convert to an integer */
    sscanf(str, "%d", &result);

	/* If number is out of bounds return Error code */  
	if( (result<-999999 && result!=-9999999) || (result > 999999) )
		return -8888888;

	return result;
}


/* Returns a valid double, sentinel value, or Error code */
double getDouble()
{
	char str[MAXFLOATLEN];
	double result;
	
	/* Input a string */
    getLine(str, MAXFLOATLEN);
	
	/* Convert to a float */
    sscanf(str, "%lf", &result); /* Note lf flag for double (long float)*/
	
	int test = result;
	/* If number is out of bounds return Error code */  
	if( (test<-999999 && test!=-9999999) || (test > 999999) )
		return -8888888;
	
	return result;
}

/* Convert a double to a string */
void doubleToString(char s[], double num)
{
	sprintf(s, "%lf", num);
}

/* Convert an Integer to a string */
void intToString(char s[], int num)
{
	sprintf(s, "%d", num);
}


/* Convert a char array to an integer */
int stringToInt(char str[])
{
	int result;
    sscanf(str, "%d", &result);

	/* If number is out of bounds return Error code */  
	if( (result<-999999 && result!=-9999999) || (result > 999999) )
		return -8888888;

	return result;
}



/* Splits a double into lhs and rhs of decimal point integers */
void splitDouble(double d, int sides[2])
{
	sides[0] = d;
	sides[1] = (1+( d-sides[0] ))*1000000;
}


/* Create a double from two integers representing the lhs and rhs
 * of the decimal point */
double reconstructDouble(int sides[2])
{
	double reconstructed = sides[0];
	reconstructed += (sides[1]/1000000.0) - 1;
	return reconstructed;
}


/* loadProgram allows the user to type a program directly into MEMORY */
int loadProgram()
{
	int address = 0;
	int input;
	int isValidLoad = 1;
	printf("*** Type in the code or -9999999 to stop ***\n\n");
	printf("00 ? ");
	input = getInteger();
	
	while( ( input != -9999999 ) && ( address < MEMORYSIZE ) ) 
	{
		if( (input > 999999) || (input<-999999 && input != -9999999)) 
		{
		    printf("\nWarning - Invalid instruction\nPlease try again!\n");
		    printf("%02d ? ", address);
		    scanf("%d", &input);
		}
		else if( address >= MEMORYSIZE )
		{
			printf("\n*** Fatal Error - Memory Overflow ***\n");
			PAUSE;
			isValidLoad = -1;
			input = -9999999;
		}
		else
		{
			MEMORY[address++] = input;

			printf("%02d ? ", address);
			scanf("%d", &input);
		}
	}
	
	printf("\n*** Program loading completed ***\n");
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
    	printf("accumulator:\t\t   +%06d\n", ACCUMULATOR );
	else
		printf("accumulator:\t\t   %06d\n", ACCUMULATOR);
		
    if(FLTACCUMULATOR >= 0)
    	printf("float accumulator:\t +%7.6f\n", FLTACCUMULATOR );
	else
		printf("float accumulator:\t %7.6f\n", FLTACCUMULATOR );	
    
    printf("instructionCounter:\t      %04d\n", INSTRUCTIONCOUNTER);
    
    if(INSTRUCTIONREGISTER  >= 0)
        printf("instructionRegister:\t   +%06d\n", INSTRUCTIONREGISTER);
	else
		printf("instructionRegister:\t   %06d\n", INSTRUCTIONREGISTER);

    printf("operationCode:\t\t        %02d\n", OPERATIONCODE);
    printf("operand:\t\t    %06d\n", OPERAND);
	 
	 
    /* Print out MEMORY Contents*/
    printf("\nMEMORY:\n");
    
    printf("%13s", "0");
    for(i=1; i<10; i++)
        printf("%9d", i);
    
    printf("\n%03d  ", row++);
    for(i=0; i<MEMORYSIZE; i++) 
	{
		value = MEMORY[i];
		if(value==0)
		    printf("%8s", " +000000 ");
        else
        {
        	if(value>0)
        	    printf(" %s%06d ", "+", MEMORY[i]);
        	else
        		printf("  %06d ", MEMORY[i]);
		}
    	
    	if( (i+1)%10==0 && (i+1 < MEMORYSIZE ) )
    	    printf("\n%03d  ", i+1);
	}
    printf("\n");
}


/* Execute the program currently loaded into memory */
int runProgram()
{
	int programState=1; /* O=Halt, -1=ERROR*/
	
	printf("\n*** Program execution begins ***\n");
	
	while( ( programState==1 ) && ( INSTRUCTIONCOUNTER < MEMORYSIZE ) ) 
	{
		loadInstruction();
		programState = processInstruction();
	}
	
	if(programState==0) {
		printf("\n*** Simpletron execution terminated normally ***\n");
		INSTRUCTIONCOUNTER = 0;
	}
	    
	else
	{
		dumpMemoryAndRegisters();
		printf("\n*** Simpletron execution terminated abnormally at line %02d ***\n", INSTRUCTIONCOUNTER);
		INSTRUCTIONCOUNTER = 0;
	}
	
	return programState;
}

/* Load the instruction pointed to by the INSTRUCTIONCOUNTER
 * into the Registers */
void loadInstruction()
{
	
	INSTRUCTIONREGISTER = MEMORY[INSTRUCTIONCOUNTER];
	OPERATIONCODE = INSTRUCTIONREGISTER / 10000;
	OPERAND = INSTRUCTIONREGISTER % 10000;
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
		case NEWLINE:
			isValidInstruction = doNewLine();
			break;
		case READFLOAT:
			isValidInstruction = doReadFloat();
			break;
		case WRITEFLOAT:
			isValidInstruction = doWriteFloat();
			break;
		case READSTRING:
			isValidInstruction = doReadString();
			break;
		case WRITESTRING:
			isValidInstruction = doWriteString();
			break;
		case LOAD:
			isValidInstruction = doLoad(); 
			break;
		case STORE:
			isValidInstruction = doStore(); 
			break;
		case LOADFLOAT:
			isValidInstruction = doLoadFloat(); 
			break;
		case STOREFLOAT:
			isValidInstruction = doStoreFloat(); 
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
		case MODULUS:
			isValidInstruction = doModulus(); 
			break;
		case EXPONENTIATION:
			isValidInstruction = doExponentiation(); 
			break;
		case ADDFLOAT:
			isValidInstruction = doAddFloat(); 
			break;
		case SUBTRACTFLOAT:
			isValidInstruction = doSubtractFloat(); 
			break;
		case DIVIDEFLOAT:
			isValidInstruction = doDivideFloat();
			break;
		case MULTIPLYFLOAT:
			isValidInstruction = doMultiplyFloat(); 
			break;
		case MODULUSFLOAT:
			isValidInstruction = doModulusFloat(); 
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
			printf("\n*** Unknown instruction at line %02d ***\n", INSTRUCTIONCOUNTER);
			PAUSE;
			isValidInstruction = -1;
	}
	
	return isValidInstruction;
}


/* Read from STDIN to MEMORY address OPERAND */
int doRead( void )
{
	printf("? ");
	
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	scanf("%d", &MEMORY[OPERAND]);
	
	if(MEMORY[OPERAND]>999999 || MEMORY[OPERAND]<-999999)
	{
		printf("\n*** Fatal Error! Overflow at address %04d ***\n", OPERAND );
		printf("*** after executing line %04d!            ***\n", INSTRUCTIONCOUNTER );
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Write value from MEMORY address Operand to STDOUT */
int doWrite( void )
{
	
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to write from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	printf( "%d", MEMORY[OPERAND] );
	INSTRUCTIONCOUNTER++;
	return 1;
}


int doNewLine( void )
{
	printf("\n");
	INSTRUCTIONCOUNTER++;
	return 1;
}


int doReadFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	int sides[2] = { 0, 0 };
	double f = getDouble();
	splitDouble(f, sides);
	MEMORY[OPERAND] = sides[0];
	MEMORY[OPERAND+1] = sides[1];	 
	
	INSTRUCTIONCOUNTER++;
	return 1;
}


int doWriteFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to load from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	
	printf("%f", f);
	
	INSTRUCTIONCOUNTER++;
	return 1;
}


/* doReadString reads a string into memory,
 * String characters are stored as half words, the first half word
 * in the strings memory location is its length */
int doReadString( void )
{
	/* First check that the memory location is valid */
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	char str[MEMORYSIZE/2];
	
	printf("? ");
	int strSize = getLine( str, MEMORYSIZE/2 )-1;
	int i, temp;
	
    /* Check that there is enough space to store the string into memory */
	if((OPERAND + strSize)>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
		       OPERAND+strSize, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
    /* Store the string into memory as half words*/
	int address = OPERAND;

	temp = strSize*1000;
	for(i=0; i<strSize; i++)
	{
		if(i%2==0) {
			temp+=(int)str[i];
			MEMORY[address++] = temp;
		}
		else
			temp = (int)str[i] * 1000;
	}
	
	if(i%2==0)
    	MEMORY[address++] = temp;
    	
   	INSTRUCTIONCOUNTER++;
    return 1;
}


int doWriteString( void )
{
	/* First check that the memory location is valid */
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	int address = OPERAND;

	int first = MEMORY[address++];
	int strSize = first/1000;
	
	/* Print the first character */
	if(strSize>0)
	    printf("%c", first-(strSize*1000));
	    
	int i, temp, temp1;
	
    /* Convert the half words back to characters and print them */
	for(i=1; i<strSize; i+=2)
	{
		temp = MEMORY[address++];
		temp1 = temp/1000;
		printf("%c", temp1);
		temp = temp-(temp1*1000);
		if(temp>0)
		    printf("%c", temp);
	}
	
    INSTRUCTIONCOUNTER++;
	return 1;
}


/* Load value at MEMORY address Operand to Accumulator */
int doLoad( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to load from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	ACCUMULATOR = MEMORY[OPERAND];
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Store value in Accumulator to MEMORY address Operand */
int doStore( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to store to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	MEMORY[OPERAND] = ACCUMULATOR;
	INSTRUCTIONCOUNTER++;
	return 1;
}


int doLoadFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to load from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	FLTACCUMULATOR = f;
	INSTRUCTIONCOUNTER++;
	return 1;
}


int doStoreFloat( void )
{
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to store to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	int sides[2];
	/* Split the value in the float accumulator and store
	 * it in two consecutive memory addresses */
	splitDouble(FLTACCUMULATOR, sides); 
	MEMORY[OPERAND]   = sides[0];
	MEMORY[OPERAND+1] = sides[1];

	INSTRUCTIONCOUNTER++;
	return 1;
}


/* Add value at MEMORY address Operand to Accumulator */
int doAdd( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	ACCUMULATOR += MEMORY[OPERAND];
	
	if(ACCUMULATOR>999999 || ACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}


/* Subtract value at MEMORY address Operand from Accumulator */
int doSubtract( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	ACCUMULATOR -= MEMORY[OPERAND];
	
	if(ACCUMULATOR>999999 || ACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}

/* Divide value in Accumulator by value at MEMORY address Operand */
int doDivide( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	if(MEMORY[OPERAND]==0)
	{
		printf("\n*** Attempt to Divide by Zero! ***\n");
		PAUSE;
		return -1;
	}
	else
	{
		ACCUMULATOR /= MEMORY[OPERAND];
		INSTRUCTIONCOUNTER++;
		return 1;		
	}
}

/* Multiply value in Accumulator by value at MEMORY address Operand*/
int doMultiply( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	ACCUMULATOR *= MEMORY[OPERAND];
	
	if(ACCUMULATOR>999999 || ACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}


/* Modulo value in Accumulator by value at MEMORY address Operand */
int doModulus( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	if(MEMORY[OPERAND]==0)
	{
		printf("\n*** Attempt to Modulo by Zero! ***\n");
		PAUSE;
		return -1;
	}
	else
	{
		ACCUMULATOR = ACCUMULATOR % MEMORY[OPERAND];
		INSTRUCTIONCOUNTER++;
		return 1;		
	}
}

/* Raise value in Accumulator to the power of value at MEMORY address Operand */
int doExponentiation( void )
{	
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}

	int i;
	int original = ACCUMULATOR;
	for(i=1; i<MEMORY[OPERAND]; i++)
	    ACCUMULATOR *= original;
	
	if(ACCUMULATOR>999999 || ACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;
	return 1;
}


int doAddFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	
	FLTACCUMULATOR += f;
	
	if(FLTACCUMULATOR>999999 || FLTACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;

	return 1;
}


int doSubtractFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	
	FLTACCUMULATOR -= f;
	
	if(FLTACCUMULATOR>999999 || FLTACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;

	return 1;
}


int doDivideFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	
	if(f==0.0)
	{
		printf("\n*** Attempt to Divide by Zero! ***\n");
		PAUSE;
		return -1;
	}
	
	FLTACCUMULATOR /= f;
	
	if(FLTACCUMULATOR>999999 || FLTACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;

	return 1;
}


int doMultiplyFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	
	FLTACCUMULATOR *= f;
	
	if(FLTACCUMULATOR>999999 || FLTACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;

	return 1;
}


int doModulusFloat( void )
{
	/* If there are not two words to load from memory */
	if(OPERAND>MEMORYSIZE-2) {
		printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
		
	int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
	double f = reconstructDouble(sides);
	
	if(f==0.0)
	{
		printf("\n*** Attempt to Modulo by Zero! ***\n");
		PAUSE;
		return -1;
	}
	
	FLTACCUMULATOR = fmod(FLTACCUMULATOR, f);
	
	if(FLTACCUMULATOR>999999 || FLTACCUMULATOR<-999999)
	{
		printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
		PAUSE;
		return -1;
	}
	
	INSTRUCTIONCOUNTER++;

	return 1;
}


/* Branch to MEMORY address Operand */
int doBranch( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	
	INSTRUCTIONCOUNTER = OPERAND;
	return 1;
}

/* Branch to MEMORY address Operand if value in Accumulator is negative */
int doBranchNeg( void )
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	if(ACCUMULATOR < 0)
	    INSTRUCTIONCOUNTER = OPERAND;
	else
	    INSTRUCTIONCOUNTER++;
	
	return 1;
}

/* Branch to MEMORY address Operand if value in Accumulator is zero */
int doBranchZero( void ) 
{
	if(OPERAND>MEMORYSIZE-1) {
		printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
		       OPERAND, INSTRUCTIONCOUNTER);
		PAUSE;
		return -1;
	}
	
	if(ACCUMULATOR == 0)
	    INSTRUCTIONCOUNTER = OPERAND;
	else
	    INSTRUCTIONCOUNTER++;
	    
	return 1;
}

