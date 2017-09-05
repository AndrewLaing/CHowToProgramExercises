/*
 * Filename:    ex11_11.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/07/2017.
 */
 
#include <stdio.h>

struct person { 
   char lastName[ 15 ];
   char firstName[ 15 ];
   char age[4];
};


void createNameage( FILE * );
void addTenRecords( FILE * );
void updateRecord( FILE * );
void deleteRecord( FILE * );
int strcmp2( const char*, const char * );


const int DEBUG = 0;             /* Idea: Use different debugging levels */
void textFile( FILE *, char * ); /* for debugging and proving that file contents
                                  * have been created, updated, and deleted */

int main()
{ 
    FILE *nfPtr;
    if ( ( nfPtr = fopen( "nameage.dat", "wb+" ) ) == NULL ) {
        printf( "File \"nameage.dat\" could not be opened.\n" );
        return -1;
    }       
    
    createNameage( nfPtr );
    if(DEBUG) printf("File \"nameage.dat\" created.\n");
    
    fclose ( nfPtr );
    
    /* Verify the file was created */
    nfPtr = fopen( "nameage.dat", "rb+" ) ;
    if(DEBUG) textFile( nfPtr, "nameageVerify.txt" );
    
    addTenRecords( nfPtr );

    if(DEBUG) textFile( nfPtr, "nameageAddTen.txt" );
    
    updateRecord( nfPtr );
    if(DEBUG) textFile( nfPtr, "nameageUpdate1.txt" );
    
    updateRecord( nfPtr );
    if(DEBUG) textFile( nfPtr, "nameageUpdate2.txt" );
    
    deleteRecord( nfPtr );
    if(DEBUG) textFile( nfPtr, "nameageDeleted.txt" );
    
    fclose ( nfPtr );
    
    return 0;
}


void createNameage(FILE *nfPtr)
{
    int i;
    struct person blankPerson = { "unassigned", "", "0"};

    for ( i = 1; i <= 100; i++ )
         fwrite( &blankPerson, sizeof( struct person ), 1, nfPtr );
}



void addTenRecords( FILE *fPtr )
{
    struct person blankPerson = { "", "", "" };
    int i;
    
    rewind( fPtr );
    
    for(i=0; i<2; i++)
    {   
        printf( "Enter lastname, firstname, age\n? " );
        scanf( "%s%s%s", &blankPerson.lastName, &blankPerson.firstName,
                         &blankPerson.age  );   
        
        fwrite( &blankPerson, sizeof( struct person ), 1, 
                 fPtr );        
    }
}


void updateRecord( FILE *fPtr )
{
    struct person blankPerson = { "", "", "" };
    int accountNum;
    
    printf("Enter number of account to update ( 1-100 ): ");
    scanf( "%d", &accountNum );
    
    fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct person ), 
           SEEK_SET );
    fread( &blankPerson, sizeof( struct person ), 1,
           fPtr );
    
    if( strcmp2(blankPerson.lastName, "unassigned") == 0)
        printf( "No info\n");
    else {
        printf( "Enter lastname, firstname, age\n? " );
        scanf( "%s%s%s", &blankPerson.lastName, &blankPerson.firstName,
                         &blankPerson.age  );   
        fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct person ), 
           SEEK_SET );
        fwrite( &blankPerson, sizeof( struct person ), 1, 
                 fPtr );   
        printf( "Record updated\n");
    }
}


void deleteRecord( FILE *fPtr )
{
    struct person temp = { "", "", ""};
    struct person blankPerson = { "unassigned", "", "0"};
    
    int accountNum;
    
    printf("Enter number of account to delete ( 1-100 ): ");
    scanf( "%d", &accountNum );
    
    fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct person ), 
           SEEK_SET );
    fread( &temp, sizeof( struct person ), 1,
           fPtr );
    
    if( strcmp2(temp.lastName, "unassigned") == 0)
        printf( "Record does not contain any info\n");
    else {
        fseek( fPtr, 
           ( accountNum - 1 ) *  sizeof( struct person ), 
           SEEK_SET );
        fwrite( &blankPerson, sizeof( struct person ), 1, 
                 fPtr );   
        printf( "Record deleted\n");
    }
}



void textFile( FILE *readPtr, char *filename )
{
   struct person blankPerson = { "unassigned", "", "0"};
   FILE *writePtr;
 
   if ( ( writePtr = fopen( filename, "w" ) ) == NULL )
        printf( "File could not be opened.\n" );
   else { 
        rewind( readPtr );
        fprintf( writePtr, "%-16s%-11s%10s\n",
              "Last Name", "First Name", "Age" );
              
        while ( !feof( readPtr  ) ) { 
            fread( &blankPerson, sizeof( struct person ), 1, 
                readPtr );

            fprintf( writePtr, "%-16s%-11s%10s\n", 
                    blankPerson.lastName, blankPerson.firstName,
                    blankPerson.age  );            
         }
              
      fclose( writePtr );
      printf("File \"%s\" created\n",filename );
   }  
}


/* Using pointer arithmetic */
int strcmp2( const char* s1, const char *s2 )
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

