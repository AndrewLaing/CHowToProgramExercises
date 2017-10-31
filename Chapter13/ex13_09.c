/*
 * Filename:    ex13_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/10/2017
 * Description: Macro
 */
 
#include <stdio.h>
#define PRINTARRAY(arr,lenArr) int printArrayCounter=0; \
                               for( ; printArrayCounter<lenArr; \
                                      printArrayCounter++ ) { \
                                   printf("%d\n", arr[printArrayCounter]); } 
                                            


int main()
{
    int test[] = {4,5,3,2,6};
    PRINTARRAY(test, 5);
    return 0;
}


