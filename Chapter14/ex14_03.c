/*
 * Filename:    ex14_03.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/10/2017
 * Description: Command line args
 */
 
#include <stdio.h>

int main( int argc, char *argv[])
{
    int i;
 
    /* argv[0] is the name of the program */
    
    for(i=1; i<argc; i++)
        printf("%s\n", argv[i]);
    
    return 0;
}

