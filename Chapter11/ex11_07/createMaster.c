/*
 * Filename:    createMaster.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/07/2017.
 */
 
#include <stdio.h>

struct clientData { 
   int acctNum;
   char lastName[ 15 ];
   char firstName[ 10 ];
   double balance;
};

int main()
{ 
   int i;
   struct clientData blankClient = { 0, "", "", 0.0 };
   FILE *cfPtr;
 
   if ( ( cfPtr = fopen( "oldMast.dat", "wb" ) ) == NULL )
      printf( "File could not be opened.\n" );
   else { 

      for ( i = 1; i <= 1000; i++ )
         fwrite( &blankClient, 
                sizeof( struct clientData ), 1, cfPtr );

      fclose ( cfPtr );
      printf("File \"oldMast.dat\" created.\n");
   }

   return 0;
}

