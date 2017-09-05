/*
 * Filename:	ex11_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        25/07/2017.
 * Description: Includes the neccessary code for exercises 11_08 and 11_09
 *              To run this program first use;
 *                 createMaster, populateMaster,    to create oldMast.dat
 *                 populateTrans                    to create trans.dat
 *              to create the files needed.
 * Todo:        Allow the user to enter the filennames either from args
 *              or from stdin
 */
 
#include <stdio.h>

struct clientData { 
   int acctNum;
   char lastName[ 15 ];
   char firstName[ 10 ];
   double balance;
};

struct clientTransaction { 
   int acctNum;
   double transaction;
};


int createNewMaster( FILE * );
int updateNewMaster( FILE * );
void updateRecord( FILE *, int, double );
int fileCopy( FILE *, FILE * );


const int DEBUG = 1;
void textFile( FILE *, char * ); /* for debugging and proving that file contents
                                  * have been created and updated */

int main()
{ 
    FILE *nfPtr = fopen("newMast.dat", "wb+");
    
    if( createNewMaster( nfPtr ) == 0 ) {
    	printf("Error - unable to create newMast.dat\n");
    	return -1;
	}
	printf("Back here\n");
	fclose(nfPtr);
	
	nfPtr = fopen("newMast.dat", "rb+");
	if(DEBUG)  textFile( nfPtr, "newMast1.txt" ); /* */

    if( updateNewMaster( nfPtr ) == 0 ) {
    	printf("Error - unable to update newMast.dat\n");
    	return -1;
	}
	
	if(DEBUG)  textFile( nfPtr, "newMast2.txt" ); /* */
    
    fclose(nfPtr);	
	return 0;
}


int createNewMaster( FILE *nfPtr )
{
	int created;
	FILE *ofPtr = fopen("oldMast.dat", "rb");
	
	created = fileCopy( ofPtr, nfPtr );
    
    fclose(ofPtr);
    return created;
}


int updateNewMaster( FILE *nfPtr )
{
    struct clientTransaction client = { 0, 0.0 };
    
	FILE *tfPtr = fopen("trans.dat", "rb");
	
	if( tfPtr == NULL) {
		printf( "\"trans.dat\" could not be opened.\n" );
		return 0;
	}
        
    while ( !feof( tfPtr  ) ) { 
        fread( &client, sizeof( struct clientTransaction ), 1, 
            tfPtr );

        if ( client.acctNum != 0 ) {
         	updateRecord( nfPtr, client.acctNum, client.transaction );
		}
    }
    
    fclose(tfPtr);
    return 1;
}


void updateRecord( FILE *fPtr, int account, double transaction )
{
    struct clientData client = { 0, "", "", 0.0 };
    
    fseek( fPtr, 
	       ( account - 1 ) * sizeof( struct clientData ), 
		   SEEK_SET );
    fread( &client, sizeof( struct clientData ), 1,
	       fPtr );
    
    if( client.acctNum == 0)
        printf( "Unmatched transaction record for account number %d\n", account );
    else {
        client.balance += transaction;
        
	    fseek( fPtr, 
		       ( account - 1 ) * sizeof( struct clientData ), 
			   SEEK_SET );
	    fwrite( &client, sizeof( struct clientData ), 1, 
		        fPtr );
	}
}


int fileCopy( FILE *ofPtr, FILE *nfPtr )
{
   	size_t res1;
	unsigned char buffer[8192]; /* used to copy contents */
    
    if( ofPtr == NULL)
        printf( "\"oldMast.dat\" could not be opened.\n" );
    else if( nfPtr == NULL )
        printf( "\"newMast.dat\" could not be opened.\n" );
    else 
	{
		while((res1 = fread(buffer, 1, sizeof buffer, ofPtr )) > 0) 
		{
			size_t res2 = fwrite(buffer, 1, res1, nfPtr );
		  	if(res2 < res1) 
			{
		    	if(ferror(nfPtr)) {
		    		printf("ERROR - unable to write to file!\n");
		    		return 0;
				}
		      	// handle error
		    	else {
		    		printf("ERROR - media full!\n");
		    		return 0;
				}
		  	}
		}		
	}
	
	return 1;
}


void textFile( FILE *readPtr, char *filename )
{
   struct clientData client = { 0, "", "", 0.0 };
   FILE *writePtr;
 
   if ( ( writePtr = fopen( filename, "w" ) ) == NULL )
        printf( "File could not be opened.\n" );
   else { 
        rewind( readPtr );
        fprintf( writePtr, "%-6s%-16s%-11s%10s\n",
	          "Acct", "Last Name", "First Name", "Balance" );
	          
	    while ( !feof( readPtr  ) ) { 
            fread( &client, sizeof( struct clientData ), 1, 
                readPtr );

	        if ( client.acctNum != 0 ) {
	         	fprintf( writePtr, "%-6d%-16s%-11s%10.2f\n", 
	                    client.acctNum, client.lastName, 
	                    client.firstName, client.balance );
			}
            
         }
	          
	  fclose( writePtr );
      printf("File \"%s\" created\n",filename );
   }  
}

