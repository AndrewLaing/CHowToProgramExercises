/*
 * Filename:    ex14_09.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/10/2017
 * Description: use goto
 */
 
#include <stdio.h>


int main( int argc, char *argv[] )
{
    int line = 0;
    int count = 0;
    int width = 5;
    
    start:
        if( line == 0 )
            goto drawTopLine;
        else if( line < width-1 )
            goto drawMiddleLine;
        else
            goto drawBottomLine;
    
    drawTopLine:
        if(count < width )
            goto star;
        else
            goto newline;
            
    drawMiddleLine:
        if(count < width ) {                
            if(count == 0 || count == width-1)
                goto star;
            else
                goto space;
        }
        else
            goto newline; 
            
    drawBottomLine:
        if(line == width)
            goto end;
        if(count < width )
            goto star;
        else
            goto newline;  
            
    star:
        printf( "*" );
        count++;
        goto start;
        
    space:
        printf( " " );
        count++;
        goto start;
        
    newline:
        printf( "\n" );
        line++;
        count = 0;
        goto start;
        
    end:        
        return 0;
}



