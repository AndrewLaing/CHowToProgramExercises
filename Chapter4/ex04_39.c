/*
 * Filename:    ex04_39.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/04/2017
 */
 
#include <stdio.h>


int main()
{
    int x;
    
    for(x = 1; x <= 10; x++)
    {
        if(x != 5)
            printf("%d ", x );
    }
     
    printf("\nUsed continue to skip printing the value 5\n");
    
    return 0;
}
