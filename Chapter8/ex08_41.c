/*
 * Filename:    ex08_41.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/07/2017.
 * Description: Dunning Letters
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *todaysDate  = "15/07/2017";
const char *invoiceDate = "15/12/2016";
const char *dueDate     = "15/03/2017";
const char *dateOfFirstLetter  = "15/04/2017";
const char *dateOfSecondLetter = "15/05/2017";
const char *dateOfThirdLetter  = "15/06/2017";
const char *dateOfFourthLetter = "15/07/2017";
const char *dateOfFifthLetter =  "15/08/2017";

int getLine( char [], int );
void printLetter1(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed);
void printLetter2(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed);
void printLetter3(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed);
void printLetter4(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed);                  
void printLetter5(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed);


int main()
{
    char input[10];
    char name[80];
    char address[80];
    char accountReference[10];
    double amountOwed;
    int ageOfAmountOwed = 0;
    
    printf("Enter debtor's name: ");
    getLine(name, 80);
    printf("Enter debtor's address: ");
    getLine(address, 80);
    printf("Enter debtor's account reference: ");
    getLine(accountReference, 80);
    printf("Enter amount owed: ");
    getLine(input, 80);
    sscanf(input, "%lf", &amountOwed);
    printf("Enter months amount overdue: ");
    getLine(input, 80);
    sscanf(input, "%d", &ageOfAmountOwed);
    
    printf("\n\n\n\n\n");

    if (ageOfAmountOwed >= 5 )
        printLetter5( name, address, accountReference, amountOwed, ageOfAmountOwed ); 
    else if (ageOfAmountOwed >= 4 )
        printLetter4( name, address, accountReference, amountOwed, ageOfAmountOwed ); 
    else if (ageOfAmountOwed >= 3 )
        printLetter3( name, address, accountReference, amountOwed, ageOfAmountOwed ); 
    else if (ageOfAmountOwed >= 2 )
        printLetter2( name, address, accountReference, amountOwed, ageOfAmountOwed ); 
    else
        printLetter1( name, address, accountReference, amountOwed, ageOfAmountOwed ); 
        
    return 0;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


void printLetter1(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed)
{
    printf("%s\n", name);
    printf("%s\n\n", address);
    printf("%s\n\n", todaysDate);
    printf("Dear Sir/Madam,\n\n");
    printf("Our Ref: %s\n\n", accountReference);

    printf("It has come to our attention that your account is overdue for payment.\n\n");

    printf("We are not aware of any disputes or reason for non-payment, therefore\n");
    printf("we would respectfully remind you that you have exceeded the trading terms \n");
    printf("for these outstanding amounts and we would be grateful to receive\n");
    printf("your remittance as soon as possible.\n\n");

    printf("The details of the outstanding invoices are as follows:\n\n");

    printf("%s\t%s\t%s\t%s\n", "Invoice No","Invoice Date","Due Date","Amount");
    printf("%05d\t\t%s\t%s\t$%0.2f\n\n", 00001, invoiceDate , dueDate ,amountOwed);

    printf("We look forward to hearing from you.\n\n");

    printf("Yours sincerely,\n\n\n\n\n\n");

    printf("On behalf of Laing Software Services\n\n");
}


void printLetter2(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed)
{
    printf("%s\n", name);
    printf("%s\n\n", address);
    printf("%s\n\n", todaysDate);
    printf("Dear Sir/Madam,\n\n");
    printf("Our Ref: %s\n\n", accountReference);


    printf("Second Request For Payment\n\n");

    printf("Further to our previous correspondence dated %s,\n", dateOfFirstLetter);
    printf("your account is still overdue for payment. We would respectfully remind you \n");
    printf("that you have exceeded the trading terms for these outstanding amounts \n");
    printf("and we would be grateful to receive your remittance by return.\n\n");

    printf("The details of the outstanding invoices are as follows:\n\n");

    printf("%s\t%s\t%s\t%s\n", "Invoice No","Invoice Date","Due Date","Amount");
    printf("%05d\t\t%s\t%s\t$%0.2f\n\n", 00001, invoiceDate , dueDate ,amountOwed);

    printf("We look forward to hearing from you.\n\n");

    printf("Yours sincerely,\n\n\n\n\n\n");

    printf("On behalf of Laing Software Services\n\n");
}


void printLetter3(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed)
{
    printf("%s\n", name);
    printf("%s\n\n", address);
    printf("%s\n\n", todaysDate);
    printf("Dear Sir/Madam,\n\n");
    printf("Our Ref: %s\n\n", accountReference);
    
    printf("Final Request For Payment \n\n");

    printf("Further to our previous correspondence dated %s, your account \n", dateOfSecondLetter );
    printf("is still overdue for payment. We would respectfully remind you that \n");
    printf("you have exceeded the trading terms for these outstanding amounts and we\n");
    printf("would be grateful to receive your remittance before %s to avoid\n", dateOfThirdLetter );
    printf("this overdue amount being passed to a commercial debt recovery service.\n\n");

    printf("The details of the outstanding invoices are as follows:\n\n");

    printf("%s\t%s\t%s\t%s\n", "Invoice No","Invoice Date","Due Date","Amount");
    printf("%05d\t\t%s\t%s\t$%0.2f\n\n", 00001, invoiceDate , dueDate ,amountOwed);

    printf("We look forward to hearing from you.\n\n");

    printf("Yours sincerely,\n\n\n\n\n\n");

    printf("On behalf of Laing Software Services\n\n");
}


void printLetter4(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed)
{
    printf("%s\n", name);
    printf("%s\n\n", address);
    printf("%s\n\n", todaysDate);
    printf("Without Prejudice\n\n");
    printf("Outstanding Invoices - Laing Software Services\n\n");

    printf("Our Ref: %s\n\n", accountReference);    
    printf("Final Letter before Action - via email & tracked post\n\n");

    printf("We are disappointed to see that despite numerous requests, payment \n");
    printf("for the overdue invoices as listed below has still not been received.\n\n");

    printf("%s\t%s\t%s\t%s\n", "Invoice No","Invoice Date","Due Date","Amount");
    printf("%05d\t\t%s\t%s\t$%0.2f\n\n", 00001, invoiceDate , dueDate ,amountOwed);

    printf("Under the Late Payment of Commercial Debts Regulations 2013 we are entitled \n");
    printf("to claim late payment interest & compensation charges. \n\n");

    printf("Take notice that if full payment of the $%0.2f is not received in our\n", amountOwed);
    printf("bank account by close of business on %s, we shall,\n", dateOfFifthLetter);
    printf("without further notice, begin legal action to recover the debt, all \n");
    printf("court costs and statutory interest of 8%% above the Bank of England base\n");
    printf("rate (fixed for the six month period within which date the invoice became\n");
    printf("overdue) pursuant to the late payment legislation to be borne by yourselves.\n\n");
    printf("To prevent this from happening please pay in full now.\n\n");
    printf("Please accept our apologies if payment has been made within the last 24 hours.\n\n");
 
    printf("This is our final communication on the issue.\n\n\n\n\n\n");

    printf("On behalf of Laing Software Services\n\n");
}

              
void printLetter5(char *name, char *address, char *accountReference, 
                  double amountOwed, int ageOfAmountOwed)
{
    printf("%s\n", name);
    printf("%s\n\n", address);
    printf("%s\n\n", todaysDate);
    printf("Notification of Transference of Debt \n\n");
    printf("Outstanding Invoices - Laing Software Services\n\n");

    printf("Our Ref: %s\n\n", accountReference);    
    printf("Notification of Actions to be Taken\n\n");

    printf("Despite our numerous requests for payment for the overdue invoices listed \n");
    printf("below no money has been received.\n\n");

    printf("%s\t%s\t%s\t%s\n", "Invoice No","Invoice Date","Due Date","Amount");
    printf("%05d\t\t%s\t%s\t$%0.2f\n\n", 00001, invoiceDate , dueDate ,amountOwed);

    printf("The amount to pay as of today currently stands at $%0.2f and the company\n", amountOwed);
    printf("has decided that, due to your total lack of effort in attempting to make\n");
    printf("even a single offer of payment, your debt will be passed on to be dealt \n");
    printf("with by our business partners the Corlioni family.\n\n");

    printf("The Corlioni family take debt collection very seriously indeed, so in order\n");
    printf("to avoid the consequences their involvement may have upon your business\n");
    printf("it is recommended that you please pay your debt in full immediately. \n\n");

    printf("This is the last letter you will receive from us on the issue, as it is\n");
    printf("no longer our problem to deal with.\n\n\n\n\n\n");

    printf("On behalf of Laing Software Services\n\n");
}


