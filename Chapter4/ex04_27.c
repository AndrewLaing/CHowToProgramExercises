/*
 * Filename:    ex04_27.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        22/04/2017
 */

#include <stdio.h>

int isValidRATriangle( float, float, float );


int main()
{
    int a, b, c;
    
    for(a=1; a<=500; a++)
    {
        for(b=1; b<=500; b++)
        {
            for(c=1; c<=500; c++)
            {
                if( isValidRATriangle(a, b, c) )
                    printf("A=%d B=%d C=%d\n", a, b, c);
            }   
        }
    }

    return 0;
}


int isValidRATriangle(float a, float b, float c)
{
    if(a>b)
    {
        if(a>c)
            return ( (c*c)+(b*b) == (a*a) );
        else
            return ( (a*a)+(b*b) == (c*c) );
    }
    else if(b>c)
        return ( (a*a)+(c*c) == (b*b) );
    else
        return ( (a*a)+(b*b) == (c*c) );
}

