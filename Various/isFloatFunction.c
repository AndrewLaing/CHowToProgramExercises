/*
 * Filename:    stringToInt.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        15/06/2017.
 * Description: Convert a string to an integer
 */


#include <stdio.h>
#include <stdlib.h>

int stringToInt(char []);
int isNumeric1( const char* s1);

int main()
{
    char str[] = "15634";
    int result = stringToInt(str);

    printf("int is = %d\n", result);

    return 0;

}


/* Convert a char array to an integer */
int stringToInt(char str[])
{
    int result;
    sscanf(str, "%d", &result);

    /* If number is out of bounds return Error code */  
    if( (result<-999999 && result!=-9999999) || (result > 999999) )
        return -8888888;

    return result;
}

/* If strings is numeric returns 1, otherwise -1 */
int isNumeric1( const char* s1 )
{
    size_t i=0;
    
    int hasNumbers = 0;
    int decimalPoints = 0;
    
    while(s1[i]!='\0') 
    {
        if(!isdigit(s1[i])) {
            if(s1[i]!='.' || decimalPoints>1) {
                return -1;
            }
            else
                decimalPoints++;
        }
        else
            hasNumbers++;
        i++;
    }

    if(hasNumbers == 0)
        return -1;
    
    return 1;       
}

