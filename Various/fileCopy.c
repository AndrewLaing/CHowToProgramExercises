/*
 * Filename:	fileCopy.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/07/2017.
 */
 
#include <stdio.h>


int main()
{ 
   	size_t res1;
	unsigned char buffer[8192]; /* used to copy contents */
	
    FILE *ofPtr = fopen("oldMast.dat", "rb");
    FILE *nfPtr = fopen("newMast.dat", "wb");
    
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
		    		return -1;
				}
		      	// handle error
		    	else {
		    		printf("ERROR - media full!\n");
		    		return -1;
				}
		  	}
		}
		
	    fclose(ofPtr);
	    fclose(nfPtr);			
	}

	return 0;
}

