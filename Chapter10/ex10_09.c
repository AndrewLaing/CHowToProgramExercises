/*
 * Filename:    ex10_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        21/07/2017.
 * Note: https://stackoverflow.com/questions/4089174/printf-and-long-double
 
         If you are using MinGW, the problem is that by default, 
         MinGW uses the I/O resp. formatting functions from the 
         Microsoft C runtime, which doesn't support 80 bit floating point 
         numbers (long double == double in Microsoft land).

         However, MinGW also comes with a set of alternative implementations 
         that do properly support long doubles. To use them, prefix the 
         function names with __mingw_ (e.g. __mingw_printf). 
         Depending on the nature of your project, you might also want to 
         globally #define printf __mingw_printf or use -D__USE_MINGW_ANSI_STDIO 
         (which enables the MinGW versions of all the printf-family functions).
         
                                                   -- klickverbot
 */

#include <stdio.h>

union floatingPoint {
    float f;
    double d;
    long double x;
};


int main()
{    
    union floatingPoint test1, test2, test3;
    
    printf("Enter a float: ");
    scanf("%f", &test1.f);
    fflush(stdin);
    
    printf("Enter a double: ");
    scanf("%lf", &test2.d);
    fflush(stdin);
        
    printf("Enter a long double: ");
    scanf("&le", &test3.x);
    fflush(stdin);

    
    printf("\n\ntest1.f as a float: %f\n", test1.f);     
    printf("test1.f as a double: %lf\n", test1.f);    
    printf("test1.f as a long double: %lf\n", test1.f);
        
    printf("\n\ntest2.d as a float: %f\n", test2.d);     
    printf("test2.d as a double: %lf\n", test2.d);    
    printf("test2.d as a long double: %lf\n", test2.d);
     
    printf("\n\ntest3.x as a float: %f\n", test3.x);     
    printf("test3.x as a double: %lf\n", test3.x);    
    printf("test3.x as a long double: %lf\n", test3.x);
    
 
    return 0;
}


