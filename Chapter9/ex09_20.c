/*
 * Filename:    ex09_20.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        18/07/2017.
 */

#include <stdio.h>


int main()
{    
    double num = 9876.12345;
    printf("Precision 1: %0.1lg\n", num);
    printf("Precision 2: %0.2lg\n", num);
    printf("Precision 3: %0.3lg\n", num);
    printf("Precision 4: %0.4lg\n", num);
    printf("Precision 5: %0.5lg\n", num);
    printf("Precision 6: %0.6lg\n", num);
    printf("Precision 7: %0.7lg\n", num);
    printf("Precision 8: %0.8lg\n", num);
    printf("Precision 9: %0.9lg\n", num);

    return 0;
}

