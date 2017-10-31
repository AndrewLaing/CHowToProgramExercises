/*
 * Filename:    ex14_02.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        29/10/2017
 * Description: Variable length arg list 
 */
 
#include <stdio.h>
#include <stdarg.h>

int product(int i, ... );

int main()
{
    int w = 37, x=22, y=1, z=10;
    
    printf("%s%d\n%s%d\n%s%d\n%s%d\n\n",
           "w = ", w,"x = ", x,"y = ", y,"z = ", z);
    printf("%s%d\n%s%d\n%s%d\n",
           "The product of w and x is ", product(2,w,x),
           "The product of w, x and y is ", product(3,w,x,y),
           "The product of w, x, y and z is ", product(4,w,x,y,z) );
           
    return 0;
}


int product(int i, ... )
{
    int total;
    int j;
    
    va_list ap;
    
    /* Let total = the first number */
    va_start(ap, i);
    total = va_arg(ap, int);
    
    for(j=2; j<=i; j++)
        total *= va_arg(ap, int);
    
    va_end(ap);
    
    return total;
}
