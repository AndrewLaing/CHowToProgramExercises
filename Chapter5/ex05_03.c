/*
 * Filename:    ex05_03.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/04/2017
 * Description: Write a program that tests if the examples of the 
 *              math library function calls shown in Fig 5.2 actually
 *              produce the indicated results. 
 */

#include <stdio.h>
#include <math.h>


int main()
{
    printf("sqrt(900.0) = %.1f\n", sqrt(900.0));
    printf("sqrt(9.0) = %.1f\n", sqrt(9.0));

    printf("exp(1.0) = %f\n", exp(1.0));
    printf("exp(2.0) = %f\n", exp(2.0));

    printf("log(2.718282) = %.1f\n", log(2.718282));
    printf("log(7.389056) = %.1f\n", log(7.389056));
    
    printf("log10(1.0) = %.1f\n", log10(1.0));
    printf("log10(10.0) = %.1f\n", log10(10.0));
    printf("log10(100.0) = %.1f\n", log10(100.0));
    
    printf("fabs(5.0) = %.1f\n", fabs(5.0));
    printf("fabs(0.0) = %.1f\n", fabs(0.0));
    printf("fabs(-5.0) = %.1f\n", fabs(-5.0));
    
    printf("ceil(9.2) = %.1f\n", ceil(9.2));
    printf("ceil(-9.8) = %.1f\n", ceil(-9.8));
    
    printf("floor(9.2) = %.1f\n", floor(9.2));
    printf("floor(-9.8) = %.1f\n", floor(-9.8));

    printf("pow(2,7) = %.1f\n", pow(2,7));
    printf("pow(9,.5) = %.1f\n", pow(9,.5));
    
    printf("fmod(13.657, 2.333) = %.3f\n", fmod(13.657, 2.333));
    
    printf("sin(0.0) = %.1f\n", sin(0.0));

    printf("cos(0.0) = %.1f\n", cos(0.0));

    printf("tan(0.0) = %.1f\n", tan(0.0));
     
    return 0;
}

