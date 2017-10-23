/*
 * Filename:    main.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/10/2017.
 * Version:     V2.9.3
 * Description: Code has been tidied up a little
 *              Corrected problem with String literal assigning the wrong 
 *               string length to the beginning of strings stored in memory
 *              Max string length increased to 50 chars
 *              Added a newline command which prints a newline to the console
 *              Corrected a problem with the createForInstruction function
 *               adding a blank instruction after tidying up the code
 *              Accepts filenames as args when run with the flag -f
 *              Prints usage information with the flag -h
 *              Repaired String literal creation method which didn't work
 *                with string comparisons. Added a removeFirstChar method to
 *                replace removeQuotes.
 *              Implemented variable string comparisons, and variable string
 *                and string literal comparisons
 *              Fixed problem with looping string compares - eg "continue (y/n)"
 *                which was retaining the last string positions
 *              Add a string literal array so that once a string literal is
 *                added to memory it does not need to be readded each time
 *                it is included into the program.
 */

#include "SimpleCompiler.h"


int main(int argc, char *argv[])
{
    char filename[ MAXLINELENGTH ];
    
    if(argc > 1) 
    {
        if(argv[1][0] == '-' && strlen2(argv[1]) > 1 ) {
            switch (argv[1][1])
            {
                case 'h':
                    printf("Usage: SimpleCompiler [-f filename]\n");
                    return 0;
    
                case 'f':
                    if(argc > 2) {
                        strcpy2(filename, argv[2]);  
                    }
                    else {
                        printf("Usage: SimpleCompiler [-f filename]\n");
                        return 0;
                    }
                    break;
    
                default:
                    printf("Usage: SimpleCompiler [-f filename]\n");
                    return 0;
            }
        }
        else {
            printf("Usage: SimpleCompiler [-f filename]\n");
            return 0;
        }
    }
    else {
        printf("Enter name of file to load: ");
        getLine( filename, MAXLINELENGTH );        
    }
    
    ForLoopStackPtr = NULL;
    
    /* Set each element in flags to -1 */
    initialiseFlags();
    
    
    /* Compile to SML */
    if( runFirstPass( filename ) != SUCCESS) {
        printf("Compilation failed on the first pass!\n");
        return FAIL;
    }
        
    if( runSecondPass() != SUCCESS) {
        printf("Compilation failed on the second pass!\n");
        return FAIL;
    }

    /* Write out the instructions to file */
    if( writeInstructionsToFile( "out.sml" ) != SUCCESS ) {
        printf("Unable to create output file!\n");
        return FAIL;
    }  
    else
        printf("Instructions successfully written to \"out.sml\"\n");
        
    return 0;
}


/**
 * The function initialiseFlags initialises all of the values within
 * the Flags array, used to mark line numbers to be resolved during the
 * compiler's second pass, to -1.
 */
void initialiseFlags()
{
    int i;
    
    for(i=0; i<MEMORYSIZE; i++)
        Flags[i]=-1;
}


/**
 * The function printFlags prints out the contents of the Flags array.
 */
void printFlags()
{
    int i;
    
    printf("\n---- Flags for Second Pass ----\n\n");
    
    for( i=1; i<=MEMORYSIZE; i++ ) {
        printf( "%4d ", Flags[i-1]) ;
        if(i%10==0)
            printf( "\n" );
    }   
}


/**
 * The method printInstructions prints out the instructions currently 
 * stored in the MEMORY array.
 */
void printInstructions()
{
    int i;
    for( i=0; i<MEMORYSIZE; i++ ) {
        if( MEMORY[i]!=0 )
            printf("%4d   %6d\n", i, MEMORY[i]); 
    }
}


/**
 * The function addInstructionToMemory checks that it can safely
 * write an instruction to memory, then adds the instruction.
 * @param instruction An instruction to write to memory.
 * @return SUCCESS if the instruction was successfully written to MEMORY,
 *         otherwise FAIL.
 */
int addInstructionToMemory( int instruction )
{
    if(INSTRUCTIONCOUNTER >= VARCONSTADDRESS ) {
        printf("Error - attempt to overwrite memory assigned to variables\n");
        return FAIL;
    }
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction;
    return SUCCESS;
}


/**
 * The method writeInstructionsToFile writes out the instructions created
 * from the Simple input file to the sml output file.
 * @param outfile The name of the sml output file to create.
 * @return SUCCESS If the write operation was successful, otherwise FAIL. 
 */
int writeInstructionsToFile( const char *outFile )
{
    int i;
    FILE *ofPtr;
    
    if( (ofPtr = fopen(outFile, "w")) == NULL ) {
        printf("File could not be opened\n");
        return FAIL;
    }
    else 
    {
        for( i=0; i<MEMORYSIZE; i++ ) {
            if( MEMORY[i]!=0 ) {
                if( MEMORY[i]>0 )
                    fprintf(ofPtr, "%02d +%d\n", i, MEMORY[i]); 
                else
                    fprintf(ofPtr, "%02d %d\n", i, MEMORY[i]); 
            } 
        }
        
        fclose(ofPtr);
    }
    
    return SUCCESS;
}


/**
 * The function addLineNumberToTable adds the details for a 
 * line number to the symbols table during the compiler's first pass.
 * @param number A line number.
 */
void addLineNumberToTable( int number )
{
    Table[TABLEPOSITION].symbol = number;
    Table[TABLEPOSITION].type = 'L';
    Table[TABLEPOSITION].location = INSTRUCTIONCOUNTER;
    TABLEPOSITION++;  
    PREVIOUSLINENUMBER = number;
}


/**
 * The function updateStringVariableAddress updates the address assigned
 * within the symbol table to the string variable c, and adjusts the
 * VARCONSTADDRESS to be assigned to the next variable.
 * @params c The variable name.
 * @param strLen The number of character spaces to be assigned to the string.
 * @return SUCCESS if the operation completed successfully, otherwise FAIL.
 */
int updateStringVariableAddress( char c, int strLen )
{   
    int i, entryUpdated=0;
    
    for( i=0; i<TABLEPOSITION; i++)
    {
        if(Table[i].symbol == c) 
        {
            int offset = strLen/2 + 1;
            int newPosition = Table[i].location - offset;
            
            /* Check that the string is not overwriting instructions */
            if( newPosition <= INSTRUCTIONCOUNTER ) {
                printf("Error - no room for variable %c to be added\n", c);
                return FAIL;
            }
                
            Table[i].location = newPosition;
            VARCONSTADDRESS -= (offset + 1);
            i = TABLEPOSITION;
            entryUpdated = 1;
        }
    }
    
    if(entryUpdated==0) {
        return FAIL;
    }
    
    return SUCCESS;
}


/**
 * The function addVariableToTable adds the details for a 
 * variable to the symbols table during the compiler's first pass.
 * @param c A variable.
 * @return SUCCESS if MEMORY space was successfilly allocated,
 *         otherwise FAIL.
 */
int addVariableToTable( char c )
{   
    /* Check that there is space tro allocate to the variable */
    if(VARCONSTADDRESS <= INSTRUCTIONCOUNTER )
        return FAIL;
        
    if( variableExistsInTable( c ) == -1)  {
        Table[TABLEPOSITION].symbol = c;
        Table[TABLEPOSITION].type = 'V'; 
        Table[TABLEPOSITION].location = VARCONSTADDRESS--;
        TABLEPOSITION++;
    }
    
    return SUCCESS;
}


/**
 * The function addConstantToTable adds the details for a 
 * constant to the symbols table, and adds its value to a
 * memory location during the compiler's first pass.
 * @param number A constant value.
 * @return SUCCESS if MEMORY space was successfully allocated,
 *         otherwise FAIL.
 */
int addConstantToTable( int number )
{   
    /* Check that there is space to allocate to the variable */
    if(VARCONSTADDRESS <= INSTRUCTIONCOUNTER )
        return FAIL;
        
    if( constantExistsInTable( number ) == -1 ) {
        Table[TABLEPOSITION].symbol = number;
        Table[TABLEPOSITION].type = 'C';
        MEMORY[ VARCONSTADDRESS ] = number;
        Table[TABLEPOSITION].location = VARCONSTADDRESS--;  
        TABLEPOSITION++;                    
    }
    
    return SUCCESS;
}


/**
 * The function runFirstPass runs the compiler's first pass of the Simple
 * source file. It reads in the lines one at a time, adding their symbols
 * to the lookup table and creating sml instructions.
 * @param inFile The name of the Simple source file to compile.
 * @return SUCCESS if the first pass ran correctly, otherwise FAIL.
 */
int runFirstPass( const char *inFile )
{
    char line[ MAXLINELENGTH ];
    char lineCopy[ MAXLINELENGTH ];
    char tokenArray[ MAXLINELENGTH ][MAXTOKENLENGTH];
    int lineParsed;
    
    if( inFile == NULL ) {
        printf( "Error - a valid Simple sourcecode file name has not been provided.\n" );
        return FAIL;
    }
    
    if( !endsWithSuffix( inFile, ".simple" ) ) {    
        printf( "Error - \"%s\" does not seem to be a valid Simple sourcecode file.\n", inFile );
        return FAIL;
    }
    
    FILE *sourceFilePtr = fopen( inFile, "r" );

    if( sourceFilePtr == NULL ) 
    {
        printf("Error - unable to open file \"%s\"\n", inFile);
        return FAIL;
    }
    else 
    {
        while ( fgets ( line, sizeof line, sourceFilePtr ) != NULL )
        {   
            if(endsWith(line, '\n') )
                removeEndChar( line );
                
            strToLowercase(line);      /* make parsing case-insensitive */        
            strcpy2( lineCopy, line ); 
            
            /* Tokenise the line*/
            int numberOfTokens;
            numberOfTokens = createTokenArray( lineCopy, tokenArray );

            /* Add symbols to the lookup table*/
            lineParsed = addSymbolsToTable( tokenArray, numberOfTokens );
            
            if(lineParsed==FAIL) {
                fclose( sourceFilePtr );
                return FAIL;
            }
                
            /* Create SML instructions from the tokenised line */
            strcpy2( lineCopy, line ); 

            if( createFirstSML( tokenArray, numberOfTokens ) != SUCCESS ) {
                fclose( sourceFilePtr );
                printf("\nSyntax error on line %s\n", tokenArray[0]);
                return FAIL;
            }
        }       
    }

    fclose( sourceFilePtr );
    printf("\nFile \"%s\" loaded. Compiling...\n", inFile );
    return SUCCESS;
}


/**
 * The function runSecondPass runs the compiler's second pass of the
 * Simple source file, resolving addresses for the line numbers flagged
 * during the first pass and updating their related sml instructions.
 * @return SUCCESS if the second pass ran correctly, otherwise FAIL.
 */
int runSecondPass()
{
    int i, address;
    for( i=0; i<MEMORYSIZE; i++ ) 
    {
        if( Flags[i] != -1 ) 
        {
            address = lineNumberExistsInTable(Flags[i]);
            
            if(address==-1) {
                printf("\nError - could not resolve a GOTO address.");       
                return FAIL;
            }

            MEMORY[ i ] += address;
            Flags[i] = -1;
        }
    }
    
    return SUCCESS;
}


/**
 * The function createTokenArray tokenises the string passed to it and
 * stores the tokens into as character array array.
 * @param line A string to tokenise.
 * @param tokenArray Used to store the tokens.
 * @return The number of tokens extracted from the string.
 */
int createTokenArray( const char *line, char tokenArray[][MAXTOKENLENGTH] )
{
    int length = 0;
    char lineCopy[ MAXLINELENGTH ]; /* make copy of line because strtok 
                                     * alters the line it tokenises */
    char *tokenPtr;
    
    strcpy2(lineCopy, line);
    
    tokenPtr = strtok( lineCopy, " \n," );
    
    while( tokenPtr != NULL ) 
    {   
        while(startsWith(tokenPtr, '(') ) {
            strcpy2( tokenArray[length++], "(" ); 
            tokenPtr++;
        }
        /* Add array references whole eg a(2) */
        if( strlen2(tokenPtr)>3 && isalpha(tokenPtr[0]) &&
            (tokenPtr[1]=='(' || tokenPtr[1]=='$') && 
            endsWith(tokenPtr, ')') )
        {
            strcpy2( tokenArray[length++], tokenPtr ); 
        }
        else if(endsWith(tokenPtr, ')') ) {
            removeEndChar(tokenPtr);            
            strcpy2( tokenArray[length++], tokenPtr ); 
            strcpy2( tokenArray[length++], ")" ); 
        }
        else if(tokenPtr[0] != '\0') {
            strcpy2( tokenArray[length++], tokenPtr ); 
        }

        tokenPtr = strtok( NULL, " \n," );
    }
         
    return length;
}


/**
 * The function addSymbolsToTable is used during the compiler's 
 * first pass to add the symbols found on a tokenised line of Simple
 * to the lookup table.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int addSymbolsToTable( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens )
{   
    if( numberOfTokens == 0 ) {
        printf("\nSyntax Error!\n");
        return FAIL;
    }
    else if( !isdigit(tokenArray[0][0]) ) {
        printf("\nSyntax Error! Line numbers are required on ALL lines!\n");
        printf("See the line after line %d\n", PREVIOUSLINENUMBER );
        return FAIL;
    }
    
    int number;
    int isLineNumber = 1;

    int i;
    for(i=0; i<numberOfTokens; i++)
    {
        if(strlen2( tokenArray[i] ) > 1 ) 
        {   
            if(isdigit( tokenArray[i][0] ) || (  tokenArray[i][0] =='-' && isdigit(  tokenArray[i][1] )) )
            {
                number = strToInt(  tokenArray[i] ); 
                
                if(isLineNumber) 
                {
                    if( number > PREVIOUSLINENUMBER && i==0 ) {
                        addLineNumberToTable( number );
                        isLineNumber = 0;
                    } else {
                        printf("\nSyntax Error! Line numbers must be sequential!\n");
                        return FAIL;
                    }
                }
                else {
                    if( addConstantToTable( number ) == FAIL )
                        return FAIL;
                }
                           
            }
            else if(isalpha( tokenArray[i][0] ) && tokenArray[i][1]=='(' )
            {
                if( addVariableToTable( tokenArray[i][0] ) == FAIL)
                    return FAIL;
            } 
            else if(isalpha( tokenArray[i][0] ) && tokenArray[i][1]=='$' )
            {
                if( addVariableToTable( tokenArray[i][0] ) == FAIL )
                    return FAIL;
            } 
            else {
                /* If the rem command is encountered skip the rest of the line */               
                if( strcmp2( tokenArray[i], "rem") == 0 ) {
                    return SUCCESS;
                }
                /* If the goto command is encountered skip the rest of the line 
                 * so that the return line number is not added as a constant */               
                else if( strcmp2( tokenArray[i], "goto") == 0 ) {
                    return SUCCESS;
                }  
                /* If the gosub command is encountered add the '@' symbol 
                 * assigned to the subroutines return address, and the '$' 
                 * symbol is used to store the value used to dynamically create
                 * a branch address for the RETURN statement */               
                else if( strcmp2( tokenArray[i], "gosub") == 0 )  
                {
                    if( variableExistsInTable( '@' ) == FAIL)  {
                        if( addVariableToTable( '@' ) == FAIL)
                            return FAIL;
                        if( addConstantToTable( BRANCH*10000 ) == FAIL )
                            return FAIL;
                    }
                    return SUCCESS;
                } 
            }    
        }
        else 
        {
            if(isdigit( tokenArray[i][0] )) {
                number = strToInt( tokenArray[i] ); 
                
                if(isLineNumber)
                {
                    if(number > PREVIOUSLINENUMBER && i==0 ) {
                        addLineNumberToTable( number );
                        isLineNumber = 0;
                    } else {
                        printf("Syntax Error! Line numbers must be sequential!\n");
                        return FAIL;
                    }
                }
                else {
                    if( addConstantToTable( number ) == FAIL)
                        return FAIL;
                }
                    
            }
            else if(isalpha( tokenArray[i][0] ) ) {
                if( addVariableToTable( tokenArray[i][0] ) == FAIL )
                    return FAIL;
            }
        }
    }
    
    return SUCCESS;
}


/**
 * The function getElementAddressFromStr is used to extract an element's
 * MEMORY address from a token containing an array variable and an index
 * of the form 'a(12)'
 * @param token A string containing an array index.
 * @param variableAddress The first address of the array variable 
 *        in memory; containing its size.
 * @return The MEMORY address of the element in the array, otherwise
 *         if an error occurs return -1;
 */
int getElementAddressFromStr(char token[], int variableAddress )
{
    int arraySize = MEMORY[variableAddress];
    /* Check that the array has been declared */
    if(arraySize<=0) {
        printf("\nArray has not been declared.");
        return FAIL;
    }
    
    int multiplier = 10;
    int arrayIdx = 0;
    int idx=2;            /* first number in arraySize */
    
    while(token[idx] != ')') {
        arrayIdx += token[idx++] - '0';
        arrayIdx *= multiplier;
    }
    
    arrayIdx /= 10;
    
    if(arrayIdx > arraySize || arrayIdx <=0 ) {
        printf("\nArray index out of bounds..");
        return FAIL;
    }
    
    variableAddress -= arrayIdx;
    
    return variableAddress;
}


/**
 * The function createInputInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple input statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createInputInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{    
    int variableIdx; 
    int instruction;
    int variableAddress;
    
    /* Simple Syntax check*/
    if(numberOfTokens < 3) {
        return FAIL;
    }
    
    /* Allows inputs of the format 
     *    input x, y, z */
    for( variableIdx=2; variableIdx<numberOfTokens; variableIdx++ )
    {
        if( !isalpha(tokenArray[variableIdx][0]) )
            return FAIL;
        
        instruction = READ*10000;
        variableAddress = variableExistsInTable( tokenArray[variableIdx][0] );

        /* If the variable is a string change the instruction */
        if(strlen2( tokenArray[variableIdx] )==2 && tokenArray[variableIdx][1]=='$' ) {
            instruction = READSTRING*10000;
        }
            
        /* If value is being inputted to an array element */
        else if(strlen2(tokenArray[variableIdx]) > 3 )
        {
            variableAddress = getElementAddressFromStr(tokenArray[variableIdx], variableAddress );
    
            if( variableAddress == -1 ) {
                return FAIL;
            }
        }
        
        instruction += variableAddress;
        
        if( addInstructionToMemory( instruction ) == FAIL ) 
            return FAIL;      
    }
    
    return SUCCESS;
}


/**
 * The function stringLiteralExistsInMemory checks whether a string
 * literal has been stored in MEMORY. If yes it returns its address
 * otherwise it returns -1.
 * @param literal A string literal.
 * @return Address of string literal if it exists in memory, 
  *        otherwise -1.
 */
int stringLiteralExistsInMemory( const char *literal )
{
    int i=0;
    for(i=0; i<numberOfStringLiterals; i++)
    {
        if( strcmp2(literal, stringLiteralArray[i]) == 0 )
            return stringLiteralAddresses[i];
    }
    
    return -1;
}


/**
 * The function addStringLiteralToMemory is used by createPrintInstruction to
 * stores a String Literal into MEMORY.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return Address of string literal in MEMORY, else if an error
 *         occurred return FAIL.
 */
int addStringLiteralToMemory( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int firstToken ) 
{
    /* Copy the first token (minus the quotes) to copy */
    char copy[MAXLINELENGTH];
    removeFirstChar( copy, tokenArray[firstToken] );
    
    if(endsWith( copy, '"') ) 
    {
        removeEndChar(copy); 
    }
    else
    {
        int idx = firstToken + 1;
    
        if( idx < numberOfTokens )
        {
            while( ( idx < numberOfTokens-1 ) && 
                   ( endsWith( tokenArray[idx], '"' ) != 1 ) )
            {
                strcat2( copy, " " );
                strcat2( copy, tokenArray[idx++] );            
            }
            strcat2( copy, " " );
            strcat2( copy, tokenArray[idx] );
            removeEndChar(copy); 
        }       
    }
    int literalAddress = stringLiteralExistsInMemory(copy);
    if( literalAddress > -1 )
        return literalAddress;

    int stringLen = strlen2(copy); 
    
    int offset = stringLen/2 + 1;
    int startPosition = VARCONSTADDRESS - offset;
            
    /* Check that the string is not overwriting instructions */
    if( startPosition < INSTRUCTIONCOUNTER ) {
        printf("Error - no room to add \'%s\' to Memory\n", copy);
        return FAIL;
    }           
    
    VARCONSTADDRESS -= (offset + 1);
    
    int address = startPosition;
    int i;
    int temp = (stringLen/2 + 1) * 1000;
    
    for(i=0; i<stringLen; i++)
    {
        if(i%2==0) {
            temp += (int)copy[i];
            MEMORY[address++] = temp;
        }
        else
            temp = (int)copy[i] * 1000;
    }
    
    if(i%2==0)
        MEMORY[address++] = temp;
    
    /* Terminate the string with a null byte */
    MEMORY[address] = 0;
    
    strcpy2( stringLiteralArray[ numberOfStringLiterals ], copy );
    stringLiteralAddresses[ numberOfStringLiterals++ ] = startPosition;

    return startPosition;
}


/**
 * The function createPrintInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple print statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createPrintInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    int instruction;
    int variableAddress;    
    int variableIdx;
    
    /* Simple Syntax check*/
    if(numberOfTokens < 3) {
        return FAIL;
    }
    
    /* Allows prints of the format 
     *   'print x, y, z' and 'print x y z'  */
    for( variableIdx=2; variableIdx<numberOfTokens; variableIdx++ )
    {
        instruction = WRITE*10000;
        
        if( !isdigit( tokenArray[variableIdx][0]) )
        {
            variableAddress = variableExistsInTable( tokenArray[variableIdx][0] );

            /* Allow the printing of string literals using */
            if(tokenArray[variableIdx][0] == '"') {
                variableAddress = addStringLiteralToMemory(tokenArray, numberOfTokens, variableIdx);
                instruction = WRITESTRING*10000;
                variableIdx = numberOfTokens;
            }
            /* If the variable holds a string change the instruction */
            else if(strlen2( tokenArray[variableIdx] )==2 && tokenArray[variableIdx][1]=='$' ) 
            {
                instruction = WRITESTRING*10000;
                /* Print can only handle one string variable per line*/
                variableIdx = numberOfTokens;
            }
            /* If an array element is being printed */
            else if(strlen2(tokenArray[variableIdx]) > 3 )
            {
                variableAddress = getElementAddressFromStr(tokenArray[variableIdx], variableAddress );

                if( variableAddress == -1 ) {
                    return FAIL;
                }
           }
        }            
        else 
            variableAddress = constantExistsInTable( strToInt(tokenArray[variableIdx]) );

        instruction += variableAddress;
         
        if( addInstructionToMemory( instruction ) == FAIL ) 
            return FAIL;                 
    }
    
    return SUCCESS;
}


/**
 * The function createGotoInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple goto statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createGotoInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax check*/
    if(numberOfTokens < 3) {
        return FAIL;
    }
    
    int instruction = BRANCH*10000;

    int returnLineNumber = strToInt(tokenArray[2]);    
    int returnAddress = lineNumberExistsInTable( returnLineNumber );
    
    if(returnAddress != -1 )
        instruction += returnAddress;
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
    }
    
    if( addInstructionToMemory( instruction ) == FAIL ) 
        return FAIL;  
    
    return SUCCESS;
}


/**
 * The function createEndInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple end statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createEndInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    int instruction = HALT*10000;
    
    if( addInstructionToMemory( instruction ) == FAIL ) 
        return FAIL;  
    
    return SUCCESS;
}


/**
 * The function addStringToVariableMemorySpace is used by createLetInstruction to
 * stores a String Literal into a variable's MEMORY space.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int addStringToVariableMemorySpace( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Copy the first token (minus the quotes) */
    char copy[MAXLINELENGTH];
    removeFirstChar( copy, tokenArray[4] );

    if(endsWith( copy, '"') ) 
    {
        removeEndChar(copy); 
    }
    else 
    {
        /* Add the rest of the string literal */
        int idx = 5;
    
        if( idx < numberOfTokens )
        {
            while( ( idx < numberOfTokens-1 ) && 
                   ( endsWith( tokenArray[idx], '"' ) != 1 ) )
            {
                strcat2( copy, " " );
                strcat2( copy, tokenArray[idx++] );            
            }
            strcat2( copy, " " );
            strcat2( copy, tokenArray[idx] );
            removeEndChar(copy); 
        }        
    }

    int stringLen = strlen2(copy); 

    /* Store the string into memory as half words*/
    int address = variableExistsInTable( tokenArray[2][0] ); 

    if(MEMORY[address] == 0)
    {
        printf("Error - the string variable %c$ needs to be declared in a DIM statement\n",
               tokenArray[2][0]);
        printf("        prior to assigning a string literal to it\n");
        return FAIL;
    }
    else if( stringLen/2 > MEMORY[address]/1000) {
        printf("Error - string literal is longer than the memory space allocated for it\n");
        return FAIL;
    }

    /* Keep the space allocated to the string variable the same */
    int temp = (MEMORY[address]/1000) * 1000;

    int i;   
    for(i=0; i<stringLen; i++)
    {
        if(i%2==0) {
            temp+=(int)copy[i];
            MEMORY[address++] = temp;
        }
        else
            temp = (int)copy[i] * 1000;
    }
    
    if(i%2==0)
        MEMORY[address++] = temp;

    return SUCCESS;
}


/**
 * The function createLetInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple let statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createLetInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax checks*/
    if(numberOfTokens < 5)
        return FAIL;
    else if( isdigit(tokenArray[2][0]) )
        return FAIL;
    else if(tokenArray[3][0]!='=' )
        return FAIL;
        

    if(tokenArray[2][1] == '$') {
        return addStringToVariableMemorySpace( tokenArray, numberOfTokens );
    }

    /* Evaluate the expression on the RHS of the = sign */
    char postfix[ MAXLINELENGTH ][MAXTOKENLENGTH];
    int pfLength = convertToPostfix( tokenArray, postfix, 4, numberOfTokens );

    int variableAddress = variableExistsInTable( tokenArray[2][0] ); 

    /* If the let statement is assigning to an array element
     * adjust the memory address accordingly*/
    if(strlen2(tokenArray[2]) > 3 )
    {
        variableAddress = getElementAddressFromStr(tokenArray[2], variableAddress );

        if( variableAddress == -1 ) {
            return FAIL;
        }
    }
    
    int loadInstruction  = LOAD * 10000;
    int storeInstruction = STORE * 10000;
    
    int evalResult = evaluatePostfixExpression( postfix, pfLength );
    
    if( evalResult == FAIL)
        return FAIL;
    
    loadInstruction += evalResult;    
    storeInstruction += variableAddress; 
       
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = storeInstruction;
    }
    else {
        /* Load result of evaluation to the accumulator */
        if( addInstructionToMemory( loadInstruction ) == FAIL ) 
            return FAIL;  
        /* Store the accumulator value into the variable */ 
        if( addInstructionToMemory( storeInstruction ) == FAIL ) 
            return FAIL;        
    }

    return SUCCESS;
}


/**
 * The function createDimInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple dim statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createDimInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax checks*/
    if(numberOfTokens < 3)
        return FAIL;
    else if( !isalpha(tokenArray[2][0]) )
        return FAIL;
    else if( !endsWith(tokenArray[2], ')') )
        return FAIL;
      
    int multiplier = 10;
    int arraySize = 0;
    int idx=2;            /* first number in arraySize */
    
    /* Adjust the start index for extracting numbers if a
     * string variable is encountered */
    if(tokenArray[2][1]=='$') {
        idx++;
    }
    
    while(tokenArray[2][idx] != ')') {
        arraySize += tokenArray[2][idx++] - '0';
        arraySize *= multiplier;
    }
    
    arraySize /= 10;
    
    /* Do boundary checks on array size */
    if(arraySize < 1) {
        printf("\nThe minimum allowed array size is 1 element.");
        return FAIL;
    }
    else if(arraySize > MAXARRAYSIZE ) {
        printf("\nThe maximum allowed array size is %d elements.", MAXARRAYSIZE );
        return FAIL;
    }   
    
    /* set the first value of the variable to the arraySize */
    int addressOfVariable = variableExistsInTable(tokenArray[2][0]);
    
    if(addressOfVariable == -1)
         return FAIL;
    
    /* If this is a String variable:
     *   first update its address in the lookup table 
     *   then add its allowed length to the bottom of
     *   its allocated MEMORY space */
    if( strlen2(tokenArray[2])>1 && tokenArray[2][1]=='$' ) {
        if( updateStringVariableAddress( tokenArray[2][0] , arraySize ) == FAIL)
            return FAIL;
        addressOfVariable = variableExistsInTable(tokenArray[2][0]);
        MEMORY[ addressOfVariable ] = ( (arraySize/2) + 1 ) * 1000;
        return SUCCESS;
    }

    MEMORY[ addressOfVariable ] = arraySize;

    /* Check that there is space to allocate to the array variables */
    if(VARCONSTADDRESS-arraySize <= INSTRUCTIONCOUNTER )
        return FAIL;
        
    /* Reserve memory space for array elements */    
    int i;
    for(i=0; i<arraySize; i++)
        VARCONSTADDRESS--;
    
    return SUCCESS;
}


/**
 * The function createIfInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple if statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createIfInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax check*/
    if(numberOfTokens < 7) {
        return FAIL;
    }
    
    /* Get the index of the comparison operator in the if statement */
    int compOpIdx = getComparisonOperatorIndex( tokenArray, numberOfTokens);
    
    /* Syntax error if comparison operator not found 
     * or in a bad location */
    if( compOpIdx==-1 || compOpIdx < 3 || compOpIdx==numberOfTokens-1) {
        return FAIL;
    }
    
    /* If this is a string comparison */
    if( strlen2(tokenArray[2])>1 && tokenArray[2][1]=='$' ) {
        return doSTRCMP(tokenArray, numberOfTokens, compOpIdx );
    }
    
    /* Evaluate the conditional expression then goto */
    switch( isComparisonOperator(tokenArray[compOpIdx]) )
    {
        case LTOPERATOR:
            doLTJMP( tokenArray, numberOfTokens, compOpIdx );
            break;
        case GTOPERATOR:
            doGTJMP( tokenArray, numberOfTokens, compOpIdx );
            break;
        case LTEOPERATOR:
            doLTEJMP( tokenArray, numberOfTokens, compOpIdx );
            break;
        case GTEOPERATOR:
            doGTEJMP( tokenArray, numberOfTokens, compOpIdx );
            break;
        case EQOPERATOR:
            doEQJMP( tokenArray, numberOfTokens, compOpIdx );
            break;
        case NEOPERATOR:
            doNEJMP( tokenArray, numberOfTokens, compOpIdx );
            break;
        default:
            break;
    }
 
    return SUCCESS;
}


/**
 * The function createGosubInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple gosub statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createGosubInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax check*/
    if(numberOfTokens < 3) {
        return FAIL;
    }
    
    /* STORE the gosub return address into the variable assigned to store it */
    int loadInstruction  = LOAD*10000;
    int storeInstruction = STORE*10000;
    
    /* Set the return address to that of the line after this one  */
    int returnAddress = INSTRUCTIONCOUNTER + 3;
    
    if( addConstantToTable( returnAddress ) == -1 )
        return FAIL;
    
    loadInstruction += constantExistsInTable( returnAddress );
    
    if( addInstructionToMemory( loadInstruction ) == -1 ) 
        return FAIL;  
    
    int gosubVarAddress = variableExistsInTable( '@' );
    if(gosubVarAddress == -1)
        return FAIL;
        
    storeInstruction += gosubVarAddress;
    
    if( addInstructionToMemory( storeInstruction ) == FAIL ) 
        return FAIL;  
     
    /* Create a goto instruction to branch to the subroutine */
    int gotoInstruction = BRANCH*10000;

    int gotoLineNumber = strToInt(tokenArray[2]);    
    int gotoAddress = lineNumberExistsInTable( gotoLineNumber );
    
    if(gotoAddress != -1 )
        gotoInstruction += gotoAddress;
    else {
        Flags[ INSTRUCTIONCOUNTER ] = gotoLineNumber;
    }
    
    if( addInstructionToMemory( gotoInstruction ) == FAIL ) 
        return FAIL;  
    return SUCCESS;
}


/**
 * The function createReturnInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple return from a 
 * subroutine statement read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createReturnInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax check*/
    if(numberOfTokens < 2) {
        return FAIL;
    }
    
    int instruction1 = LOAD*10000;
    /* load instruction into ACCUMULATOR */
    /* Add the return address VALUE */
    /* Store in ACCUMULATOR ++ */
    /* This will dynamically create the return */
    
    int addressOfVariable = constantExistsInTable(BRANCH*10000); 
    
    if(addressOfVariable == -1)
         return FAIL;

    instruction1 += addressOfVariable;
    if( addInstructionToMemory( instruction1 ) == FAIL ) 
        return FAIL;  
    
    int addInstruction = ADD*10000;
    int returnAddress = variableExistsInTable( '@' );
    
    if(returnAddress == -1 )
        return FAIL;
    
    addInstruction += returnAddress;
    if( addInstructionToMemory( addInstruction ) == FAIL ) 
        return FAIL;  
    
    int storeInstruction = STORE*10000;
    storeInstruction += INSTRUCTIONCOUNTER+1;
    
    if( addInstructionToMemory( storeInstruction ) == FAIL ) 
        return FAIL;  
    /* Create a space for the BRANCH instruction to be placed */
    INSTRUCTIONCOUNTER++;
    return SUCCESS;
}


/**
 * The function findStepValueIndex is used to find and return the index of the
 * STEP keyword in the token array passed from createForInstruction.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return the index of the STEP keyword in the token array, otherwise FAIL
 *         if it was not found.
 */
int findStepValueIndex( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens )
{
    int svi = FAIL;
    if(numberOfTokens < 9)
        return svi;
       
    int idx; 
    for( idx=6; idx<numberOfTokens; idx++ ) {
        if(strcmp2(tokenArray[idx], "step") == 0 ) {
            svi = idx;
            break;
        }
    }
    
    return svi;
}


/**
 * The function findStepValueIndex is used to find and return the index of the
 * TO keyword in the token array passed from createForInstruction.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return the index of the TO keyword in the token array, otherwise FAIL
 *         if it was not found.
 */
int findToValueIndex( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens )
{
    int tvi = FAIL;
    if(numberOfTokens < 6)
        return tvi;
       
    int idx; 
    for( idx=5; idx<numberOfTokens; idx++ ) {
        if(strcmp2(tokenArray[idx], "to") == 0 ) {
            tvi = idx;
            break;
        }
    }
    
    return tvi;
}


/**
 * The function createForInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple for statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createForInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    int addressOfCountVariable;
    int addressOfStepValue;
    int startOfLoopAddress;
    
    /* Simple Syntax check*/
    if(numberOfTokens < 7) {
        return FAIL;
    }
    
    addressOfCountVariable = variableExistsInTable(tokenArray[2][0]); 
    int stepIndex = findStepValueIndex(tokenArray, numberOfTokens );
    
    if(stepIndex == -1) 
    {
        /* If a step value has not been declared use 1 as the default value */
        if( addConstantToTable( 1 ) == FAIL)
            return FAIL;
        addressOfStepValue = constantExistsInTable(1);
    }
    else {
        addressOfStepValue = constantExistsInTable( strToInt( tokenArray[stepIndex+1] ) );
    }
    
    int toIndex = findToValueIndex(tokenArray, numberOfTokens ); 
    
    /* For statements need a TO keyword*/
    if(toIndex == -1)
        return FAIL;
    
    /* Create a let statement */
    /* tokenArray[0] "let" tokenArray[2] tokenArray[3] .. to keyword */
    int i;
    char letStatement[ MAXLINELENGTH ][MAXTOKENLENGTH];
    for(i=0; i<toIndex; i++) {
        if(i==1)
            strcpy2(letStatement[i], "let");
        else
            strcpy2(letStatement[i], tokenArray[i]);
    }
    
    createLetInstruction( letStatement, toIndex );
    
    /* The loop starts here */
    startOfLoopAddress = INSTRUCTIONCOUNTER;
    
    /* Create the jmpGTEStatement */
    char jmpGTStatement[ MAXLINELENGTH ][MAXTOKENLENGTH];
    strcpy2( jmpGTStatement[0], tokenArray[0]);
    strcpy2( jmpGTStatement[1], "if");
    strcpy2( jmpGTStatement[2], tokenArray[2]);
    strcpy2( jmpGTStatement[3], ">");
    strcpy2( jmpGTStatement[4], tokenArray[toIndex+1]);
    strcpy2( jmpGTStatement[5], "goto");
    strcpy2( jmpGTStatement[6], tokenArray[0]);
       
    doGTJMP( jmpGTStatement , 7, 3 );
    
    /* Add the variables needed by the NEXT statement to the forLoopStack */
    pushFL( &ForLoopStackPtr, addressOfCountVariable, addressOfStepValue, 
                              startOfLoopAddress, INSTRUCTIONCOUNTER-1 );
    
    return SUCCESS;
}


/**
 * The function createNextInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple next statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createNextInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax check*/
    if(numberOfTokens < 2) {
        return FAIL;
    }
    
    int stackPopped[4];
    popFL( &ForLoopStackPtr, stackPopped );  
    /* contains - addressOfCountVariable,addressOfStepValue, 
     *            startOfLoopAddress, jmpGTAddress */
    
    /* Augment the count variable of the For loop */
    int loadInstruction  = LOAD * 10000;
    loadInstruction += stackPopped[0];
    if( addInstructionToMemory( loadInstruction ) == FAIL ) 
        return FAIL;  
    
    int addInstruction   = ADD * 10000;
    addInstruction += stackPopped[1];
    if( addInstructionToMemory( addInstruction ) == FAIL ) 
        return FAIL;  
    
    int storeInstruction = STORE * 10000;
    storeInstruction += stackPopped[0];
    if( addInstructionToMemory( storeInstruction ) == FAIL ) 
        return FAIL;  
    
    int branchInstruction = BRANCH * 10000;
    branchInstruction += stackPopped[2];
    if( addInstructionToMemory( branchInstruction ) == FAIL ) 
        return FAIL;  
    
    /* Correct the goto addresses for the conditional branch created in
     * createForInstruction to point to the first instruction after
     * the NEXT instructions */
    int branchPosInstruction = BRANCHPOS*10000;
    branchPosInstruction += INSTRUCTIONCOUNTER;
    
    MEMORY[ stackPopped[3] ] = branchPosInstruction;
    
    return SUCCESS;
}


/**
 * The function createNewlineInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple newline statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createNewlineInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* Simple Syntax check*/
    if(numberOfTokens < 2) {
        return FAIL;
    }
    
    /* Augment the count variable of the For loop */
    int instruction  = NEWLINE * 10000;
    if( addInstructionToMemory( instruction ) == FAIL ) 
        return FAIL;  
    
    return SUCCESS;
}

/**
 * The function createFirstSML is used during the compiler's first pass
 * of the Simple source file to create SML instructions
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the line parsed correctly, otherwise FAIL.
 */
int createFirstSML( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    if( numberOfTokens == 0 ) {
        printf("\nSyntax Error! Lines cannot be left empty!\n");
        return FAIL;
    }
    
    if(strcmp2( tokenArray[1], "rem" ) == 0 )
        return SUCCESS;
    else if(strcmp2( tokenArray[1], "input" ) == 0 )
        return createInputInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "print" ) == 0 )
        return createPrintInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "goto" ) == 0 )
        return createGotoInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "end" ) == 0 )
        return createEndInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "let" ) == 0 )
        return createLetInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "dim" ) == 0 )
        return createDimInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "if" ) == 0 )
        return createIfInstruction( tokenArray, numberOfTokens );   
    else if(strcmp2( tokenArray[1], "gosub" ) == 0 )
        return createGosubInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "return" ) == 0 )
        return createReturnInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "for" ) == 0 )
        return createForInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "next" ) == 0 )
        return createNextInstruction( tokenArray, numberOfTokens );   
    else if(strcmp2( tokenArray[1], "newline" ) == 0 )
        return createNewlineInstruction( tokenArray, numberOfTokens );
    else {
        printf("\nInvalid command \'%s\'", tokenArray[1]);
        return FAIL;
    }
    
    return SUCCESS;
}


/**
 * The function dumpTableEntries is used to print out the current
 * contents of the Symbol Table to the screen.
 */
void dumpTableEntries()
{
    int i;
    printf( "\n---- Symbol Table Contents ----\n\n" );
    for( i=0; i<TABLEPOSITION; i++ )
    {
        printf( "---- Entry #%d ----\n", i);
        
        if(Table[i].type == 'V')
            printf( "Symbol   = %c\n", Table[i].symbol );
        else
            printf( "Symbol   = %d\n", Table[i].symbol );
        
        printf( "Type     = %c\n", Table[i].type );
        printf( "Location = %d\n\n", Table[i].location );
    }
}


 /**
  * The function variableExistsInTable checks whether the variable symbol
  * exists in the lookup table or not.
  * @param symbol A variable to look for in the Symbol Table.
  * @return The address assigned to the Symbol in MEMORY, or if
  *         the symbol can not be found -1.
  */
int variableExistsInTable( char symbol )
{
    int i;
    for( i=0; i<TABLEPOSITION; i++ )
    {
        if(Table[i].type == 'V') 
        {
            if(Table[i].symbol == symbol )
                return Table[i].location;
        }
    }
    return -1;
}


 /**
  * The function constantExistsInTable checks whether the constant value
  * exists in the lookup table or not.
  * @param symbol A constant to look for in the Symbol Table.
  * @return The address assigned to the constant in MEMORY, or if
  *         the line number can not be found -1.
  */
int constantExistsInTable( int value )
{
    int i;
    for( i=0; i<TABLEPOSITION; i++ )
    {
        if(Table[i].type == 'C') 
        {
            if(Table[i].symbol == value )
                return Table[i].location;
        }
    }
    return -1;
}


 /**
  * The function lineNumberExistsInTable checks whether the line number value
  * exists in the lookup table or not.
  * @param symbol A line number to look for in the Symbol Table.
  * @return The address assigned to the line number in MEMORY, or if
  *         the line number can not be found -1.
  */
int lineNumberExistsInTable( int value )
{
    int i;
    for( i=0; i<TABLEPOSITION; i++ )
    {
        if(Table[i].type == 'L') 
        {
            if(Table[i].symbol == value )
                return Table[i].location;
        }
    }
    return -1;
}


/* The method convertToPostfix takes an infix expression stored in an
 * array and converts it to a postfix expression stored in an array.
 * @param infix A tokenised Simple statement containing an infix expression.
 * @param postfix An array to store the converted expression strings in.
 * @param start The index of the first token of the infix expression.
 * @param end The index of the last token of the infix expression.
 * @return The length of the postfix expression.
 */
int convertToPostfix( char infix[][MAXTOKENLENGTH], char postfix[][MAXTOKENLENGTH], int start, int end )
{
    int i=start, postFixLength=0;   
    char c;
    
    /* Push left parenthesis to stack */
    StackNodePtr stackPtr = NULL;
    push( &stackPtr, '(' ); 

    infix[end][0] = ')';
    
    /* Do the conversion */
    while( !isEmpty( stackPtr ) && i <= end )
    {
        c = infix[i][0];
        
        if( c=='-' && strlen2(infix[i])>1  && isdigit(infix[i][1]) )
            strcpy2(postfix[ postFixLength++ ], infix[i]);
        
        else if( isdigit(c) )  
            strcpy2(postfix[ postFixLength++ ], infix[i]);
        
        else if( c == '(')
            push( &stackPtr, '(' );
        
        else if( isOperator(c) == 1 ) 
        {
            if( !isEmpty( stackPtr ) && isOperator( stackTop(stackPtr) ) ) {
                while( isOperator( stackTop(stackPtr) ) && 
                       (precedence( stackTop(stackPtr), c )) >= 0 ) 
                {
                    postfix[ postFixLength ][0] = pop( &stackPtr );
                    postfix[ postFixLength++ ][1] = '\0';
                }
                push( &stackPtr, c );
            }
            else
                push( &stackPtr, c );
        }
        else if( c == ')') 
        {
            if( !isEmpty( stackPtr ) ) 
            {
                c = pop( &stackPtr ); 

                while( !isEmpty( stackPtr ) && c != '(' ) {
                    postfix[ postFixLength ][0] = c;
                    postfix[ postFixLength++ ][1] = '\0';
                    c = pop( &stackPtr ); 
                }
            }
        }
        else {
            strcpy2( postfix[ postFixLength++ ], infix[i]);
        }
        
        i++;
    }
    
    return postFixLength;
}


/**
 * The function precendence compares operator1 with operator2 to determine
 * which has the higher precedence.
 * @param operator1 A methematical operator.
 * @param operator2 A methematical operator.
 * @return -1 if operator1 has lower precedence than operator2,
 *          0 if it has the same precedence, and 1 if it has higher precedence. 
 */
int precedence( char operator1, char operator2 )
{
    int result = 1;

    switch( operator1 )
    {
        case '^':
            if( operator2 == '^') result = 0;
            break;
        case '*': case '/': case '%':
            switch( operator2 ) {
                case '^':
                    result = -1;
                    break;
                case '*': case '/': case '%':
                    result = 0;
                    break;
                default:
                    break;
            }
            break;
        case '+': case '-': 
            switch( operator2 ) {
                case '-': case '+':
                    result = 0;
                    break;
                default:
                    result = -1;
                    break;
            }
            break;
    }

    return result;
}


/**
 * The function evaluatePostfixExpression creates the SML instructions 
 * needed to evaluate the postfix expression expr. It returns the memory 
 * address where the instructions will store the result of the evaluation.
 * @param postfix An array containing a postfix expression. 
 * @param pfLength The length of the postfix array.
 * @result The memory address where the instructions will store the 
 *         result of the evaluation, otherwise FAIL if the expression could 
 *         not be evaluated. 
 */
int evaluatePostfixExpression( char postfix[][MAXTOKENLENGTH], int pfLength )
{
    StackNodePtr stackPtr = NULL;
    int x, y;
    int i=0;
    int address, calcReturn;
    char c;
    
    
    while( i < pfLength )
    {
        c = postfix[i][0];
        
        /* Must also handle negative numbers */
        if( isdigit( c ) || ( c=='-' && strlen2(postfix[i])>1  && isdigit(postfix[i][1]) ) )
        {
            int number;
            sscanf(postfix[i], "%d", &number);
            
            address = constantExistsInTable( number );
            if(address==-1) 
                return FAIL;
            
            push( &stackPtr, address );
        }
        /* Alter to deal with array indicies when they appear */
        else if( isalpha( c ) ) 
        {
            address = variableExistsInTable( c );
            if(address==-1) 
                return FAIL;
            /* If an array element is being dealt with,
             * adjust the memory address accordingly*/
            if(strlen2(postfix[i]) > 3 )
            {
                address = getElementAddressFromStr(postfix[i], address );
        
                if( address == -1 )
                    return FAIL;
            }
            
            push( &stackPtr, address ); 
        }
        else if( isOperator( c ) )
        {
            if(isEmpty( stackPtr ) ) {
                printf("Invalid postfix expression!\n");
                return FAIL;
            }
            x = pop( &stackPtr );
            
            if(isEmpty( stackPtr ) ) {
                printf("Invalid postfix expression!\n");
                return FAIL;
            }
            y = pop( &stackPtr );
            
            calcReturn = calculate( y, x, c );
            if(calcReturn == FAIL) 
                return FAIL;
            
            push( &stackPtr, calcReturn );
        }
        i++;
    }
    
    if(isEmpty( stackPtr ) ) {
        printf("Invalid postfix expression!\n");
        return FAIL;
    }
    
    return pop( &stackPtr );
}


/**
 * The function calculate is used to create instructions which will
 * perform various mathematical operations.
 * @param op1 The first operand in the math operation
 * @param op2 The second operand in the math operation
 * @param theOperator The operator used in the math operation.
 * @result The memory address where the instructions will store the 
 *         result of the math operation, otherwise FAIL.
 */
int calculate( int op1, int op2, char theOperator )
{   
    /* Check that there is space to allocate to the temporary variable */
    if(VARCONSTADDRESS <= INSTRUCTIONCOUNTER )
        return FAIL;
        
    int tempStorage = VARCONSTADDRESS--;
    
    int loadInstruction = LOAD * 10000;
    loadInstruction += op1;
    
    int storeInstruction = STORE * 10000;
    storeInstruction += tempStorage;
    
    int addInstruction = ADD * 10000;
    int subInstruction = SUBTRACT * 10000;
    int mulInstruction = MULTIPLY * 10000;
    int divInstruction = DIVIDE * 10000;
    int expInstruction = EXPONENTIATION * 10000;
    int modInstruction = MODULUS * 10000;
    
    switch( theOperator )
    {
        case '+':
            if( addInstructionToMemory( loadInstruction ) == FAIL ) 
                return FAIL;  // load op1 to accumulator
        
            addInstruction += op2;
            if( addInstructionToMemory( addInstruction ) == FAIL ) 
                return FAIL;  // add op2  
            
            if( addInstructionToMemory( storeInstruction ) == FAIL ) 
                return FAIL;  // store result to tempStorage
            break;
        case '-':
            if( addInstructionToMemory( loadInstruction ) == FAIL ) 
                return FAIL;  // load op1 to accumulator 
            
            subInstruction += op2;
            if( addInstructionToMemory( subInstruction ) == FAIL ) 
                return FAIL;    // subtract op2
            
            if( addInstructionToMemory( storeInstruction ) == FAIL ) 
                return FAIL;  // store result to tempStorage
            break;
        case '*':
            if( addInstructionToMemory( loadInstruction ) == FAIL ) 
                return FAIL;  // load op1 to accumulator
            
            mulInstruction += op2;
            if( addInstructionToMemory( mulInstruction ) == FAIL ) 
                return FAIL;  // multiply by op2 
            
            if( addInstructionToMemory( storeInstruction ) == FAIL ) 
                return FAIL;  // store result to tempStorage
            break;
        case '/':
            if( addInstructionToMemory( loadInstruction ) == FAIL ) 
                return FAIL;  // load op1 to accumulator
            
            divInstruction += op2;
            if( addInstructionToMemory( divInstruction ) == FAIL ) 
                return FAIL;  // divide by op2  
            
            if( addInstructionToMemory( storeInstruction ) == FAIL ) 
                return FAIL;  // store result to tempStorage
            break;
        case '^':
            if( addInstructionToMemory( loadInstruction ) == FAIL ) 
                return FAIL;  // load op1 to accumulator
            
            expInstruction += op2;
            if( addInstructionToMemory( expInstruction ) == FAIL ) 
                return FAIL;  // raise to the power of op2
            
            if( addInstructionToMemory( storeInstruction ) == FAIL ) 
                return FAIL;  // store result to tempStorage
            break;
        case '%':
            if( addInstructionToMemory( loadInstruction ) == FAIL ) 
                return FAIL;  // load op1 to accumulator
            
            modInstruction += op2;
            if( addInstructionToMemory( modInstruction ) == FAIL ) 
                return FAIL;  // modulo by op2 
            
            if( addInstructionToMemory( storeInstruction ) == FAIL ) 
                return FAIL;  // store result to tempStorage
            break;
        default:
            break;
    }
    
    return tempStorage;
}


/**
 * The function getComparisonOperatorIndex returns the index of the 
 * comparison operator within the tokenised line of Simple code in
 * the tokens array.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param length The number of tokens contained in tokenArray.
 * @return The index of the comparison operator within the tokenised line
 *         of Simple code, otherwise -1 if a comparison operator is
 *         not found.
 */
int getComparisonOperatorIndex( char tokens[ ][ MAXTOKENLENGTH ], int length )
{
    int idx, idx2;
    
    for( idx=3; idx<length; idx++ ) {
        for( idx2=0; idx2<NUMBEROFCOMPOPERATORS; idx2++ ) 
        {
            if(strcmp2(tokens[idx], compOperators[idx2]) == 0 )
                return idx;
        }   
    }
    
    return FAIL;
}


/**
 * The function isComparisonOperator returns the index of the comparison
 * operator, contained within the test string, from the compOperators array.
 * @param test A comparison operator.
 * @return The index of the comparison operator in the compOperators array,
 *         else FAIL if the test string could not be found in the array.
 */
int isComparisonOperator( char *test ) 
{
    int idx;
    for( idx=0; idx<NUMBEROFCOMPOPERATORS; idx++ ) 
    {
        if(strcmp2(test, compOperators[idx]) == 0 )
            return idx;
    }   
    return FAIL;
}


/**
 * The function doLTJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x < y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doLTJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int ltIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];  
    char RHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];

    int pfLengthLHS = convertToPostfix( tokenArray, LHSPostfix, 2, ltIndex );
    int pfLengthRHS = convertToPostfix( tokenArray, RHSPostfix, ltIndex+1, numberOfTokens-2 ); 
    
    RHSAddress = evaluatePostfixExpression( RHSPostfix, pfLengthRHS );
    LHSAddress = evaluatePostfixExpression( LHSPostfix, pfLengthLHS );

    if(RHSAddress == FAIL || LHSAddress == FAIL)
        return FAIL;

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;

    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;
       
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        if( addInstructionToMemory( instruction1 ) == FAIL ) 
            return FAIL;  
        if( addInstructionToMemory( instruction2 ) == FAIL ) 
            return FAIL;  
    }

    /* Branch if accumulator is less than zero */
    int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
    
    returnAddress = lineNumberExistsInTable( returnLineNumber );

    int instruction3 = BRANCHNEG * 10000;
    
    if(returnAddress != -1 ) {
        instruction3 += returnAddress;
    }  
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
    }
    
    if( addInstructionToMemory( instruction3 ) == FAIL ) 
        return FAIL;
          
    return SUCCESS;
}           


/**
 * The function doGTJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x > y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doGTJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int gtIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];   
    char RHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];

    int pfLengthLHS = convertToPostfix( tokenArray, LHSPostfix, 2, gtIndex );
    int pfLengthRHS = convertToPostfix( tokenArray, RHSPostfix, gtIndex+1, numberOfTokens-2 ); 
    
    RHSAddress = evaluatePostfixExpression( RHSPostfix, pfLengthRHS );
    LHSAddress = evaluatePostfixExpression( LHSPostfix, pfLengthLHS );

    if(RHSAddress == FAIL || LHSAddress == FAIL)
        return FAIL;

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;
 
    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;    
           
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        if( addInstructionToMemory( instruction1 ) == FAIL ) 
            return FAIL;  
        if( addInstructionToMemory( instruction2 ) == FAIL ) 
            return FAIL;  
    }

    /* Branch if accumulator is greater than zero */
    int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
    
    returnAddress = lineNumberExistsInTable( returnLineNumber );

    int instruction3 = BRANCHPOS*10000;
    
    if(returnAddress != -1 ) {
        instruction3 += returnAddress;
    }
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
    }

    if( addInstructionToMemory( instruction3 ) == FAIL ) 
        return FAIL;

    return SUCCESS;
}   


/**
 * The function doLTEJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x <= y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */         
int doLTEJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int lteIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];  
    char RHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];

    int pfLengthLHS = convertToPostfix( tokenArray, LHSPostfix, 2, lteIndex ); 
    int pfLengthRHS = convertToPostfix( tokenArray, RHSPostfix, lteIndex+1, numberOfTokens-2 ); 

    RHSAddress = evaluatePostfixExpression( RHSPostfix, pfLengthRHS );    
    LHSAddress = evaluatePostfixExpression( LHSPostfix, pfLengthLHS );

    if(RHSAddress == FAIL || LHSAddress == FAIL)
        return FAIL;

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;
        
    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;         
               
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        if( addInstructionToMemory( instruction1 ) == FAIL ) 
            return FAIL;  
        if( addInstructionToMemory( instruction2 ) == FAIL ) 
            return FAIL;  
    } 

    /* Branch if accumulator is less than or equal to zero */
    int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
    
    returnAddress = lineNumberExistsInTable( returnLineNumber );

    int instruction3 = BRANCHNEG*10000;
    int instruction4 = BRANCHZERO*10000;
    
    if(returnAddress != -1 ) {
        instruction3 += returnAddress;
        instruction4 += returnAddress;
    }       
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
        Flags[ INSTRUCTIONCOUNTER+1 ] = returnLineNumber;
    }
    
    if( addInstructionToMemory( instruction3 ) == FAIL ) 
        return FAIL;  
    if( addInstructionToMemory( instruction4 ) == FAIL ) 
        return FAIL;  

    return SUCCESS;
}           


/**
 * The function doGTEJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x >= y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doGTEJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int gteIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];   
    char RHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];

    int pfLengthLHS = convertToPostfix( tokenArray, LHSPostfix, 2, gteIndex ); 
    int pfLengthRHS = convertToPostfix( tokenArray, RHSPostfix, gteIndex+1, numberOfTokens-2 ); 

    RHSAddress = evaluatePostfixExpression( RHSPostfix, pfLengthRHS );    
    LHSAddress = evaluatePostfixExpression( LHSPostfix, pfLengthLHS );

    if(RHSAddress == FAIL || LHSAddress == FAIL)
        return FAIL;

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;
    
    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;   
            
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        if( addInstructionToMemory( instruction1 ) == FAIL ) 
            return FAIL;  
        if( addInstructionToMemory( instruction2 ) == FAIL ) 
            return FAIL;  
    } 

    /* Branch if accumulator is greater than or equal to zero */
    int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
    
    returnAddress = lineNumberExistsInTable( returnLineNumber );

    int instruction3 = BRANCHPOS*10000;
    int instruction4 = BRANCHZERO*10000;
    
    if(returnAddress != -1 ) {
        instruction3 += returnAddress;
        instruction4 += returnAddress;
    }  
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
        Flags[ INSTRUCTIONCOUNTER+1 ] = returnLineNumber;
    }
    
    if( addInstructionToMemory( instruction3 ) == FAIL ) 
        return FAIL; 
    if( addInstructionToMemory( instruction4 ) == FAIL ) 
        return FAIL;  

    return SUCCESS;
}   

    
/**
 * The function doEQJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x == y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doEQJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int eqIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];  
    char RHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];

    int pfLengthLHS = convertToPostfix( tokenArray, LHSPostfix, 2, eqIndex ); 
    int pfLengthRHS = convertToPostfix( tokenArray, RHSPostfix, eqIndex+1, numberOfTokens-2 ); 
    
    RHSAddress = evaluatePostfixExpression( RHSPostfix, pfLengthRHS ); 
    LHSAddress = evaluatePostfixExpression( LHSPostfix, pfLengthLHS );

    if(RHSAddress == FAIL || LHSAddress == FAIL)
        return FAIL;

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;

    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;      
             
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        if( addInstructionToMemory( instruction1 ) == FAIL ) 
            return FAIL;  
        if( addInstructionToMemory( instruction2 ) == FAIL ) 
            return FAIL;
    } 

    /* Branch if accumulator is equal to zero */
    int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
    returnAddress = lineNumberExistsInTable( returnLineNumber );

    int instruction3 = BRANCHZERO*10000;

    if(returnAddress != -1 )
        instruction3 += returnAddress;
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
    }
    
    if( addInstructionToMemory( instruction3 ) == FAIL ) 
        return FAIL;  

    return SUCCESS;
}           


/**
 * The function doNEJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x != y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doNEJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int neIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];  
    char RHSPostfix[ MAXLINELENGTH ][MAXTOKENLENGTH];

    int pfLengthLHS = convertToPostfix( tokenArray, LHSPostfix, 2, neIndex ); 
    int pfLengthRHS = convertToPostfix( tokenArray, RHSPostfix, neIndex+1, numberOfTokens-2 ); 

    RHSAddress = evaluatePostfixExpression( RHSPostfix, pfLengthRHS );    
    LHSAddress = evaluatePostfixExpression( LHSPostfix, pfLengthLHS );

    if(RHSAddress == FAIL || LHSAddress == FAIL)
        return FAIL;

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;

    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;
       
    /* Optimise if this was a production*/
    if( (INSTRUCTIONCOUNTER-1 > 2) &&  
        (MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE) && 
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 < BRANCH) &&
        (MEMORY[INSTRUCTIONCOUNTER-2]/10000 != LOAD) )
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        if( addInstructionToMemory( instruction1 ) == FAIL ) 
            return FAIL; 
        if( addInstructionToMemory( instruction2 ) == FAIL ) 
            return FAIL;
    } 

    /* Branch if accumulator is not equal to zero */
    int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
    
    returnAddress = lineNumberExistsInTable( returnLineNumber );

    int instruction3 = BRANCHNEG*10000;
    int instruction4 = BRANCHPOS*10000;
    
    if(returnAddress != -1 ) {
        instruction3 += returnAddress;
        instruction4 += returnAddress;
    }
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
        Flags[ INSTRUCTIONCOUNTER+1 ] = returnLineNumber;
    }
    
    if( addInstructionToMemory( instruction3 ) == FAIL ) 
        return FAIL; 
    if( addInstructionToMemory( instruction4 ) == FAIL ) 
        return FAIL;  

    return SUCCESS;
}


/**
 * The function doSTRCMP creates the necessary instructions to perform
 * the SML equivalent of a Simple string compare. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @param cmpOpIndex The index of the comparison operator in tokenArray
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doSTRCMP(char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int cmpOpIndex )
{
    /* Compare the strings */
    if( doSTREQ( tokenArray, numberOfTokens, cmpOpIndex ) == FAIL)
        return FAIL;

    if( strcmp2(tokenArray[cmpOpIndex], "==" ) == 0) 
    {
        /* Branch if accumulator is equal to zero */
        int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
        int returnAddress = lineNumberExistsInTable( returnLineNumber );

        int instruction3 = BRANCHZERO*10000;

        if(returnAddress != -1 )
            instruction3 += returnAddress;
        else {
            Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
        }
        
        if( addInstructionToMemory( instruction3 ) == FAIL ) 
            return FAIL;  
    }
    else if( strcmp2(tokenArray[cmpOpIndex], "!=" ) == 0) 
    {
         /* Branch if accumulator is not equal to zero */
        int returnLineNumber = strToInt(tokenArray[numberOfTokens-1]);
        
        int returnAddress = lineNumberExistsInTable( returnLineNumber );

        int instruction3 = BRANCHNEG*10000;
        int instruction4 = BRANCHPOS*10000;
        
        if(returnAddress != -1 ) {
            instruction3 += returnAddress;
            instruction4 += returnAddress;
        }
        else {
            Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
            Flags[ INSTRUCTIONCOUNTER+1 ] = returnLineNumber;
        }
        
        if( addInstructionToMemory( instruction3 ) == FAIL ) 
            return FAIL; 
        if( addInstructionToMemory( instruction4 ) == FAIL ) 
            return FAIL;  
    }
    else {
        printf("Error - comparing strings with %s is not implemented yet!\n", tokenArray[cmpOpIndex]);
        return FAIL;
    }
    
    return SUCCESS; 
}


/**
 * The function doSTREQ creates the necessary instructions to perform
 * the SML equivalent of a Simple string compare to check whether two
 * strings are equal. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @param cmpOpIndex The index of the comparison operator in tokenArray
 * @return SUCCESS if the instructions were successfully created, otherwise FAIL.
 */
int doSTREQ( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int cmpOpIndex )
{
    /* #######################################################
     *     Initialise the variables used by this function
     * #######################################################
     */

    int idxA;
    idxA = cmpOpIndex - 1;
    int idxB;
    idxB = cmpOpIndex + 1;
    
    int loadInstruction = LOAD*10000;
    int divideInstruction = DIVIDE*10000;
    int storeInstruction = STORE*10000;
    int multInstruction = MULTIPLY*10000;
    int addInstruction = ADD*10000;
    int subInstruction = SUBTRACT*10000;
    int branchNegInst = BRANCHNEG*10000;
    int branchZeroInst = BRANCHZERO*10000;
    int branchPosInst = BRANCHPOS*10000;
    
    int exitInstruction;
    exitInstruction = INSTRUCTIONCOUNTER+40;
    
    
    /* ----------------------------------
       get address of first string
       store into VARCONSTADDRESS--
       store address of variable to int   
       ---------------------------------- */
    int addressA;
    addressA = variableExistsInTable(tokenArray[idxA][0]);
    
    if(addressA == -1)
        return FAIL;
    
    /* Store start position in A */
    MEMORY[VARCONSTADDRESS] = addressA;
    
    int startOfA;                    
    startOfA = VARCONSTADDRESS--;
    
    /* Store current position in A */
    MEMORY[VARCONSTADDRESS] = addressA;
    
    int positionInA;
    positionInA = VARCONSTADDRESS--;
    
    /* ----------------------------------   
       get address of second string
       store into VARCONSTADDRESS--
       store address of variable to int
       ---------------------------------- */
    int addressB;
    
    /* Is this a string literal? */
    if(tokenArray[idxB][0] == '"' ) {
        addressB = addStringLiteralToMemory( tokenArray, numberOfTokens, idxB );     
    }
    else {
        addressB = variableExistsInTable(tokenArray[idxB][0]);      
    }

    if(addressB == -1)
        return FAIL;

    /* Store start position in B */
    MEMORY[VARCONSTADDRESS] = addressB;
    
    int startOfB;                    
    startOfB = VARCONSTADDRESS--;
    
    /* Store current position in A */
    MEMORY[VARCONSTADDRESS] = addressB;
    
    int positionInB;
    positionInB = VARCONSTADDRESS--;
    
    /* ----------------------------------  
       addConstantsToTable 1, 1000
       store addresses of variables to int
       ---------------------------------- */
    addConstantToTable(1);   
    int one = constantExistsInTable( 1 );
    if(one == -1)
        return FAIL;
        
    addConstantToTable(1000);   
    int thousand = constantExistsInTable( 1000 );
    if(thousand == -1)
        return FAIL;        
        
    /* ---------------------------------- 
       addConstantToTable LOAD * 10000
       store address of variable to int
       ---------------------------------- */
    addConstantToTable(LOAD*10000);   
    int loadA = constantExistsInTable( LOAD*10000 );
    if(loadA == -1)
        return FAIL;
        
    /* ---------------------------------- 
       addConstantToTable SUBTRACT * 10000
       store address of variable to int
       ---------------------------------- */
    addConstantToTable(SUBTRACT*10000);   
    int subB = constantExistsInTable( SUBTRACT*10000 );
    if(subB == -1)
        return FAIL;
    /* ---------------------------------- */
    
    /* #######################################################
     *  load the first byte of a$ to get and store strlen 1-5
     * #######################################################
     */
    /* load the first byte of a$ */
    if( addInstructionToMemory( loadInstruction + addressA ) == FAIL ) 
        return FAIL;
    
    /* divide by 1000 */
    if( addInstructionToMemory( divideInstruction + thousand ) == FAIL ) 
        return FAIL;
    
    /* store strlen for a$ */
    int strlenAAddress;
    strlenAAddress = VARCONSTADDRESS;
    
    if( addInstructionToMemory( storeInstruction + strlenAAddress ) == FAIL ) 
        return FAIL;
    
    VARCONSTADDRESS--;
    
    /* multiply by 1000 */
    if( addInstructionToMemory( multInstruction + thousand ) == FAIL ) 
        return FAIL;
        
    /* store result of strLen(a$)*1000 */
    int strlenAThousand;
    strlenAThousand = VARCONSTADDRESS;
    
    if( addInstructionToMemory( storeInstruction + strlenAThousand ) == FAIL ) 
        return FAIL;
        
    VARCONSTADDRESS--;
    
    /* #######################################################
     *               store MAX of for-loop 6-8
     * #######################################################
     */
    
    /* load address of a$ */
    if( addInstructionToMemory( loadInstruction + positionInA ) == FAIL ) 
        return FAIL;
        
    /* add strlen(a$) to create MAX for for-loop */
    if( addInstructionToMemory( addInstruction + strlenAAddress ) == FAIL ) 
        return FAIL;
        
    /* store MAX */
    int maxA;
    maxA = VARCONSTADDRESS;
    
    if( addInstructionToMemory( storeInstruction + maxA ) == FAIL ) 
        return FAIL;
 
    VARCONSTADDRESS--;
        
    /* ########################################################
     *            get and store first char of a$ 9-11
     * ########################################################
     */
    
    /* load first byte of a$ */
    if( addInstructionToMemory( loadInstruction + addressA ) == FAIL ) 
        return FAIL;    

    /* subtract strlen*1000 of a$ to get first char */
    if( addInstructionToMemory( subInstruction + strlenAThousand ) == FAIL ) 
        return FAIL;
    
    /* store first char of a$ */
    int tempA;
    tempA = VARCONSTADDRESS;
    
    if( addInstructionToMemory( storeInstruction + tempA ) == FAIL ) 
        return FAIL;
        
    VARCONSTADDRESS--;
    
    /* #######################################################
     *  load first char of b$ into the Accumulator 12-17
     * #######################################################
     */
     
    /* load the first byte of b$ */
    if( addInstructionToMemory( loadInstruction + addressB ) == FAIL ) 
        return FAIL;    
        
    /* divide by 1000 */
    if( addInstructionToMemory( divideInstruction + thousand ) == FAIL ) 
        return FAIL;
     
    /* multiply by 1000 */
    if( addInstructionToMemory( multInstruction + thousand ) == FAIL ) 
        return FAIL;
     
    /* store strlen(b$)*1000 */
    int strlenBThousand;
    strlenBThousand = VARCONSTADDRESS;
    
    if( addInstructionToMemory( storeInstruction + strlenBThousand ) == FAIL ) 
        return FAIL;
        
    VARCONSTADDRESS--;
    
    /* load the first byte of b$ */
    if( addInstructionToMemory( loadInstruction + addressB ) == FAIL ) 
        return FAIL;    
    
    /* subtract strlen(b$)*1000 to get first char */
    if( addInstructionToMemory( subInstruction + strlenBThousand ) == FAIL ) 
        return FAIL;

    /* #######################################################
     *      compare first char of a$ with first char of b$
     *       if they are not equal skip the for loop 18-20
     * #######################################################
     */  
    
    /* subtract 1st char of a$ from 1st char of b$ */
    if( addInstructionToMemory( subInstruction + tempA ) == FAIL ) 
        return FAIL;

    /* branchneg   ie not equal to 
     * branch after the exitroutine which checks in cases where a$ matches b$
     * that b$ does not have extra characters
     */
    if( addInstructionToMemory( branchNegInst + exitInstruction+4 ) == FAIL ) 
        return FAIL;

    /* branchpos   ie not equal to */
    if( addInstructionToMemory( branchPosInst + exitInstruction+4 ) == FAIL ) 
        return FAIL;
        
    /* #######################################################
     *        for loop to compare the rest of a$ with b$
     *            increment the position in a$ 21-25
     * #######################################################
     */
     
    /* load current position in a$ */
    if( addInstructionToMemory( loadInstruction + positionInA ) == FAIL ) 
        return FAIL;
    
    /* add 1 */
    if( addInstructionToMemory( addInstruction + one ) == FAIL ) 
        return FAIL;
    
    /* store incremented position */
    if( addInstructionToMemory( storeInstruction + positionInA ) == FAIL ) 
        return FAIL;
    
    /* subtract MAX */
    if( addInstructionToMemory( subInstruction + maxA ) == FAIL ) 
        return FAIL;
    
    /* BRANCHZERO */
    if( addInstructionToMemory( branchZeroInst + exitInstruction ) == FAIL ) 
        return FAIL;
    
    /* #######################################################
     *            increment the position in b$ 26-28
     * #######################################################
     */

    /* load current position in b$ */
    if( addInstructionToMemory( loadInstruction + positionInB ) == FAIL ) 
        return FAIL;
    
    /* add 1 */
    if( addInstructionToMemory( addInstruction + one ) == FAIL ) 
        return FAIL;
    
    /* store incremented position */
    if( addInstructionToMemory( storeInstruction + positionInB ) == FAIL ) 
        return FAIL;
        
    /* #######################################################
     *   create a load instruction for position in a$ 29-31
     * #######################################################
     */
     
    /* load LOAD instruction */
    if( addInstructionToMemory( loadInstruction + loadA ) == FAIL ) 
        return FAIL; 
    
    /* add current position in a$ */
    if( addInstructionToMemory( addInstruction + positionInA ) == FAIL ) 
        return FAIL;    
    
    /* store 4 instructions from the current one */
    if( addInstructionToMemory( storeInstruction + INSTRUCTIONCOUNTER+4 ) == FAIL ) 
        return FAIL;
        
    /* #######################################################
     * create a subtract instruction for position in b$ 32-34
     * #######################################################
     */
     
    /* load SUBTRACT instruction */
    if( addInstructionToMemory( loadInstruction + subB ) == FAIL ) 
        return FAIL;
    
    /* add current position in b$ */
    if( addInstructionToMemory( addInstruction + positionInB ) == FAIL ) 
        return FAIL;
    
    /* store 3 instructions from the current one */
    if( addInstructionToMemory( storeInstruction + INSTRUCTIONCOUNTER+3 ) == FAIL ) 
        return FAIL;
     
    /* #######################################################
     *  BRANCH to beginning of for-loop if values are equal
     * #######################################################
     */
    
    /* First increment the INSTRUCTIONCOUNTER to make space 
     * for the two instructions added above */
    INSTRUCTIONCOUNTER++;  /* Make space for load a$ chars*/
        
    /* ********************************************************************** */    
    /* If the value loaded to the ACCUMULATOR is zero then it is the end
     * of the String */
     
    if( addInstructionToMemory( branchZeroInst + exitInstruction ) == FAIL ) 
        return FAIL;
    
    /* ********************************************************************** */
    
    INSTRUCTIONCOUNTER++;  /* Make space for subtract b$ chars*/
     
    /* branch zero to start of for-loop */
    if( addInstructionToMemory( branchZeroInst + exitInstruction-20 ) == FAIL ) 
        return FAIL;
    
    // Else strings are not equal  //
    if( addInstructionToMemory( branchNegInst + exitInstruction+4 ) == FAIL ) 
        return FAIL;

    /* branchpos ie not equal to */
    if( addInstructionToMemory( branchPosInst + exitInstruction+4 ) == FAIL ) 
        return FAIL;
    
    /* #######################################################
     * create a load instruction for position in b$ 
     * #######################################################
     */
     
    /* load LOAD instruction */
    if( addInstructionToMemory( loadInstruction + loadA ) == FAIL ) 
        return FAIL;
    
    /* add current position in b$ */
    if( addInstructionToMemory( addInstruction + positionInB ) == FAIL ) 
        return FAIL;
    
    /* store 1 instructions from the current one */
    if( addInstructionToMemory( storeInstruction + INSTRUCTIONCOUNTER+1 ) == FAIL ) 
        return FAIL;
    
    INSTRUCTIONCOUNTER++;  /* Make space for load b$ chars*/
    /* if the strings are equal this will be 0 */
      
    /* store value in ACCUMULATOR to tempA */
    if( addInstructionToMemory( storeInstruction + tempA ) == FAIL ) 
        return FAIL;

    /* //// Reinitialise the string index position counters //// */
        
    /* load stored start position of a$ */
    if( addInstructionToMemory( loadInstruction + startOfA ) == FAIL ) 
        return FAIL;

    /* store to positionInA */
    if( addInstructionToMemory( storeInstruction + positionInA ) == FAIL ) 
        return FAIL;

    /* load stored start position of b$ */
    if( addInstructionToMemory( loadInstruction + startOfB ) == FAIL ) 
        return FAIL;

    /* store to  positionInB */
    if( addInstructionToMemory( storeInstruction + positionInB ) == FAIL ) 
        return FAIL;

    /* load stored position in b$ */
    if( addInstructionToMemory( loadInstruction + tempA ) == FAIL ) 
        return FAIL;

    return SUCCESS;
}   

