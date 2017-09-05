/*
 * Filename:	ex04_24.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        22/04/2017
 * Description: Print a table of decimal, binary, octal and
 *				hexadecimal equivalents.
 */

#include <stdio.h>

int main()
{    
    printf( "Decimal\tBinary\tOctal\tHex\n" );
    printf( "0\t0\t0\t0\n" );
    printf( "1\t1\t1\t1\n" );
    printf( "2\t10\t2\t2\n" );    
    printf( "3\t11\t3\t3\n" );    
    printf( "4\t100\t4\t4\n" );    
    printf( "5\t101\t5\t5\n" );    
    printf( "6\t110\t6\t6\n" );    
    printf( "7\t111\t7\t7\n" );    
    printf( "8\t1000\t10\t8\n" );
    printf( "9\t1001\t11\t9\n" );    
    printf( "10\t1010\t12\tA\n" ); 
    printf( "11\t1011\t13\tB\n" );    
    printf( "12\t1100\t14\tC\n" );    
    printf( "13\t1101\t15\tD\n" );
    printf( "14\t1110\t16\tE\n" );    
    printf( "15\t1111\t17\tF\n" ); 
    
	return 0;
}

