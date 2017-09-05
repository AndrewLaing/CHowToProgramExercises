/*
 * Filename:    ex10_06.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/07/2017.
 */

#include <stdio.h>

char *strcpy1( char* s1, const char *s2 );


struct inventory {
    char lastName[15];
    char firstName[15];
    int customerNumber;
    
    struct {
        char phoneNumber[11];
        char address[50];
        char city[15];
        char state[3];
        char zipCode[6];
    } personal;  
    
} customerRecord, *customerPtr; 


int main()
{    
    customerPtr = &customerRecord;
    
    strcpy1(customerRecord.lastName, "Jenkins"); 
    strcpy1(customerRecord.firstName, "Gillian"); 
    customerRecord.customerNumber = 10152;
        
    strcpy1(customerRecord.personal.phoneNumber, "018118055"); 
    strcpy1(customerRecord.personal.address, "251 Torrington Crescent"); 
    strcpy1(customerRecord.personal.city, "Leeds"); 
    strcpy1(customerRecord.personal.state, "YK"); 
    strcpy1(customerRecord.personal.zipCode, "S1 3ED"); 
    
    printf("a: %s\n", customerRecord.lastName);
    printf("b: %s\n", customerPtr->lastName);   
    printf("c: %s\n", customerRecord.firstName);
    printf("d: %s\n", customerPtr->firstName);  
    printf("e: %d\n", customerRecord.customerNumber);
    printf("f: %d\n", customerPtr->customerNumber); 
    printf("g: %s\n", customerRecord.personal.phoneNumber);
    printf("h: %s\n", customerPtr->personal.phoneNumber);
    printf("i: %s\n", customerRecord.personal.address);
    printf("j: %s\n", customerPtr->personal.address);
    
    printf("k: %s\n", customerRecord.personal.city);
    printf("l: %s\n", customerPtr->personal.city);
    printf("m: %s\n", customerRecord.personal.state);
    printf("n: %s\n", customerPtr->personal.state);
    printf("o: %s\n", customerRecord.personal.zipCode);
    printf("p: %s\n", customerPtr->personal.zipCode);
    return 0;
}

/* Using pointer arithmetic */
char *strcpy1( char* s1, const char *s2 )
{   
    char *result = s1;
    
    while(*s2!='\0')
        *s1++=*s2++;
        
    *s1='\0';
    return result;  
}

