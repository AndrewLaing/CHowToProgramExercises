/*
 * Filename:    ex10_08.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/07/2017.
 */

#include <stdio.h>

union integer {
    char c;
    short s;
    int i;
    long b;
};


int main()
{    
    union integer test1, test2, test3, test4;
    
    printf("Enter a char: ");
    scanf("%c", &test1.c);
    fflush(stdin);
    
    printf("Enter a short: ");
    scanf("%hd", &test2.s);
    fflush(stdin);
        
    printf("Enter an integer: ");
    scanf("%d", &test3.i);
    fflush(stdin);
        
    printf("Enter a long: ");
    scanf("%ld", &test4.b);
    fflush(stdin);
    
    printf("\n\ntest1.c as a char: %c\n", test1.c);    
    printf("test1.c as a short: %hd\n", test1.c);    
    printf("test1.c as an int: %d\n", test1.c);    
    printf("test1.c as a long: %ld\n", test1.c);
    
    printf("\n\ntest2.s as a char: %c\n", test2.s);    
    printf("test2.s as a short: %hd\n", test2.s);    
    printf("test2.s as an int: %d\n", test2.s);    
    printf("test2.s as a long: %ld\n", test2.s);
    
    printf("\n\ntest3.i as a char: %c\n", test3.i);    
    printf("test3.i as a short: %hd\n", test3.i);    
    printf("test3.i as an int: %d\n", test3.i);    
    printf("test3.i as a long: %ld\n", test3.i);
    
    printf("\n\ntest4.b as a char: %c\n", test4.b);    
    printf("test4.b as a short: %hd\n", test4.b);    
    printf("test4.b as an int: %d\n", test4.b);    
    printf("test4.b as a long: %ld\n", test4.b);  
    return 0;
}


