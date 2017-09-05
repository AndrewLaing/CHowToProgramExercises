/*
 * Filename:    ex05_23.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        01/05/2017
 */

#include <stdio.h>


int secondsSinceTwelve( int, int, int );


int main()
{
    int hours, minutes, seconds;
    int result;
    
    printf("Enter hours: ");
    scanf("%d", &hours);
    
    if(hours < 0 || hours > 23) {
        printf("Invalid value for hours entered!\n");
        return -1;
    }
    
    printf("Enter minutes: ");
    scanf("%d", &minutes);
        
    if(minutes < 0 || minutes > 59) {
        printf("Invalid value for minutes entered!\n");
        return -1;
    }
    
    printf("Enter seconds: ");
    scanf("%d", &seconds);
        
    if(seconds < 0 || seconds > 59) {
        printf("Invalid value for seconds entered!\n");
        return -1;
    }
    
    result = secondsSinceTwelve(hours, minutes, seconds);
    
    printf("It has been %d seconds since 12 O'clock.\n", result);   
    
    return 0;
}


int secondsSinceTwelve( int hours, int minutes, int seconds )
{
    if(hours>=12)
        hours -= 12;
    
    minutes += (hours*60);
    seconds += (minutes*60);
    
    return seconds;
}

