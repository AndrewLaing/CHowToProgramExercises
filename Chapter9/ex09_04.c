/*
 * Filename:    ex09_04.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        16/07/2017.
 */

#include <stdio.h>

int main()
{   
    unsigned int a = 40000;
    printf("a - %-15.8unext item\n\n", a);
    
    int hex;
    printf("Enter a number in hex eg 12A or 0x12A: ");
    scanf("%x", &hex);
    
    fflush(stdin); /* clear stdin */
    
    printf("b - %X = %d\n\n", hex, hex);
    
    printf("c - %+d\n     %d\n\n", 200, 200);
    
    printf("d - %#x\n\n", 100);
    
    char s[20];
    printf("Enter a string: ");
    scanf("%[^p]", s);
    printf("e - %s\n\n", s);
    
    fflush(stdin); /* clear stdin */
    
    printf("f - %09f\n\n", 1.234);

    int hour, min, sec; 
    printf("Enter a time in the format hh:mm:ss: ");
    scanf("%d%*c%d%*c%d", &hour, &min, &sec);
    printf("g - hours = %d  minutes = %d  seconds = %d\n\n", hour, min, sec);
    
    fflush(stdin); /* clear stdin */
    
    char s1[20];
    printf("Enter a string enclosed in double quotes: ");
    scanf("\"%[^\"]", s1);
    printf("h - %s\n\n", s1);
    
    fflush(stdin); /* clear stdin */
    
    int hour1, min1, sec1;  
    printf("Enter a time in the format hh:mm:ss: ");
    scanf("%d:%d:%d", &hour1, &min1, &sec1);
    printf("i - hours = %d  minutes = %d  seconds = %d\n\n", hour1, min1, sec1);
    return 0;
}

