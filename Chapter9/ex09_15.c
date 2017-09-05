/*
 * Filename:    ex09_15.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        17/07/2017.
 */

#include <stdio.h>



int main()
{   
    /* Note: see compiler warning. Had trigraphs been enabled
     *       the top line would have printed a pipe symbol 
     *       instead of ??! */
    printf("trigraph ??! trigraph\n");
    printf("trigraph \?\?! trigraph\n");
    printf("trigraph ?" "?! trigraph\n");
    return 0;
}


