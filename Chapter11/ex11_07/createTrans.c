/*
 * Filename:	createTrans.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/07/2017.
 */
 
#include <stdio.h>

struct clientTransaction { 
   int acctNum;
   double transaction;
};

int main()
{ 
   int i;
   struct clientTransaction blankClient = { 0, 0.0 };
   FILE *cfPtr;
 
   if ( ( cfPtr = fopen( "trans.dat", "wb" ) ) == NULL )
      printf( "File could not be opened.\n" );
   else { 

      for ( i = 1; i <= 1000; i++ )
         fwrite( &blankClient, 
                sizeof( struct clientTransaction ), 1, cfPtr );

      fclose ( cfPtr );
      printf("File \"trans.dat\" created.\n");
   }

   return 0;
}

