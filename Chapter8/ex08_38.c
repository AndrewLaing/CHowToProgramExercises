/*
 * Filename:    ex08_38.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        10/07/2017.
 * Todo:        Do a test version - see notes
 */

#include <stdio.h>
#include <string.h>
#define PERMITTEDLENGTH 9

void printNumberInWords( double );
int getLine( char [], int );
double asciiToDouble( const char * );

const char belowTwenty[20][10] = {
        "Zero","One","Two","Three","Four","Five","Six","Seven","Eight",
        "Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen",
        "Sixteen","Seventeen","Eighteen","Nineteen"
};

const char tens[10][10] = {
        "Zero","Ten","Twenty","Thirty","Fourty","Fifty","Sixty",
        "Seventy","Eighty","Ninety"
};

int main()
{
    char amount[PERMITTEDLENGTH+1];
    double toPay;
    
    printf("Enter amount to be paid: ");
    getLine(amount, PERMITTEDLENGTH+1);
    
    toPay = asciiToDouble(amount);
    
    /* Add this to keep pennies accurate */
    toPay+=0.0000000001;
    
    if(toPay>999999.99) {
        printf("\n!!!!! Invalid Amount - Notifying security !!!!!\n");
        return -1;
    }
    
    printNumberInWords( toPay );
    
    return 0;
}


void printNumberInWords( double amount )
{
    int temp;
    int sum = (int)amount;
    int overThousand=0, overHundred=0, overHundred1=0;  
    int pennies = (int)( (amount - (int)amount)*100);
    
    if(sum >= 100000)
    {
        temp = sum/100000;
        printf("%s ", belowTwenty[temp]);
        sum = sum - temp*100000;
        overHundred1++;
        overThousand++;
    }
    
    if(overHundred1 > 0)
        printf("Hundred ");
    
    if(sum >= 20000)
    {
        temp = sum/10000;
        printf("%s ", tens[temp]);
        sum = sum - temp*10000;
        overThousand++;
    }
    
    if(sum >= 1000)
    {
        temp = sum/1000;
        printf("%s ", belowTwenty[temp]);
        sum = sum - temp*1000;
        overThousand++;
    }
    
    if(overThousand > 0)
        printf("Thousand ");
        
    if(sum >= 100)
    {
        temp = sum/100;
        printf("%s ", belowTwenty[temp]);
        sum = sum - temp*100;
        overHundred++;
    }
    
    if(overHundred > 0)
        printf("Hundred ");
    
    if(sum >= 20)
    {
        temp = sum/10;
        printf("%s ", tens[temp]);
        sum = sum - temp*10;
        overThousand++;
    }
    
    if(sum >= 1)
    {
        printf("%s ", belowTwenty[sum]);
    }
    
    if(pennies>0)
        printf("%d/100", pennies);
    
    printf("\n");
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


double asciiToDouble(const char *str)
{
    double result;
    sscanf(str, "%lf", &result);
    
    return result;
}


