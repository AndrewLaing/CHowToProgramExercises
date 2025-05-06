/*
 * Filename:    ex13_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/10/2017
 * Description: Macro
 */
 
#include <stdio.h>
#define SUMARRAY(arr,lenArr) i=0; \
                             total = 0; \
                               for( ; i<lenArr; i++ ) { \
                                   total += arr[i]; } \
                             printf("SUM = %d\n", total);
// store the result in the variable given in parameter                             
#define SUMARRAY1(arr,lenArr,sumTotal) i=0; \
                                       sumTotal = 0; \
                                       for( ; i<lenArr; i++ ) { \
                                           sumTotal += arr[i]; }


int main()
{    
    int i, total;
    
    int test[] = {4,5,3,2,6};
    SUMARRAY(test, 5);

    SUMARRAY1(test, 5, total);
    printf("Total = %d\n", total);
    
    return 0;
}


