/*
 * Filename:    ex14_06.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        29/10/2017
 * Description: Trapping signals
 * Re Window 10 signals
 
sig value   Description
SIGABRT     Abnormal termination
SIGFPE      Floating-point error
SIGILL      Illegal instruction
SIGINT      CTRL+C signal
SIGSEGV     Illegal storage access
SIGTERM     Termination request

SIGINT is not supported for any Win32 application. 
When a CTRL+C interrupt occurs, Win32 operating systems generate 
a new thread to specifically handle that interrupt. 
This can cause a single-thread application, such as one in UNIX, 
to become multithreaded and cause unexpected behavior.

 */
 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void signal_handler( int );

int main()
{   
//     signal( SIGABRT, signal_handler );
//     abort();
    
    // trying to use the abort function throws the following message
    // runs the signal_handler function then terminates the program abnormally;
    // This application has requested the Runtime to terminate it in an unusual way.
    // Please contact the application's support team for more information.
        
    signal( SIGABRT, signal_handler );
    raise(SIGABRT);
    
    signal( SIGINT, signal_handler );

    
    while( 1) {
        ;
    }
    
    return 0;
}


void signal_handler( int signalValue )
{
    int response;
    
    printf( "\n%s%d%s\n%s",
            "Interupt signal ( ", signalValue, " ) received.",
            "Do you wish to continue ( 1 = yes or 2 = no )? " );
            
    scanf("%d", &response );
    
    while (response != 1 && response != 2) {
        printf( "( 1 = yes or 2 = no )? " );
        scanf("%d", &response );
    }
    
    if( response == 1 )
        signal( SIGINT, signal_handler );   // reset the signal handler
    else
        exit( EXIT_SUCCESS );
}

 
