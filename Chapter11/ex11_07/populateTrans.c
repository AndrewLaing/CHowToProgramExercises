/*
 * Filename:	populateTrans.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/07/2017.
 */
 
#include <stdio.h>

struct clientTransaction { 
   int acctNum;
   double transaction;
};


int enterChoice( void );
void textFile( FILE * );
void newRecord( FILE * );


int main()
{ 
   FILE *cfPtr;
   int choice;
 
   if ( ( cfPtr = fopen( "trans.dat", "rb+" ) ) == NULL )
      printf( "File could not be opened.\n" );
   else 
   { 
        while( (choice = enterChoice() ) != 3)
        {
        	switch(choice) {
        		case 1:
        			textFile( cfPtr );
					break;
				case 2:
				    newRecord( cfPtr );
					break;
				default:
				    printf("INVALID OPTION - Please try again!\n");
					break;    
			}
		}
		
		fclose( cfPtr );
   }

   return 0;
}


int enterChoice( void )
{
	int menuChoice;
	
	printf("Enter your choice\n"
	       "1 - store a formatted text file of accounts called\n"
	       "    \"transactions.txt\" for printing\n"
	       "2 - add a new transaction\n"
	       "3 - end program\n? " );
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


void newRecord( FILE *fPtr )
{
    struct clientTransaction client = { 0, 0.0 };
	int accountNum;
    
    printf("Enter account number ( 1-1000 ): ");
    scanf( "%d", &accountNum );
    
    fseek( fPtr, 
	       ( accountNum - 1 ) *  sizeof( struct clientTransaction ), 
		   SEEK_SET );
    fread( &client, sizeof( struct clientTransaction  ), 1,
	       fPtr );
    
    if( client.acctNum != 0)
        printf( "Account #%d already contains information\n", 
		        client.acctNum );
    else {
        printf( "Enter transaction amount\n? " );
        scanf( "%lf", &client.transaction );
        client.acctNum = accountNum;     
        fseek( fPtr, ( client.acctNum - 1 ) * 
                sizeof( struct clientTransaction ), SEEK_SET );
        fwrite( &client, sizeof( struct clientTransaction ), 1, 
                 fPtr );
	}
}

