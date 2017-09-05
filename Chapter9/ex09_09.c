/*
 * Filename:	ex09_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        17/07/2017.
 */

#include <stdio.h>

int main()
{	
    int a = 455;
    int *a1;    
    a1 = &a;
    
    int b = -455;
    int *b1;
    b1 = &a;
    
    short c = 32000;
    short *c1;
    c1 = &c;
    
    long int d = 2000000000L;
    long int *d1 = &d;
    int e = 0455;
    unsigned int f = 455;
    unsigned int g = -455;
    int h = 0x455;



	printf("%d\n", &a1);	
	printf("%i\n", &b1);	
	printf("%d\n", &a1);
	printf("%hd\n", &c1);    /* h is short */	
	printf("%ld\n", &d1);    /* l is long */	
	printf("%o\n", &a1);	
	printf("%u\n", &a1);	
	printf("%u\n", &b1);	
	printf("%x\n", &a1);	
	printf("%X\n", &a1);
	printf("%p\n", a1);

	return 0;
}



