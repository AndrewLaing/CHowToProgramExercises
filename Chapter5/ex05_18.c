/*
 * Filename:    ex05_18.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        27/04/2017
 */

#include <stdio.h>


int isEven( int );


int main()
{
    int i;
    int num;
    
    for(i=0; i<3; i++)
    {
        printf("Enter a number: ");
        scanf("%d", &num);
        
        if (isEven(num) )
            printf("%d is even\n\n", num); 
        else
            printf("%d is odd\n\n", num);       
    }

    return 0;
}


int isEven(int n)
{
    return (n%2==0); 
}

