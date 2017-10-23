/*
 * Filename:    main.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/10/2017.
 * Description: Simpletron Interpreter version 2.2
 *              Corrected error with Float Storage
 *              Added some input validations and removed some
 *                obsolete checks.
 *              Removed the newlines automatically added when writing
 *                out ints and floats to stdin
 *              Corrected string read/write errors
 *              Strings now need space allocated them with the length
 *                in half bytes being stored there
 *                eg 988  12000   - 24 characters
 *              doStringWrite will write for the length of the string or
 *                until it encounters a nullbyte
 *              removed the ? prompt displayed whenever the user input
 *                any data e.g., from doReadString. So the can supply
 *                the own prompt with a print statement 
 *              DoReadString does not add string length - it must be
 *                declared in advance to a dim statement
 *              Corrected printing error in doWriteString
 */

#include "SimpleTron.h"

// Methods /////////////////////////////////

int main()
{
    printf("%s\n", INTROTEXT);
    PAUSE;

    mainMenu();
    
    return 0;
}


/**
 * The function mainMenu is used to display the main menu
 * to the user, allow the user to select an option, and
 * call the function related to the user's choice.
 */
void mainMenu()
{
    char choice;
    int showMenu = 1;
    
    while( showMenu == 1 )
    {
        CLEARSCREEN;
        printf("%s", MENU);
        
        /* Get input and consume any other characters */
        choice = getchar();
        fflush( stdin );
        
        switch( choice )
        {
            case '1':
                loadProgram();
                break;
            case '2':
                loadCodeFromFile();
                break;                  
            case '3':
                runProgram();
                break;
            case '4':
                dumpMemoryAndRegistersToFile();
                break;
            case '5':
                dumpMemoryAndRegistersToScreen();
                break;
            case '6':
                CLEARSCREEN;
                printf( OPCODELIST );
                break;
            case '0':
                printf("QUITTING\n");
                return;
                break;
            default:
                printf("\n*** Invalid option ***\n");
                break;
        }
        
        PAUSE;
    }
}


/**
 * The function getInteger inputs and returns an integer.
 * @return An integer.
 */
int getInteger()
{
    char input[WORDLENGTH];
    int result = 0;
    int validInt = 0;
    
    /* Input a string */
    getLine( input, WORDLENGTH );
    
    /* If the string is valid convert and return it */
    while( validInt == 0 )
    { 
        /* sscanf returns the number of conversions made */
        if( !isspace(input[0]) )
            validInt = sscanf(input, "%d", &result); 

        if( validInt == 0 ) 
        {
            printf("Error - Please enter a valid number: ");
            getLine(input, WORDLENGTH);         
        }
    }

    return result;
}


/**
 * The function getDouble inputs and returns a double.
 * @return A double.
 */
double getDouble()
{
    char input[MAXFLOATLEN];
    double result;
    int validDouble = 0;
        
    /* Input a string */
    getLine( input, MAXFLOATLEN );
    
    /* If the string is valid convert and return it */
    while( validDouble == 0 )
    { 
        /* sscanf returns the number of conversions made */
        if( !isspace(input[0]) )
            validDouble = sscanf(input, "%lf", &result); 

        if( validDouble == 0 ) 
        {
            printf("Error - Please enter a valid number: ");
            getLine(input, MAXFLOATLEN);            
        }
    }

    return result;
}


/**
 * The function doubleToString writes the character equivalent of the
 * double num to the character array passed to it. 
 * @param s[] A character array to store the converted double.
 * @param num A double to convert to a string.
 */
void doubleToString(char s[], double num)
{
    sprintf( s, "%lf", num );
}


/**
 * The function intToString writes the character equivalent of the
 * integer num to the character array passed to it. 
 * @param s[] A character array to store the converted integer.
 * @param num An integer to convert to a string.
 */
void intToString(char s[], int num)
{
    sprintf( s, "%d", num );
}


/**
 * The function isValidInt checks whether the string passed to it
 * contains a valid integer. If yes it returns 1, otherwise -1; 
 * @param str A string to check whether it is an integer or not.
 * @return 1 if the string passed to it contains a valid integer,
 *           otherwise -1.
 */
int isValidInt(const char *str)
{
    if ( *str == '-' || *str=='+' )
        ++str;

    if (!*str)
        return -1;

    while (*str)
    {
        if ( !isdigit(*str) )
            return -1;
        else
            ++str;
    }
    
    return 1;
}


/**
 * The function splitDouble splits a double into left-hand side and
 * right-hand side of the decimal point and stores these values
 * into the integer array sides.
 * @param d A double to split into left-hand side and right-hand side 
 *          of the decimal point
 * @param sides An integer array to store the sides of the split double.
 */
void splitDouble(double d, int sides[2])
{
    sides[0] = d;
    sides[1] = ( d-sides[0] )*1000000;
}


/**
 * The function reconstructDouble creates and returns a double
 * from the left-hand side and right-hand side parts of it contained
 * in the integer array sides.
 * @param sides An integer array to containing the sides of the 
 *              split double.
 * @return A double reconstructed from the two sides stored in 
 *         the sides array. 
 */
double reconstructDouble(int sides[2])
{
    double reconstructed = sides[0];
    reconstructed += ( sides[1]/1000000.0 );
    return reconstructed;
}


/**
 * The function clearMemory sets resets the values in all
 * memory locations to zero. 
 */
void clearMemory()
{
    int i;
    for( i=0; i<MEMORYSIZE; i++ )
        MEMORY[i] = 0;  
}


/**
 * The function addInstructionToMemory store instructions
 * directly into the SimpleTron's MEMORY array. If the MEMORY
 * address or instruction value is out of bounds it returns -1,
 * otherwise if the instruction was added successfully it returns 1.
 * @return 1 if the program was entered into memory, otherwise -1. 
 */     
int addInstructionToMemory( int address, int instruction )
{
    if( address >= MEMORYSIZE || address < 0 )
        return -1;
    if( instruction < -999999 || instruction > 999999 )
        return -1;
    MEMORY[address++] = instruction;
    
    return 1;
}


/**
 * The function loadProgram allows the user to input instructions
 * directly into the SimpleTron's MEMORY array. If the program was entered
 * correctly it returns 1, otherwise -1.
 * @return 1 if the program was entered into memory, otherwise -1. 
 */
int loadProgram()
{
    clearMemory();
    
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
            input = getInteger();
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
            if( addInstructionToMemory( address, input ) == -1 )
                return -1;
            address++;

            printf("%02d ? ", address);
            input = getInteger();
        }
    }
    
    printf("\n*** Program loading completed ***\n");
    return isValidLoad;
}


/**
 * The function loadCodeFromFile allows the user to load an sml program
 * stored in a file directly into the simpletrons MEMORY array. 
 */
void loadCodeFromFile()
{
    int address, instruction;
    int validLine;
    char line[ LINELENGTH ];
    char *linePtr;
    size_t tokenNumber = 0;
    char *tokenPtr;
    
    CLEARSCREEN;
    char filename[30];
    
    printf("Enter name of file to load: ");
    getLine( filename, 30 ); 
    
    if( !endsWithSuffix(filename, ".sml") ) {
        printf("Error - \"%s\" does not seem to be a valid sml file.\n", filename);
        return;
    }
        
    FILE *sourceFilePtr = fopen(filename, "r");

    if( sourceFilePtr == NULL ) {
        printf("Error - unable to open file \"%s\"\n", filename);
        return;
    }
    else 
    {
        clearMemory(); /* Remove any programs currently in memory */
        
        while ( fgets ( line, sizeof line, sourceFilePtr ) != NULL )
        {
            validLine = 0;
            
            linePtr = line;
            while(linePtr[0]==' ')
                linePtr++;

            tokenNumber = 0;
            
            tokenPtr = strtok(linePtr, " \t");
            while ( tokenPtr != NULL )
            {
                if( endsWithSuffix(tokenPtr, "\n") )
                    removeEndChar( tokenPtr );
                    
                if( isValidInt( tokenPtr ) >= 0 ) {
                    if( tokenNumber == 0 ) {
                        sscanf(tokenPtr, "%d", &address);
                        validLine++;
                    }
                    else if( tokenNumber == 1 ) {
                        sscanf(tokenPtr, "%d", &instruction);
                        validLine++;
                    } 
                }
                    
                tokenPtr = strtok(NULL, " \t");
                tokenNumber++;
            }
            if( validLine==2 ) 
            {
                if( addInstructionToMemory( address, instruction ) == -1 ) 
                {
                    fclose( sourceFilePtr );
                    printf("Error - Invalid Address/Instruction in file '%d %d'\n", 
                            address, instruction);
                    return;
                }    
            }
        }       
    }

    fclose( sourceFilePtr );
    printf("File \"%s\" loaded into memory.\n", filename);
}


/**
 * The function dumpMemoryAndRegistersToFile allows the user to write
 * the current contents of the Registers and Memory to a dump file.
 */
void dumpMemoryAndRegistersToFile()
{
    int i, value, row=0;
    
    char filename[30];
    
    CLEARSCREEN;
    printf("Enter name of dump file (e.g,. coredump.txt): ");
    getLine( filename, 30 ); 
   
    FILE *ofPtr;
 
    if ( ( ofPtr = fopen( filename, "w" ) ) == NULL )
    {
        printf("Error - unable to create file \"%s\"\n", filename);
        return;
    }

    /* Print out REGISTER Contents*/
    fprintf( ofPtr, "REGISTERS:\n");
    if(ACCUMULATOR >= 0)
        fprintf( ofPtr, "accumulator:\t\t  +%06d\n", ACCUMULATOR );
    else
        fprintf( ofPtr, "accumulator:\t\t  %06d\n", ACCUMULATOR);
        
    if(FLTACCUMULATOR >= 0)
        fprintf( ofPtr, "float accumulator:\t+%7.6f\n", FLTACCUMULATOR );
    else
        fprintf( ofPtr, "float accumulator:\t%7.6f\n", FLTACCUMULATOR );    
    
    fprintf( ofPtr, "instructionCounter:\t     %04d\n", INSTRUCTIONCOUNTER);
    
    if(INSTRUCTIONREGISTER  >= 0)
        fprintf( ofPtr, "instructionRegister:  +%06d\n", INSTRUCTIONREGISTER);
    else
        fprintf( ofPtr, "instructionRegister:   %06d\n", INSTRUCTIONREGISTER);

    fprintf( ofPtr, "operationCode:\t\t       %02d\n", OPERATIONCODE);
    fprintf( ofPtr, "operand:\t\t       %06d\n", OPERAND);
     
    /* Print out MEMORY Contents*/
    fprintf( ofPtr, "\nMEMORY:\n");
    
    fprintf( ofPtr, "%13s", "0");
    
    for( i=1; i<10; i++ )
        fprintf( ofPtr, "%9d", i);
    
    fprintf( ofPtr, "\n%03d  ", row++);
    
    for( i=0; i<MEMORYSIZE; i++ ) 
    {
        value = MEMORY[i];
        if( value==0 )
            fprintf( ofPtr, "%8s", " +000000 ");
        else
        {
            if(value>0)
                fprintf( ofPtr, " %s%06d ", "+", MEMORY[i]);
            else
                fprintf( ofPtr, "  %06d ", MEMORY[i]);
        }
        
        if( (i+1)%10==0 && (i+1 < MEMORYSIZE ) )
            fprintf( ofPtr, "\n%03d  ", i+1);
    }
    
    fprintf( ofPtr, "\n");
    fclose( ofPtr );
    printf("Core written out to %s\n", filename);
}


/**
 * The function dumpMemoryAndRegistersToScreen allows the user to write
 * the current contents of the Registers and Memory to stdout.
 */
void dumpMemoryAndRegistersToScreen()
{
    int i, value, row=0;
    
    CLEARSCREEN;
    
    /* Print out REGISTER Contents*/
    printf("REGISTERS:\n");
    if( ACCUMULATOR >= 0 )
        printf("accumulator:\t\t   +%06d\n", ACCUMULATOR );
    else
        printf("accumulator:\t\t   %06d\n", ACCUMULATOR);
        
    if( FLTACCUMULATOR >= 0 )
        printf("float accumulator:\t +%7.6f\n", FLTACCUMULATOR );
    else
        printf("float accumulator:\t %7.6f\n", FLTACCUMULATOR );    
    
    printf("instructionCounter:\t      %04d\n", INSTRUCTIONCOUNTER);
    
    if( INSTRUCTIONREGISTER  >= 0 )
        printf("instructionRegister:\t   +%06d\n", INSTRUCTIONREGISTER);
    else
        printf("instructionRegister:\t   %06d\n", INSTRUCTIONREGISTER);

    printf("operationCode:\t\t        %02d\n", OPERATIONCODE);
    printf("operand:\t\t    %06d\n", OPERAND);
     
    /* Print out MEMORY Contents*/
    printf("\nMEMORY:\n");
    
    printf("%13s", "0");
    for( i=1; i<10; i++ )
        printf("%9d", i);
    
    printf("\n%03d  ", row++);
    for( i=0; i<MEMORYSIZE; i++ ) 
    {
        value = MEMORY[i];
        if( value==0 )
            printf("%8s", " +000000 ");
        else
        {
            if( value>0 )
                printf(" %s%06d ", "+", MEMORY[i]);
            else
                printf("  %06d ", MEMORY[i]);
        }
        
        if( (i+1)%10==0 && (i+1 < MEMORYSIZE ) )
            printf("\n%03d  ", i+1);
    }
    printf("\n");
}


/**
 * The function runProgram executes the sml program currently
 * loaded into MEMORY. If the program executed correctly it
 * returns 0, otherwise -1.
 * @return 1 if the program executed correctly, otherwise -1. 
 */
int runProgram()
{
    int programState=1; /* O=Halt, -1=ERROR*/
    
    printf("\n*** Program execution begins ***\n");
    
    while( ( programState==1 ) && ( INSTRUCTIONCOUNTER < MEMORYSIZE ) ) 
    {
        loadInstruction();
//        Uncomment to step lthrough instruction by instruction        
//        PAUSE;
//        dumpMemoryAndRegistersToScreen();
//        PAUSE;
        
        programState = processInstruction();
    }
    
    if( programState==0 ) {
        printf("\n*** Simpletron execution terminated normally ***\n");
        INSTRUCTIONCOUNTER = 0;
    }  
    else
    {
        dumpMemoryAndRegistersToScreen();
        printf("\n*** Simpletron execution terminated abnormally at line %02d ***\n", INSTRUCTIONCOUNTER);
        INSTRUCTIONCOUNTER = 0;
    }
    
    return programState;
}


/**
 * The function loadInstruction() loads the instruction pointed
 * to by the INSTRUCTIONCOUNTER into the Registers.
 */
void loadInstruction()
{
    INSTRUCTIONREGISTER = MEMORY[INSTRUCTIONCOUNTER];
    OPERATIONCODE = INSTRUCTIONREGISTER / 10000;
    OPERAND = INSTRUCTIONREGISTER % 10000;
}


/**
 * The function processInstruction() decodes and executes the 
 * instruction currently loaded into the registers. If the instruction
 * executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int processInstruction()
{
    int isValidInstruction = 1;
    
    switch( OPERATIONCODE )
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
        case BRANCHPOS:
            isValidInstruction = doBranchPos(); 
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


/**
 * The function doRead reads an integer from stdin to the 
 * MEMORY address OPERAND. If the instruction executed correctly 
 * it returns 1, otherwise -1
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doRead( void )
{   
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    MEMORY[OPERAND] = getInteger();
    
    if( MEMORY[OPERAND]>999999 || MEMORY[OPERAND]<-999999 )
    {
        printf("\n*** Fatal Error! Overflow at address %04d ***\n", OPERAND );
        printf("*** after executing line %04d!            ***\n", INSTRUCTIONCOUNTER );
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doWrite writes an integer stored at the MEMORY address
 * OPERAND to stdout. If the instruction executed correctly 
 * it returns 1, otherwise -1
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doWrite( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to write from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    printf( "%d", MEMORY[OPERAND] );
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doNewLine writes a newline character to stdout, returns 
 * successful execution code 1.
 * @return Successful execution code 1. 
 */
int doNewLine( void )
{
    printf("\n");
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doReadFloat reads a double from stdin to the 
 * MEMORY address OPERAND. If the instruction executed correctly 
 * it returns 1, otherwise -1. Note: doubles are stored as two integers
 * representing the left-hand side and right-hand sides of the decimal point.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doReadFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
        printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
     
    int sides[2] = { 0, 0 };
    double f = getDouble();
    splitDouble(f, sides);
    
    if( sides[0] < -999999 || sides[0] > 999999 ) {
        return -1;
    } 
        
    if( sides[1] < -999999 || sides[1] > 999999 ) {
        return -1;
    }
    
    MEMORY[OPERAND] = sides[0];
    MEMORY[OPERAND+1] = sides[1];    
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doWriteFloat writes a double stored at the MEMORY address
 * OPERAND to stdout. If the instruction executed correctly 
 * it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doWriteFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
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


/**
 * The function doReadString reads a string from stdin to the 
 * MEMORY address OPERAND. If the instruction executed correctly 
 * it returns 1, otherwise -1. Note: String characters are stored as 
 * half words, the beginning of the strings memory location contains
 * the length of the string to follow.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doReadString( void )
{   
    /* First check that the memory location is valid */
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    char input[ MAXSTRINGLEN ];

    int strSize = getLine( input, MAXSTRINGLEN );
    int i, temp;
    
    /* Check whether the string can fit into the space allocated for it */
    int allocatedSpace = MEMORY[OPERAND] / 1000;

    if( strSize > allocatedSpace*2-2 ) {
        printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
               OPERAND+strSize, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    /* Check that there is enough space to store the string into memory */
    if( OPERAND + (strSize/2 + 1) > MEMORYSIZE-1) {
        printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
               OPERAND+strSize, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    /* Store the string into memory as half words*/
    int address = OPERAND;

    temp = (MEMORY[OPERAND] / 1000)*1000;
    for( i=0; i<=strSize; i++ )
    {
        if( i%2==0 ) {
            temp+=(int)input[i];
            MEMORY[address++] = temp;
        }
        else
            temp = (int)input[i] * 1000;
    }
    
    if( i%2==0 )
        MEMORY[address++] = temp;
    
    /* Fill the rest of the allocated space with null bytes */
    for( ; i<allocatedSpace; i++ )
        MEMORY[address++] = 0;
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doWriteString writes a string stored at the MEMORY address
 * OPERAND to stdout. If the instruction executed correctly 
 * it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doWriteString( void )
{
    /* First check that the memory location is valid */
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to write to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    int address = OPERAND;

    int first = MEMORY[address++];
    int strSize = first/1000;
    
    /* Print the first character */
    if( strSize>0 && (first-(strSize*1000)) )
        printf("%c", first-(strSize*1000));
    
    if(strSize==1)
        return 1;
    
    int i, temp, temp1;
    
    /* Convert the half words back to characters and print them */
    for( i=1; i<strSize; i++ )
    {
        temp = MEMORY[address++];
        temp1 = temp/1000;
        
        if(temp1 > 0)
            printf("%c", temp1);
        else
            break;
            
        temp = temp-(temp1*1000);
        
        /* Print chars until a null byte is encountered */
        if(temp>0)
            printf("%c", temp);
        else
            break;
    }
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doLoad loads the integer value stored at MEMORY address 
 * OPERAND into the Accumulator. If the instruction executed correctly 
 * it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doLoad( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to load from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    ACCUMULATOR = MEMORY[OPERAND];
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doStore stores the integer value currently contained within
 * the Accumulator to the MEMORY address OPERAND. If the instruction 
 * executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doStore( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to store to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    MEMORY[OPERAND] = ACCUMULATOR;
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doLoad loads the float value stored at MEMORY address 
 * OPERAND into the Float Accumulator. If the instruction executed 
 * correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doLoadFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
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


/**
 * The function doStoreFloat stores the float value currently contained within
 * the Float Accumulator to the MEMORY address OPERAND. If the instruction 
 * executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doStoreFloat( void )
{
    if( OPERAND>MEMORYSIZE-2 ) {
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


/**
 * The function doAdd adds the integer value stored at MEMORY address 
 * OPERAND to the value contained within the Accumulator. If the instruction 
 * executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doAdd( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    ACCUMULATOR += MEMORY[OPERAND];
    
    if( ACCUMULATOR>999999 || ACCUMULATOR<-999999 )
    {
        printf("\n*** Fatal Error! Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doSubtract subtracts the integer value stored at MEMORY address 
 * OPERAND from the value contained within the Accumulator. If the instruction 
 * executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doSubtract( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    ACCUMULATOR -= MEMORY[OPERAND];
    
    if( ACCUMULATOR>999999 || ACCUMULATOR<-999999 )
    {
        printf("\n*** Fatal Error! Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doDivide divides the value contained within the Accumulator
 * by the integer value stored at MEMORY address OPERAND. If the instruction 
 * executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doDivide( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    if( MEMORY[OPERAND]==0 )
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


/**
 * The function doMultiply multiplies the value contained within
 * the Accumulator by the integer value stored at MEMORY address OPERAND.
 * If the instruction  executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doMultiply( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    ACCUMULATOR *= MEMORY[OPERAND];
    
    if( ACCUMULATOR>999999 || ACCUMULATOR<-999999 )
    {
        printf("\n*** Fatal Error! Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doModulus modulos the value contained within
 * the Accumulator by the integer value stored at MEMORY address OPERAND.
 * If the instruction  executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doModulus( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    if( MEMORY[OPERAND]==0 )
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


/**
 * The function doExponentiation raise the value contained within
 * the Accumulator to the power of the integer value stored at MEMORY
 * address OPERAND. If the instruction  executed correctly it returns 1,
 * otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doExponentiation( void )
{   
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }

    int i;
    int original = ACCUMULATOR;
    for( i=1; i<MEMORY[OPERAND]; i++ )
        ACCUMULATOR *= original;
    
    if( ACCUMULATOR>999999 || ACCUMULATOR<-999999 )
    {
        printf("\n*** Fatal Error! Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;
    return 1;
}


/**
 * The function doAddFloat adds the float value stored at MEMORY address 
 * OPERAND to the value contained within the Float Accumulator.
 * If the instruction executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doAddFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
        
    int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
    double f = reconstructDouble(sides);
    
    FLTACCUMULATOR += f;
    
    if( FLTACCUMULATOR>999999.999999 || FLTACCUMULATOR<-999999.999999 )
    {
        printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;

    return 1;
}


/**
 * The function doSubtractFloat subtracts the float value stored at MEMORY
 * address  OPERAND from the value contained within the Accumulator.
 * If the instruction executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doSubtractFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
        
    int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
    double f = reconstructDouble(sides);
    
    FLTACCUMULATOR -= f;
    
    if( FLTACCUMULATOR>999999.999999 || FLTACCUMULATOR<-999999.999999 )
    {
        printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;

    return 1;
}


/**
 * The function doDivideFloat divides the value contained within
 * the Float Accumulator by the float value stored at MEMORY address OPERAND. 
 * If the instruction executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doDivideFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
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
    
    INSTRUCTIONCOUNTER++;

    return 1;
}


/**
 * The function doMultiplyFloat multiplies the value contained within
 * the Float Accumulator by the float value stored at MEMORY address OPERAND.
 * If the instruction  executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doMultiplyFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
        
    int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
    double f = reconstructDouble(sides);
    
    FLTACCUMULATOR *= f;
    
    if( FLTACCUMULATOR>999999.999999 || FLTACCUMULATOR<-999999.999999 )
    {
        printf("\n*** Fatal Error! Float Accumulator overflow ***\n");
        PAUSE;
        return -1;
    }
    
    INSTRUCTIONCOUNTER++;

    return 1;
}


/**
 * The function doModulusFloat modulos the value contained within
 * the Float Accumulator by the float value stored at MEMORY address OPERAND.
 * If the instruction executed correctly it returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doModulusFloat( void )
{
    /* If there are not two words to load from memory */
    if( OPERAND>MEMORYSIZE-2 ) {
        printf("\n*** Fatal Error! Attempting to read from out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
        
    int sides[2] = { MEMORY[OPERAND], MEMORY[OPERAND+1] };
    double f = reconstructDouble(sides);
    
    if( f==0.0 )
    {
        printf("\n*** Attempt to Modulo by Zero! ***\n");
        PAUSE;
        return -1;
    }
    
    FLTACCUMULATOR = fmod(FLTACCUMULATOR, f);
    
    INSTRUCTIONCOUNTER++;

    return 1;
}


/**
 * The function doBranch branches the flow of execution of a running program
 * to MEMORY address OPERAND. If the instruction executed correctly it 
 * returns 1, otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doBranch( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }  
    
    INSTRUCTIONCOUNTER = OPERAND;
    return 1;
}


/**
 * The function doBranchNeg branches the flow of execution of a running program
 * to MEMORY address OPERAND if the value contained within the Accumulator
 * is negative. If the instruction executed correctly it returns 1, 
 * otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doBranchNeg( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    if( ACCUMULATOR < 0 )
        INSTRUCTIONCOUNTER = OPERAND;
    else
        INSTRUCTIONCOUNTER++;
    
    return 1;
}


/**
 * The function doBranchZero branches the flow of execution of a running program
 * to MEMORY address OPERAND if the value contained within the Accumulator
 * is zero. If the instruction executed correctly it returns 1, 
 * otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doBranchZero( void ) 
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    if( ACCUMULATOR == 0 )
        INSTRUCTIONCOUNTER = OPERAND;
    else
        INSTRUCTIONCOUNTER++;
        
    return 1;
}


/**
 * The function doBranchPos branches the flow of execution of a running program
 * to MEMORY address OPERAND if the value contained within the Accumulator
 * is greater than zero. If the instruction executed correctly it returns 1, 
 * otherwise -1.
 * @return 1 if the instruction executed correctly, otherwise -1. 
 */
int doBranchPos( void )
{
    if( OPERAND>MEMORYSIZE-1 ) {
        printf("\n*** Fatal Error! Attempting to branch to out of bounds address %d at line %04d ***\n", 
               OPERAND, INSTRUCTIONCOUNTER);
        PAUSE;
        return -1;
    }
    
    if( ACCUMULATOR > 0 )
        INSTRUCTIONCOUNTER = OPERAND;
    else
        INSTRUCTIONCOUNTER++;
    
    return 1;
}

