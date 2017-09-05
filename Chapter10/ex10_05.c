/*
 * Filename:    ex10_05.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/07/2017.
 */

#include <stdio.h>
char *strcpy1( char* s1, const char *s2 );

struct inventory {
    char partName[30];
    int partNumber;
    float price;
    int stock;
    int reorder;
}; 


union data {
    char c;
    short s;
    float f;
    double d;
};


struct address {
    char streetAddress[25];
    char city[20];
    char state[3];
    char zipCode[6];
};


struct student {
    char firstName[15];
    char lastName[15];
    struct address homeAddress;
};


struct test {
    unsigned a : 1;
    unsigned b : 1;
    unsigned c : 1;
    unsigned d : 1;
    unsigned e : 1;
    unsigned f : 1;
    unsigned g : 1;
    unsigned h : 1;
    unsigned i : 1;
    unsigned j : 1;
    unsigned k : 1;
    unsigned l : 1;
    unsigned m : 1;
    unsigned n : 1;
    unsigned o : 1;
    unsigned p : 1;
};

int main()
{    
    /* Use of a union */
    union data uniontest;
    uniontest.c = 'A';
    printf("uniontest.c = %c\n", uniontest.c);
    uniontest.d = 1.234;
    printf("uniontest.d = 1.234;\n");
    printf("uniontest.d = %0.3f\n\n", uniontest.d);
    
    /* Struct tests */
    struct address bobsAddress;
    strcpy1(bobsAddress.city, "Sheffield");
    strcpy1(bobsAddress.state, "YK");
    strcpy1(bobsAddress.streetAddress, "12 Addison Terrace");
    strcpy1(bobsAddress.zipCode, "S1 4DF");
    
    printf("Bobs address:\n%s\n%s\n%s\n%s\n\n",
           bobsAddress.streetAddress,
           bobsAddress.city,
           bobsAddress.state,
           bobsAddress.zipCode );
           
    struct student classRep;
    strcpy1( classRep.firstName, "Bob");
    strcpy1( classRep.lastName , "Jenkinson");
        
    classRep.homeAddress = bobsAddress; 
    printf("Student rep: %s %s\n%s\n%s\n%s\n%s\n\n",
           classRep.firstName, classRep.lastName, 
           classRep.homeAddress.streetAddress,
           classRep.homeAddress.city,
           classRep.homeAddress.state,
           classRep.homeAddress.zipCode );
           
    struct test Test;
    Test.e = 1;
    Test.n = 0;
    printf("Test.e = %d Test.n = %d\n", Test.e, Test.n);
    
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

