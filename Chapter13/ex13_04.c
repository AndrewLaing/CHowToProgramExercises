/*
 * Filename:    ex13_04.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/10/2017
 * Description: Macro
 */
 
#include <stdio.h>
#define PI 3.14159
#define SPHEREVOLUME(x) ( (4.0 / 3) * PI * ( (x) * (x) * (x) ) )


int main()
{
    int i;
    printf("Radius\tVolume\n\n");
    for(i=1; i<=10; i++)
    {
        printf("%3d\t%lf\n", i, SPHEREVOLUME(i));
    }
    return 0;
}


