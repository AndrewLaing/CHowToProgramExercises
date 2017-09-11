/*
 * Filename:    main.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/09/2017.
 *
 * TODO: for the JMP functions implement the optimise
 
    // Optimise if this was a production
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = storeInstruction;
    }
 
 */

#include "SimpleCompiler.h"


int main()
{
    /* Set each element in flags to -1 */
    initialiseFlags();
    
    char filename[ MAXLINELENGTH ];
    printf("Enter name of file to load: ");
    getLine( filename, MAXLINELENGTH );
    
    /* Compile to SML */
    if( runFirstPass( filename ) != 0)
        return -1; 
        
    if( runSecondPass() != 0)
        return -1; 

    /* Write out the instructions to file */
    if( writeInstructionsToFile( "out.sml" ) != 0 )
        return -1; 
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
 * The method writeInstructionsToFile writes out the instructions created
 * from the Simple input file to the sml output file.
 * @param outfile The name of the sml output file to create.
 * @return 0 If the write operation was successful, otherwise -1. 
 */
int writeInstructionsToFile( const char *outFile )
{
    int i;
    FILE *ofPtr;
    
    if( (ofPtr = fopen(outFile, "w")) == NULL ) {
        printf("File could not be opened\n");
        return -1;
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
    
    return 0;
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
    Table[TABLEPOSITION].location = INSTRUCTIONCOUNTER++;
    TABLEPOSITION++;  
    PREVIOUSLINENUMBER = number;
}


/**
 * The function addVariableToTable adds the details for a 
 * variable to the symbols table during the compiler's first pass.
 * @param c A variable.
 */
void addVariableToTable( char c )
{   
    if( variableExistsInTable( c ) == -1)  {
        Table[TABLEPOSITION].symbol = c;
        Table[TABLEPOSITION].type = 'V'; 
        Table[TABLEPOSITION].location = VARCONSTADDRESS--;
        TABLEPOSITION++;
    }
}


/**
 * The function addConstantToTable adds the details for a 
 * constant to the symbols table, and adds its value to a
 * memory location during the compiler's first pass.
 * @param number A constant value.
 */
void addConstantToTable( int number )
{
    if( constantExistsInTable( number ) == -1 ) {
        Table[TABLEPOSITION].symbol = number;
        Table[TABLEPOSITION].type = 'C';
        MEMORY[ VARCONSTADDRESS ] = number;
        Table[TABLEPOSITION].location = VARCONSTADDRESS--;  
        TABLEPOSITION++;                    
    }
}


/**
 * The function runFirstPass runs the compiler's first pass of the Simple
 * source file. It reads in the lines one at a time, adding their symbols
 * to the lookup table and creating sml instructions.
 * @param inFile The name of the Simple source file to compile.
 * @return 0 if the first pass ran correctly, otherwise an error code
 *         relating to the error that occured.
 */
int runFirstPass( const char *inFile )
{
    char line[ MAXLINELENGTH ];
    char lineCopy[ MAXLINELENGTH ];
    char tokenArray[ MAXLINELENGTH ][MAXTOKENLENGTH];
    int lineParsed;
    
    if( inFile == NULL ) {
        printf( "Error - a valid Simple sourcecode file name has not been provided.\n" );
        return 1;
    }
    
    if( !endsWithSuffix( inFile, ".simple" ) ) {    
        printf( "Error - \"%s\" does not seem to be a valid Simple sourcecode file.\n", inFile );
        return 2;
    }
    
    FILE *sourceFilePtr = fopen( inFile, "r" );

    if( sourceFilePtr == NULL ) 
    {
        printf("Error - unable to open file \"%s\"\n", inFile);
        return 3;
    }
    else 
    {
        while ( fgets ( line, sizeof line, sourceFilePtr ) != NULL )
        {   
            if(endsWith(line, '\n') )
                removeEndChar( line );
                
            strcpy2( lineCopy, line ); 
            
            int numberOfTokens;
            numberOfTokens = createTokenArray( lineCopy, tokenArray );

            lineParsed = addSymbolsToTable( tokenArray, numberOfTokens );
            
            if(lineParsed==0) {
                fclose( sourceFilePtr );
                return 4;
            }
                
            strcpy2( lineCopy, line ); 
            /* pass to create SML here */
            createFirstSML( tokenArray, numberOfTokens ); 
        }       
    }

    fclose( sourceFilePtr );
    printf("\nFile \"%s\" loaded. Compiling...\n", inFile );
    return 0;
}


/**
 * The function runSecondPass runs the compiler's second pass of the
 * Simple source file, resolving addresses for the line numbers flagged
 * during the first pass and updating their related sml instructions.
 * @return 0 if the second pass ran correctly, otrherwise -1.
 */
int runSecondPass()
{
    int i, address;
    for( i=0; i<MEMORYSIZE; i++ ) 
    {
        if( Flags[i] != -1 ) {
            address = lineNumberExistsInTable(Flags[i]);
            if(address==-1) return -1;
            MEMORY[ i ] += address;
            Flags[i] = -1;
        }
    }
    
    return 0;
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
    
    tokenPtr = strtok( lineCopy, " \n" );
    
    while( tokenPtr != NULL ) 
    {   
        while(startsWith(tokenPtr, '(') ) {
            strcpy2( tokenArray[length++], "(" ); 
            tokenPtr++;
        }
        if(endsWith(tokenPtr, ')') ) {
            removeEndChar(tokenPtr);            
            strcpy2( tokenArray[length++], tokenPtr ); 
            strcpy2( tokenArray[length++], ")" ); 
        }
        else if(tokenPtr[0] != '\0') {
            strcpy2( tokenArray[length++], tokenPtr ); 
        }

        tokenPtr = strtok( NULL, " \n" );
    }
         
    return length;
}


/**
 * The function addSymbolsToTable is used during the compiler's 
 * first pass to add the symbols found on a tokenised line of Simple
 * to the lookup table.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int addSymbolsToTable( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens )
{   
    if( numberOfTokens == 0 ) {
        printf("Syntax Error!\n");
        return 0;
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
                        printf("Syntax Error!\n");
                        return 0;
                    }
                }
                else
                    addConstantToTable( number );       
            }
            else {
                /* If the rem command is encountered skip the rest of the line */               
                if( strcmp2( tokenArray[i], "rem") == 0 ) {
                    INSTRUCTIONCOUNTER--;
                    return 1;
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
                        printf("Syntax Error!\n");
                        return 0;
                    }
                }
                else
                    addConstantToTable( number );
            }
            else if(isalpha( tokenArray[i][0] ) )
                addVariableToTable( tokenArray[i][0] );
        }
    }
    
    return 1;
}


/**
 * The function createInputInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple input statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createInputInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* The line number has been assigned the address of the instruction pointer
     * and augmented it, so it needs to be decremented to place the first
     * instruction here in the correct memory address */
    INSTRUCTIONCOUNTER--;
    
    int instruction = READ*10000;
    int variableAddress = variableExistsInTable( tokenArray[2][0] );
    instruction += variableAddress;
     
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction;
    
    return 1;
}


/**
 * The function createPrintInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple print statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createPrintInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* The line number has been assigned the address of the instruction pointer
     * and augmented it, so it needs to be decremented to place the first
     * instruction here in the correct memory address */
    INSTRUCTIONCOUNTER--;
    
    int instruction = WRITE*10000;
    int variableAddress;    
    
    if( !isdigit( tokenArray[2][0]) )
        variableAddress = variableExistsInTable( tokenArray[2][0] );
    else
        variableAddress = constantExistsInTable( strToInt(tokenArray[2]) );
    
    instruction += variableAddress;
     
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction;
    
    return 1;
}


/**
 * The function createGotoInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple goto statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createGotoInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    INSTRUCTIONCOUNTER--;
    
    int instruction = BRANCH*10000;

    int returnLineNumber = strToInt(tokenArray[2]);    
    int returnAddress = lineNumberExistsInTable( returnLineNumber );
    
    if(returnAddress != -1 )
        instruction += returnAddress;
    else {
        Flags[ INSTRUCTIONCOUNTER ] = returnLineNumber;
    }
    
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction;
    
    return 1;
}


/**
 * The function createEndInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple end statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createEndInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    INSTRUCTIONCOUNTER--;
    int instruction = HALT*10000;
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction;
    
    return 1;
}


/**
 * The function createLetInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple let statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createLetInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* The line number has been assigned the address of the instruction pointer
     * and augmented it, so it needs to be decremented to place the first
     * instruction here in the correct memory address */
    INSTRUCTIONCOUNTER--;
    
    /* Evaluate the expression on the RHS of the = sign */
    char postfix[ MAXLINELENGTH ];
    convertToPostfix( tokenArray, postfix, 4, numberOfTokens ); 

    int variableAddress = variableExistsInTable( tokenArray[2][0] ); 
    
    int loadInstruction  = LOAD * 10000;
    int storeInstruction = STORE * 10000;
    
    int evalResult = evaluatePostfixExpression( postfix );
    
    loadInstruction += evalResult;    
    storeInstruction += variableAddress; 
       
    /* Optimise if this was a production*/
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = storeInstruction;
    }
    else {
        /* Load result of evaluation to the accumulator */
        MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;

        /* Store the accumulator value into the variable */    
        MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction;        
    }

    
    return 1;
}



/**
 * The function createIfInstruction is used during the compiler's 
 * first pass to create the SML equivalent of a Simple if statement
 * read in from the source file.
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createIfInstruction( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    /* The line number has been assigned the address of the instruction pointer
     * and augmented it, so it needs to be decremented to place the first
     * instruction here in the correct memory address */
    INSTRUCTIONCOUNTER--;
    
    /* Get the index of the comparison operator in the if statement */
    int compOpIdx = getComparisonOperatorIndex( tokenArray, numberOfTokens);
    
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
 
    return 1;
}


/**
 * The function createFirstSML is used during the compiler's first pass
 * of the Simple source file to create SML instructions
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the line parsed correctly, otherwise 0.
 */
int createFirstSML( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens ) 
{
    if( numberOfTokens == 0 ) {
        printf("Syntax Error!\n");
        return 0;
    }
    
    if(strcmp2( tokenArray[1], "rem" ) == 0 )
        return 1;
    else if(strcmp2( tokenArray[1], "input" ) == 0 )
        return createInputInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "print" ) == 0 )
        return createPrintInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "goto" ) == 0 )
        return createGotoInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "end" ) == 0 )
        return createEndInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "if" ) == 0 )
        return createIfInstruction( tokenArray, numberOfTokens );
    else if(strcmp2( tokenArray[1], "let" ) == 0 )
        return createLetInstruction( tokenArray, numberOfTokens );
    else {
        printf("Syntax Error!\n");
        return 0;
    }
    
    return 1;
}


/**
 * The method dumpTableEntries is used to print out the current
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
  * The function variableExistsInTable checks whether the constant value
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
  * The function variableExistsInTable checks whether the line number value
  * exists in the lookup table or not.
  * @param symbol A line numberto look for in the Symbol Table.
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


/* The method convertToPostfix takes an infix expression stored as
 * a string and converts it to a postfix expression stored in a string
 * using a stack implementation.
 * @param infix A tokenised Simple statement containing an infix expression.
 * @param postfix A character array to store the converted expression to.
 * @param start The index of the first token of the infix expression.
 * @param end The index of the lasst token of the infix expression.
 */
void convertToPostfix( char infix[][MAXTOKENLENGTH], char postfix[], int start, int end )
{
    int i=start, j=0;   
    char c;

    /* Push left parenthesis to stack */
    StackNodePtr stackPtr = NULL;
    push( &stackPtr, '(' ); 

    infix[end][0] = ')';
    
    /* Do the conversion */
    while( !isEmpty( stackPtr ) && i <= end )
    {
        int k=0;
        c = infix[i][k++];
        
        if( c=='-' && strlen2(infix[i])>1  && isdigit(infix[i][1]) )
        {
            postfix[j++] = c;
            c = infix[i][k++];
        }
        
        if( isdigit(c) ) 
        {       
            while( isdigit(c) ) {
                postfix[j++] = c;
                c = infix[i][k++];
            }
            postfix[j++] = ' ';
        }
        else if( c == '(')
            push( &stackPtr, '(' );
        else if( isOperator(c) == 1 ) 
        {
            if( !isEmpty( stackPtr ) && isOperator( stackTop(stackPtr) ) ) {
                while( isOperator( stackTop(stackPtr) ) && 
                       (precedence( stackTop(stackPtr), c )) >= 0 ) 
                {
                    postfix[j++] = pop( &stackPtr );
                    postfix[j++] = ' ';
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
                    postfix[j++] = c;
                    postfix[j++] = ' ';
                    c = pop( &stackPtr ); 
                }
            }
        }
        else if( c != ' ')
        {
            postfix[j++] = c;
            postfix[j++] = ' ';
        }
        
        i++;
    }
    postfix[j] = '\0';
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
 * @param expr A string containing a postfix expression. 
 * @result The memory address where the instructions will store the 
 *         result of the evaluation, otherwise 0 if the expression could 
 *         not be evaluated. 
 */
int evaluatePostfixExpression( char *expr )
{
    StackNodePtr stackPtr = NULL;
    
    char postfix[MAXLINELENGTH][MAXTOKENLENGTH];
    int pfLength = createTokenArray( expr, postfix );
    
    int x, y;
    
    int i=0;
    int address;
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
            push( &stackPtr, address );     /* TODO - insert atoi method */
        }
        else if( isalpha( c ) ) 
        {
            address = variableExistsInTable( c );
            push( &stackPtr, address ); 
        }
        else if( isOperator( c ) )
        {
            if(isEmpty( stackPtr ) ) {
                printf("Invalid postfix expression!\n");
                return 0;
            }
            x = pop( &stackPtr );
            
            if(isEmpty( stackPtr ) ) {
                printf("Invalid postfix expression!\n");
                return 0;
            }
            y = pop( &stackPtr );
            
            push( &stackPtr, calculate( y, x, c ) );
        }
        i++;
    }
    
    if(isEmpty( stackPtr ) ) {
        printf("Invalid postfix expression!\n");
        return 0;
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
 *         result of the math operation.
 */
int calculate( int op1, int op2, char theOperator )
{   
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
            MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;  // load op1 to accumulator
        
            addInstruction += op2;
            MEMORY[ INSTRUCTIONCOUNTER++ ] = addInstruction;   // add op2
            
            MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction; // store result to tempStorage
            break;
        case '-':
            MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;  // load op1 to accumulator
            
            subInstruction += op2;
            MEMORY[ INSTRUCTIONCOUNTER++ ] = subInstruction;   // subtract op2
            
            MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction; // store result to tempStorage
            break;
        case '*':
            MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;  // load op1 to accumulator
            
            mulInstruction += op2;
            MEMORY[ INSTRUCTIONCOUNTER++ ] = mulInstruction;   // multiply by op2
            
            MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction; // store result to tempStorage
            break;
        case '/':
            MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;  // load op1 to accumulator
            
            divInstruction += op2;
            MEMORY[ INSTRUCTIONCOUNTER++ ] = divInstruction;   // divide by op2
            
            MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction; // store result to tempStorage
            break;
        case '^':
            MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;  // load op1 to accumulator
            
            expInstruction += op2;
            MEMORY[ INSTRUCTIONCOUNTER++ ] = expInstruction;   // raise to the power of op2
            
            MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction; // store result to tempStorage
            break;
        case '%':
            MEMORY[ INSTRUCTIONCOUNTER++ ] = loadInstruction;  // load op1 to accumulator
            
            modInstruction += op2;
            MEMORY[ INSTRUCTIONCOUNTER++ ] = modInstruction;   // modulo by op2
            
            MEMORY[ INSTRUCTIONCOUNTER++ ] = storeInstruction; // store result to tempStorage
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
    
    return -1;
}


/**
 * The function isComparisonOperator returns the index of the comparison
 * operator, contained within the test string, from the compOperators array.
 * @param test A comparison operator.
 * @return The index of the comparison operator in the compOperators array,
 *         else -1 if the test string could not be found in the array.
 */
int isComparisonOperator( char *test ) 
{
    int idx;
    for( idx=0; idx<NUMBEROFCOMPOPERATORS; idx++ ) 
    {
        if(strcmp2(test, compOperators[idx]) == 0 )
            return idx;
    }   
    return -1;
}


/**
 * The function doLTJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x < y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the instructions were successfully created.
 */
int doLTJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int ltIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ];   
    char RHSPostfix[ MAXLINELENGTH ];

    convertToPostfix( tokenArray, LHSPostfix, 2,         ltIndex ); 
    convertToPostfix( tokenArray, RHSPostfix, ltIndex+1, numberOfTokens-2 ); 
    
    RHSAddress = evaluatePostfixExpression( RHSPostfix );
    LHSAddress = evaluatePostfixExpression( LHSPostfix );

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;

    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;

    /* Subtract RHS expression result from the accumulator */
    /* If last instruction, for evaluate LHS, was a STORE it does not
     * need to be stored then reloaded into the Accumulator */
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction1;
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction2;
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
    
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction3;

    return 1;
}           


/**
 * The function doGTJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x > y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the instructions were successfully created.
 */
int doGTJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int gtIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ];   
    char RHSPostfix[ MAXLINELENGTH ];

    convertToPostfix( tokenArray, LHSPostfix, 2,         gtIndex ); 
    convertToPostfix( tokenArray, RHSPostfix, gtIndex+1, numberOfTokens-2 ); 
    
    RHSAddress = evaluatePostfixExpression( RHSPostfix );
    LHSAddress = evaluatePostfixExpression( LHSPostfix );

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;
 
    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;    
    
    /* If last instruction, for evaluate LHS, was a STORE it does not
     * need to be stored then reloaded into the Accumulator */
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction1;
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction2;
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
        
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction3;

    return 1;
}   


/**
 * The function doLTEJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x <= y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the instructions were successfully created.
 */         
int doLTEJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int lteIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ];   
    char RHSPostfix[ MAXLINELENGTH ];

    convertToPostfix( tokenArray, LHSPostfix, 2,          lteIndex ); 
    convertToPostfix( tokenArray, RHSPostfix, lteIndex+1, numberOfTokens-2 ); 

    RHSAddress = evaluatePostfixExpression( RHSPostfix );    
    LHSAddress = evaluatePostfixExpression( LHSPostfix );

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;
        
    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;         
        
    /* If last instruction, for evaluate LHS, was a STORE it does not
     * need to be stored then reloaded into the Accumulator */
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction1;
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction2;
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
        
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction3;  
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction4;

    return 1;
}           


/**
 * The function doGTEJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x >= y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the instructions were successfully created.
 */
int doGTEJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int gteIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ];   
    char RHSPostfix[ MAXLINELENGTH ];

    convertToPostfix( tokenArray, LHSPostfix, 2,          gteIndex ); 
    convertToPostfix( tokenArray, RHSPostfix, gteIndex+1, numberOfTokens-2 ); 

    RHSAddress = evaluatePostfixExpression( RHSPostfix );    
    LHSAddress = evaluatePostfixExpression( LHSPostfix );

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;
    
    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;   
     
    /* If last instruction, for evaluate LHS, was a STORE it does not
     * need to be stored then reloaded into the Accumulator */
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction1;
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction2;
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
    
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction3;  
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction4;

    return 1;
}   

    
/**
 * The function doEQJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x == y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the instructions were successfully created.
 */
int doEQJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int eqIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ];   
    char RHSPostfix[ MAXLINELENGTH ];

    convertToPostfix( tokenArray, LHSPostfix, 2,         eqIndex ); 
    convertToPostfix( tokenArray, RHSPostfix, eqIndex+1, numberOfTokens-2 ); 
    
    RHSAddress = evaluatePostfixExpression( RHSPostfix ); 
    LHSAddress = evaluatePostfixExpression( LHSPostfix );

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;

    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;      
      
    /* If last instruction, for evaluate LHS, was a STORE it does not
     * need to be stored then reloaded into the Accumulator */
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction1;
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction2;
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
    
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction3;

    return 1;
}           


/**
 * The function doNEJMP creates the necessary instructions to perform
 * the SML equivalent of a Simple 'if x != y goto n'. It is used during
 * the compiler's first pass. 
 * @param tokenArray A tokenised line from the Simple source file.
 * @param numberOfTokens The number of tokens contained in tokenArray.
 * @return 1 if the instructions were successfully created.
 */
int doNEJMP( char tokenArray[][MAXTOKENLENGTH], int numberOfTokens, int neIndex )
{
    int LHSAddress, RHSAddress;
    int returnAddress;

    char LHSPostfix[ MAXLINELENGTH ];   
    char RHSPostfix[ MAXLINELENGTH ];

    convertToPostfix( tokenArray, LHSPostfix, 2,         neIndex ); 
    convertToPostfix( tokenArray, RHSPostfix, neIndex+1, numberOfTokens-2 ); 

    RHSAddress = evaluatePostfixExpression( RHSPostfix );    
    LHSAddress = evaluatePostfixExpression( LHSPostfix );

    int instruction1 = LOAD * 10000;
    instruction1 += LHSAddress;

    int instruction2 = SUBTRACT * 10000;
    instruction2 += RHSAddress;

    /* If last instruction, for evaluate LHS, was a STORE it does not
     * need to be stored then reloaded into the Accumulator */
    if(MEMORY[INSTRUCTIONCOUNTER-1]/10000 == STORE)
    {
        MEMORY[ INSTRUCTIONCOUNTER-1 ] = instruction2;
    }
    else {
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction1;
        MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction2;
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
    
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction3;  
    MEMORY[ INSTRUCTIONCOUNTER++ ] = instruction4;

    return 1;
}

