/*
 * Filename:    ex05_41.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        06/05/2017
 * Description: Recursive factorial function
 */

#include <stdio.h>
int DEBUG = 1;
int start = 1;

long factorial( long );

int main()
{
    int i;

    for(i=1; i<=10; i++)
    {
        start=1;
        printf("%2d! = %1d\n\n", i, factorial( i ));
    }

    return 0;
}

long factorial( long number)
{
    int rcParam;
    static int calls=0;
    
    if(start)
    {
        calls=0;
        printf("=== First call to function ===\n");
        start=0;
    }
    
    
    calls++;
    
    if(DEBUG) printf("Call #%d: Number = %d\n", calls, number);
        
    if( number <= 1)
        return 1;
    else {
        rcParam = number * factorial(number - 1);
        
        if(DEBUG) printf("Call #%d: Recursive call parameter = %d\n", calls, rcParam);
        
        return rcParam;     
    }    
}

