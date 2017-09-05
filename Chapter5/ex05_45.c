/*
 * Filename:	ex05_45.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        07/05/2017
 */

#include <stdio.h>
#include <math.h>


double distance(double x1, double x2, double y1, double y2)
{
	return sqrt( pow((x2-x1), 2) + pow((y2-y1), 2) );
}


int main()
{
	double x1=1.0, y1=1.0;
	double x2=6.0, y2=6.0;
	
	printf("Distance between 1,1 and 6,6 = %.2f\n", distance(x1, x2, y1, y2));

	return 0;
}

