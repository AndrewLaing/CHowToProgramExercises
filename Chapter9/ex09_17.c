/*
 * Filename:    ex09_17.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/07/2017.
 */

#include <stdio.h>



int main()
{   
    float a, b, c;
     
    printf("a: Enter 1.2345: ");
    scanf("%e", &a);
    fflush(stdin);   
    
    printf("b: Enter 1.2345: ");
    scanf("%f", &b);
    fflush(stdin);   
    
    printf("c: Enter 1.2345: ");
    scanf("%g", &c);
    fflush(stdin);   
    

    
    printf("\n---- a %%e ----\n");
    printf("%%e  = %e\n", a);
    printf("%%f  = %f\n", a);
    printf("%%g  = %g\n", a);

    
    printf("\n---- b %%f ----\n");
    printf("%%e  = %e\n", b);
    printf("%%f  = %f\n", b);
    printf("%%g  = %g\n", b);

    
    printf("\n---- c %%o ----\n");
    printf("%%e  = %e\n", c);
    printf("%%f  = %f\n", c);
    printf("%%g  = %g\n", c);


    return 0;
}


