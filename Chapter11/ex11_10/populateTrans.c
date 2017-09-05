/*
 * Filename:	populateTrans.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/07/2017.
 * Description: Appends transactions to the end of the file
 */
 
#include <stdio.h>

struct clientTransaction { 
   int acctNum;
   double transaction;
};


int enterChoice( void );
void textFile( FILE * );
void addTransaction( FILE * );


int main()
{ 
   FILE *cfPtr;
   int choice;
 
   if ( ( cfPtr = fopen( "trans.dat", "ab" ) ) == NULL )
      printf( "File could not be opened.\n" );
   else 
   { 
        while( (choice = enterChoice() ) != 2)
        {
        	switch(choice) {
        		case 1:
                    addTransaction( cfPtr );
					break;
				default:
				    printf("INVALID OPTION - Please try again!\n");
					break;    
			}
		}
		
		fclose( cfPtr );
    }
   
    cfPtr = fopen( "trans.dat", "rb" );
	textFile( cfPtr );
	fclose( cfPtr );

   return 0;
}


int enterChoice( void )
{
	int menuChoice;
	
	printf("Enter your choice\n"
	       "1 - add a new transaction\n"
	       "2 - end program\n? " );
	scanf("%d", &menuChoice);
	fflush( stdin );
	
	return menuChoice;
}

void textFile( FILE *readPtr )
{
   struct clientTransaction client = { 0, 0.0 };
   FILE *writePtr;
 
   if ( ( writePtr = fopen( "transactions.txt", "w" ) ) == NULL )
        printf( "File could not be opened.\n" );
   else { 
        rewind( readPtr );
        fprintf( writePtr, "%-6s%-16s\n",
	          "Acct", "Transaction" );
	          
	    while ( !feof( readPtr  ) ) { 
            fread( &client, sizeof( struct clientTransaction ), 1, 
                readPtr );

	        if ( client.acctNum != 0 ) {
	         	fprintf( writePtr, "%-6d%-16.2f\n", 
	                    client.acctNum, client.transaction );
			}
            
         }
	          
	  fclose( writePtr );
      printf("File \"transactions.txt\" created\n");
   }
   
}


void addTransaction( FILE *fPtr )
{
    struct clientTransaction client = { 0, 0.0 };
	int accountNum;
    
    printf("Enter account number ( 1-1000 ): ");
    scanf( "%d", &accountNum );
    
    fflush(stdin);
    
    printf( "Enter transaction amount\n? " );
    scanf( "%lf", &client.transaction );
    client.acctNum = accountNum;     
    fseek( fPtr, ( client.acctNum - 1 ) * 
            sizeof( struct clientTransaction ), SEEK_SET );
    fwrite( &client, sizeof( struct clientTransaction ), 1, 
             fPtr );

}

