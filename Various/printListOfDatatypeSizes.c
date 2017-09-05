/*
 * Filename:	ex11_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        30/07/2017.
 */

#include <stdio.h>

int main(int argc, char **argv)
{	   
    FILE *ofPtr;

    if ( ( ofPtr = fopen( "datasize.dat", "w" ) ) == NULL )
    {
    	printf("Error - unable to open file \"%s\"\n", argv[1]);
    	return -1;
	}


    fprintf(ofPtr, "%-25s%5s\n", "Data Type", "Size");
    fprintf(ofPtr, "%-25s%5d\n", "char", sizeof(char));
    fprintf(ofPtr, "%-25s%5d\n", "unsigned char", sizeof(unsigned char));
    fprintf(ofPtr, "%-25s%5d\n", "short int", sizeof(short int));
    fprintf(ofPtr, "%-25s%5d\n", "unsigned short int", sizeof(unsigned short int));  
    fprintf(ofPtr, "%-25s%5d\n", "int", sizeof(int));
    fprintf(ofPtr, "%-25s%5d\n", "unsigned int", sizeof(unsigned int));  
    fprintf(ofPtr, "%-25s%5d\n", "long int", sizeof(long int));
    fprintf(ofPtr, "%-25s%5d\n", "unsigned long int", sizeof(unsigned long int));  
    fprintf(ofPtr, "%-25s%5d\n", "float", sizeof(float));
    fprintf(ofPtr, "%-25s%5d\n", "double", sizeof(double));  
    fprintf(ofPtr, "%-25s%5d\n", "long double", sizeof(long double));     

 	return 0;
}


