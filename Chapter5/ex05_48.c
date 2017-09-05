/*
 * Filename:    ex05_48.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        07/05/2017
 */

#include <stdio.h>



int mystery( int, int );

int main()
{
    int x, y;
    printf("Enter two integers: ");
    scanf("%d%d", &x, &y);
    printf("The result is %d\n", mystery(x,y) );

    return 0;
}

/* mystery multiplies x by y */
int mystery( int x, int y )
{
    if( y == 1 )
        return x;
    else {
        if(y>1)
            return x + mystery(x, y-1); 
        else {
            y = abs(y);
            return -(x + mystery(x, y-1)); 
        }
    }    
}

