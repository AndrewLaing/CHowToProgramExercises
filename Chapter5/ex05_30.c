/*
 * Filename:    ex05_30.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        03/05/2017
 */

#include <stdio.h>

int qualityPoints( int );


int main()
{
    int n;
    
    printf("Enter the student's average: ");
    scanf("%d", &n);
    
    printf("The quality points of the students = %d\n", qualityPoints( n ));

    return 0;
}


int qualityPoints( int n )
{
    if( n >= 90 )
        return 4;
    else if( n >= 80 )
        return 3;
    else if( n >= 70 )
        return 2;
    else if( n >= 60 )
        return 1;
    else 
        return 0;
}

