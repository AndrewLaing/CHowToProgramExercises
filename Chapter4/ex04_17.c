/*
 * Filename:	ex04_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/04/2017
 * Description: Collecting money becomes increasingly difficult during
 *				periods of recession, so companies may tighten their credit
 *				limits to prevent their accounts receivable (money owed to
 *				them) from becoming too large. In response to a prolonged 
 *				recession, one company has cut its customer's credit
 *				limit in half. Thus, if a particular customer has a credit
 *				limit of $2000, this customer's credit limit is now $1000.
 *				Write as program that analyses the credit status of three
 *				customers of this company. For each customer you are given;
 *					1. The customer's account number
 *					2. The customer's credit limit before the recession.
 *					3. The customer's current balance (i.e., The amount the
 *					   customer owes the company.)
 *				Your program should calculate and print the new credit limit
 *				for each customer and print which customers have current
 *				balances that exceed their new credit limits. 
 */

#include <stdio.h>


int main()
{   
    // Initialise variables
    int accountNumber, oldCreditLimit, newCreditLimit, balance;
    int count;
     
    // While count < 3
    for(count=1; count<=3; count++)
    {
		// Input account number
		printf("\nInput account number: ");
		scanf("%d", &accountNumber);
		
		// Input credit limit before the recession
		printf("Input credit limit before the recession: ");
		scanf("%d", &oldCreditLimit);
		
		// Input current balance
		printf("Input current balance: ");
		scanf("%d", &balance);
		
		// Calculate and print new credit limit
		newCreditLimit = oldCreditLimit / 2;
		printf("Customer's new credit limit is $%d\n", newCreditLimit);
		
		// Print if customer has exceeded their credit limit
		if(balance > newCreditLimit) 
		{
		    printf("Customer with account %d has exceeded their credit limit!!\n", accountNumber);
		}
    }

	return 0;
}

