/*
 * Filename:	ex09_10.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        17/07/2017.
 */

#include <stdio.h>

int main()
{	
    int a    = 12345;
    double b = 1.2345;



	printf("%.10d\n", a);
	printf("%.8d\n", a);
	printf("%.6d\n", a);
	printf("%.3d\n", a);
	printf("%11.1d\n", a);	
	
	
	printf("%.5f\n", b);	
	printf("%.4f\n", b);	
	printf("%.3f\n", b);	
	printf("%.2f\n", b);	
	printf("%.1f\n", b);	
	printf("%.0f\n", b);	

	return 0;
}



