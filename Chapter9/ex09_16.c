/*
 * Filename:	ex09_16.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        17/07/2017.
 */

#include <stdio.h>



int main()
{	 
	int a,b,c,d,e,f;
	short g;
	long h;
	 
    printf("a: Enter 437: ");
    scanf("%d", &a);
    fflush(stdin);	 
    
    printf("b: Enter 437: ");
    scanf("%i", &b);
    fflush(stdin);	 
    
    printf("c: Enter 437: ");
    scanf("%o", &c);
    fflush(stdin);	 
    
    printf("d: Enter 437: ");
    scanf("%u", &d);
    fflush(stdin);	 
    
    printf("e: Enter 437: ");
    scanf("%x", &e);
    fflush(stdin);	 
    
    printf("f: Enter 437: ");
    scanf("%X", &f);
    fflush(stdin);	
	 
    printf("g: Enter 437: ");
    scanf("%hd", &g);
    fflush(stdin);	 
    
    printf("h: Enter 437: ");
    scanf("%ld", &h);
    fflush(stdin);
    
    
    printf("\n---- a %%d ----\n");
    printf("%%d  = %d\n", a);
    printf("%%i  = %i\n", a);
    printf("%%o  = %o\n", a);
    printf("%%u  = %u\n", a);
    printf("%%x  = %x\n", a);
    printf("%%X  = %X\n", a);
    printf("%%hd = %hd\n", a);
    printf("%%ld = %ld\n", a);
    
    printf("\n---- b %%i ----\n");
    printf("%%d  = %d\n", b);
    printf("%%i  = %i\n", b);
    printf("%%o  = %o\n", b);
    printf("%%u  = %u\n", b);
    printf("%%x  = %x\n", b);
    printf("%%X  = %X\n", b);
    printf("%%hd = %hd\n", b);
    printf("%%ld = %ld\n", b);
    
    printf("\n---- c %%o ----\n");
    printf("%%d  = %d\n", c);
    printf("%%i  = %i\n", c);
    printf("%%o  = %o\n", c);
    printf("%%u  = %u\n", c);
    printf("%%x  = %x\n", c);
    printf("%%X  = %X\n", c);
    printf("%%hd = %hd\n", c);
    printf("%%ld = %ld\n", c);  
    
    printf("\n---- d %%u ----\n");
    printf("%%d  = %d\n", d);
    printf("%%i  = %i\n", d);
    printf("%%o  = %o\n", d);
    printf("%%u  = %u\n", d);
    printf("%%x  = %x\n", d);
    printf("%%X  = %X\n", d);
    printf("%%hd = %hd\n", d);
    printf("%%ld = %ld\n", d); 
    
    printf("\n---- e %%x ----\n");
    printf("%%d  = %d\n", e);
    printf("%%i  = %i\n", e);
    printf("%%o  = %o\n", e);
    printf("%%u  = %u\n", e);
    printf("%%x  = %x\n", e);
    printf("%%X  = %X\n", e);
    printf("%%hd = %hd\n", e);
    printf("%%ld = %ld\n", e); 
    
    printf("\n---- f %%x ----\n");
    printf("%%d  = %d\n", f);
    printf("%%i  = %i\n", f);
    printf("%%o  = %o\n", f);
    printf("%%u  = %u\n", f);
    printf("%%x  = %x\n", f);
    printf("%%X  = %X\n", f);
    printf("%%hd = %hd\n", f);
    printf("%%ld = %ld\n", f); 
    
    printf("\n---- g %%hd ----\n");
    printf("%%d  = %d\n", g);
    printf("%%i  = %i\n", g);
    printf("%%o  = %o\n", g);
    printf("%%u  = %u\n", g);
    printf("%%x  = %x\n", g);
    printf("%%X  = %X\n", g);
    printf("%%hd = %hd\n", g);
    printf("%%ld = %ld\n", g); 
    
    printf("\n---- h %%ld ----\n");
    printf("%%d  = %d\n", h);
    printf("%%i  = %i\n", h);
    printf("%%o  = %o\n", h);
    printf("%%u  = %u\n", h);
    printf("%%x  = %x\n", h);
    printf("%%X  = %X\n", h);
    printf("%%hd = %hd\n", h);
    printf("%%ld = %ld\n", h); 

	return 0;
}


