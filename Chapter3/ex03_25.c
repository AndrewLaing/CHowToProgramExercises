/*
 * Filename:    ex03_25.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
    int n;
    
    printf("N\t10*N\t100*N\t1000*N\n\n");
    
    for(n=1; n<=10; n++)
        printf("%d\t%d\t%d\t%d\n", n, (n*10), (n*100), (n*1000));
    
    return 0;
}
