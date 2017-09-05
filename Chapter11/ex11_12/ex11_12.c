/*
 * Filename:    ex11_12.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/07/2017.
 * TODO:        Add properly validated input methods for EACH field
 *              so that the program does not need to use scanf()
 */
 
#include <stdio.h>

struct tool { 
    int recordNum;
    char toolName[ 30 ];
    int quantity;
    double cost;
};


void initialiseRecords( FILE * );
int enterChoice( void );
void addRecord( FILE * );
void updateRecord( FILE * );
void deleteRecord( FILE *fPtr );
void textFile( FILE *, char * );
void displayRecords( FILE * );
int strcmp2( const char *, const char * );


int main()
{   
   FILE *cfPtr;
   int choice;
 
    if ( ( cfPtr = fopen( "hardware.dat", "rb+" ) ) == NULL )
    {
        /* If file doesn't exist create it */
        cfPtr = fopen( "hardware.dat", "wb+" );
        fclose( cfPtr );
        cfPtr = fopen( "hardware.dat", "rb+" );
        /* Initialise record file*/
        initialiseRecords( cfPtr );
    }

    while( (choice = enterChoice() ) != 6)
    {
        switch(choice) {
            case 1:
                textFile( cfPtr, "Hardware.txt" );
                break;
            case 2:
                addRecord( cfPtr );
                break;
            case 3:
                updateRecord( cfPtr );
                break;
            case 4:
                deleteRecord( cfPtr );
                break;
            case 5:
                displayRecords( cfPtr );
                break;
            default:
                printf("\nINVALID OPTION - Please try again!\n\n");
                break;    
        }
    }
    
    fclose( cfPtr );

   return 0;
}


void initialiseRecords(FILE *nfPtr)
{
    struct tool blankTool = { 0, "unassigned", 0, 0.0 };
    int i;
    
    rewind( nfPtr );
    
    for(i=0; i<100; i++)
    {   
        blankTool.recordNum = i+1;   
        
        fwrite( &blankTool, sizeof( struct tool ), 1, 
                 nfPtr );     
    }
}


int enterChoice( void )
{
    int menuChoice;
    
    printf("Enter your choice:\n"
           "1 - Create a text file of all tools records\n"
           "    named \"tools.txt\"\n"
           "2 - add a new record\n"
           "3 - update an existing record\n"
           "4 - delete a record\n"
           "5 - display all tool records\n"
           "6 - end program\n? " );

    scanf("%d", &menuChoice);
    fflush( stdin );
    
    return menuChoice;
}


void addRecord( FILE *fPtr )
{
    struct tool blankTool = { 0, "", 0, 0.0 };
    int accountNum;
    
    printf("Enter record number ( 1-100 ): ");
    scanf( "%d", &accountNum );
    
    fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct tool ), 
           SEEK_SET );
    fread( &blankTool, sizeof( struct tool ), 1,
           fPtr );
    
    if( strcmp2(blankTool.toolName, "unassigned") != 0)
        printf( "\nA record with that number already exists!\n\n");
    else {
        printf( "Enter tool-name, quantity, cost\n? " );
        scanf( "%s%d%lf", &blankTool.toolName, &blankTool.quantity,
                         &blankTool.cost );   
        fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct tool ), 
           SEEK_SET );
        fwrite( &blankTool, sizeof( struct tool ), 1, 
                 fPtr );   
        printf( "\nRecord added\n\n");
    }
}


void updateRecord( FILE *fPtr )
{
    struct tool blankTool = { 0, "", 0, 0.0 };
    int accountNum;
    
    printf("Record number to update ( 1-100 ): ");
    scanf( "%d", &accountNum );
    
    fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct tool ), 
           SEEK_SET );
    fread( &blankTool, sizeof( struct tool ), 1,
           fPtr );
    
    if( strcmp2(blankTool.toolName, "unassigned") == 0)
        printf( "\nNo info in record to update!\n\n");
    else {
        printf( "Enter tool-name, quantity, cost\n? " );
        scanf( "%s%d%lf", &blankTool.toolName, &blankTool.quantity,
                         &blankTool.cost );   
        fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct tool ), 
           SEEK_SET );
        fwrite( &blankTool, sizeof( struct tool ), 1, 
                 fPtr );   
        printf( "\nRecord updated\n");
    }
}


void deleteRecord( FILE *fPtr )
{
    struct tool temp = { 0, "unassigned", 0, 0.0 };
    struct tool blankTool = { 0, "unassigned", 0, 0.0 };
    
    int recordNum;
    
    printf("Enter number of the record to delete ( 1-100 ): ");
    scanf( "%d", &recordNum );
    
    fseek( fPtr, 
           ( recordNum - 1 ) *  sizeof( struct tool ), 
           SEEK_SET );
    fread( &temp, sizeof( struct tool ), 1,
           fPtr );
    
    if( strcmp2(temp.toolName, "unassigned") == 0)
        printf( "\nRecord does not contain any info!\n\n");
    else {
        fseek( fPtr, 
           ( recordNum - 1 ) *  sizeof( struct tool ), 
           SEEK_SET );
        blankTool.recordNum = recordNum;
        fwrite( &blankTool, sizeof( struct tool ), 1, 
                 fPtr );   
        printf( "\nRecord deleted\n");
    }
}


void textFile( FILE *readPtr, char *filename )
{
    struct tool blankTool = { 0, "", 0, 0.0 };
    FILE *writePtr;
 
    if ( ( writePtr = fopen( filename, "w" ) ) == NULL )
        printf( "File could not be opened.\n" );
    else { 
        rewind( readPtr );
        fprintf( writePtr, "%-12s%-32s%-11s%10s\n",
              "Record Num", "Tool Name", "Quantity", "Cost" );
              
        fread( &blankTool, sizeof( struct tool ), 1, readPtr );    
              
        while ( !feof( readPtr  ) ) { 
            fprintf( writePtr, "%-12d%-32s%-11d%10.2f\n", 
                    blankTool.recordNum, blankTool.toolName,
                    blankTool.quantity, blankTool.cost   );    
                    
            fread( &blankTool, sizeof( struct tool ), 1, 
                readPtr );           
        }
              
        fclose( writePtr );
        printf("\nFile \"%s\" created\n\n",filename );
    }  
}


void displayRecords( FILE *readPtr )
{
    //struct person blankPerson = { "unassigned", "", "0"};
    struct tool blankTool = { 0, "", 0, 0.0 };
    int numberOfRecords = 0;
 
    rewind( readPtr );

    printf( "\n%-12s%-32s%-11s%10s\n",
          "Record Num", "Tool Name", "Quantity", "Cost" );
          
    fread( &blankTool, sizeof( struct tool ), 1, readPtr );  
          
    while ( !feof( readPtr  ) ) {
        if( strcmp2(blankTool.toolName, "unassigned") != 0)
        {
            printf( "%-12d%-32s%-11d%10.2f\n", 
                    blankTool.recordNum, blankTool.toolName,
                    blankTool.quantity, blankTool.cost   );  
            
            numberOfRecords++;  
        }
        fread( &blankTool, sizeof( struct tool ), 1, 
                        readPtr );  
    }
    
    if(numberOfRecords==0)
        printf("\nNo records to display!\n");
    printf("\n");
}


int strcmp2( const char *s1, const char *s2 )
{      
    while(*s2!='\0') {
        if(*s1<*s2)
            return -1;
        else if(*s1>*s2)
            return 1;
        s1++;
        s2++;           
    }

    return 0;   
}

