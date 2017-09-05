/*
 * Filename:	ex03_28.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/04/2017
 */

#include <stdio.h>

int main()
{
	/* Initialisation phase */
	int passes=0, failures=0, student=1, result;
	
	/* Processing phase */
	while( student <= 10 ) 
	{
		printf( "Enter result ( 1=pass, 2=fail ): " );
		scanf( "%d", &result );

        if(result == 1)
        {
        	passes = passes + 1;
        	student = student + 1;
		}
        else if(result == 2)
        {
        	failures = failures + 1;
        	student = student + 1;
		}
        else 
            printf("<< Invalid input. >>\n");
	}

    /* Termination phase */
    
    printf( "Passed %d\n", passes );
    printf( "Failed %d\n", failures );
    
    if( passes > 8 )
        printf( "Raise tuition\n" );

	return 0;
}

