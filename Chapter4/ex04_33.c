/*
 * Filename:    ex04_33.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        24/04/2017
 */

#include <stdio.h>


int main()
{   
    int i, current;
    
    for(i=1; i<=100; i++)
    {
        current=i;
        
        if(current==100) {
            printf("C");
            current=0;
        }
        if(current>=50) {
            printf("L");
            current-=50;
        }
        while(current>=10) {
            printf("X");
            current-=10;
        }
        if(current>=5) {
            if(current%10==9) {
                printf("IX");
                current-=9;
            }
            else {
                printf("V");
                current-=5;
            }   
        }
        while(current>0) 
        {
            if(current%10==4) {
                printf("IV");
                current-=4;
            }
            else {
                printf("I");
                current-=1;
            }
            
        }
        printf("\n");
    }

    return 0;
}

