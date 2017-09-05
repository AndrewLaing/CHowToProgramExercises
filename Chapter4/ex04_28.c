/*
 * Filename:    ex04_28.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        23/04/2017
 */

#include <stdio.h>


int main()
{
    float wages, hourlyRate, amountPerItem, weeklySales;
    int paycode=0, hoursWorked, itemsProduced;
    float commission = 0.057;
    
    while(paycode!=-1) {
        printf("Enter employee paycode or -1 to exit: ");
        scanf( "%d", &paycode );
        
        wages = 0.0;
        
        switch(paycode)
        {
            // Manager
            case 1:
                printf("Enter the employee's weekly wages: ");
                scanf( "%f", &wages );
                break;
            // Hourly Workers
            case 2:
                printf("Enter the worker's hourly rate: ");
                scanf( "%f", &hourlyRate );
                printf("Enter the number of hours worked: ");
                scanf( "%d", &hoursWorked );
                if(hoursWorked>40) {
                    wages = (hoursWorked - 40) * (hourlyRate * 1.5);
                    hoursWorked = 40;
                }
                wages += (hoursWorked * hourlyRate );
                break;
            // Commission Workers
            case 3:
                wages = 250.0;
                printf("Enter the worker's weekly sales total: ");
                scanf( "%f", &weeklySales );
                wages += (weeklySales * commission);
                break;
            // Pieceworkers
            case 4:
                printf("Enter the price paid per item made: ");
                scanf( "%f", &amountPerItem );
                printf("Enter the number of items made: ");
                scanf( "%d", &itemsProduced );
                wages = amountPerItem * itemsProduced;
                break;
            // Exit
            case -1:
                break;
            default:
                printf("\n<< Invalid employee code!!! >>\n");
                break;
        }
        
        if(paycode>=1 && paycode <=4)
            printf("The employees weekly wage is $%.2f\n\n", wages);
    }

    return 0;
}

