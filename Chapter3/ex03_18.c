/*
 * Filename:	ex03_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/04/2017
 */

#include <stdio.h>

int main()
{
	int accountNumber;
	float beginningBalance, totalCharges, totalCredits, creditLimit;
	float balance;
    
    printf( "Enter account number (-1 to end): " );
    scanf( "%d", &accountNumber );

    while( accountNumber != -1) 
    {
	    printf( "Enter beginning balance: " );
	    scanf( "%f", &beginningBalance );
        printf( "Enter total charges: " );
   		scanf( "%f", &totalCharges );
        printf( "Enter total credits: " );
    	scanf( "%f", &totalCredits );
        printf( "Enter credit limit: " );
    	scanf( "%f", &creditLimit );
    	
    	balance = beginningBalance + totalCharges - totalCredits;
    	
    	if( balance > creditLimit )
    	{
    		printf( "Account:      %d\n", accountNumber );
    		printf( "Credit limit: %.2f\n", creditLimit );
    		printf( "Balance:      %.2f\n", balance );
    		printf( "Credit Limit Exceeded.\n" );
		}
    	
    	printf( "\n\nEnter account number (-1 to end): " );
    	scanf( "%d", &accountNumber );
	}
    
	return 0;
}

