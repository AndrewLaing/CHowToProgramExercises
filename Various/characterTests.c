/*
 * Filename:    ex08_26.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        26/06/2017.
 */

#include <stdio.h>

#define MAXLEN 4
 
int isdigit( int );
int isalpha( int );
int isalnum( int );
int isxdigit( int );
int islower( int );
int isupper( int );
int isspace( int );
int iscntrl( int );
int ispunct( int );
int isprint( int );
int isgraph( int );



int main()
{
    char test1 = '6';
    char test2 = 's';
    char test3 = 'D';

    char test5 = ' ';
    char test6 = '!';
    char test7 = '\n';
    
    /* Test isdigit */
    if(isdigit(test1)==1)
        printf("'%c' is a digit\n", test1);
    else
        printf("'%c' is NOT a digit\n", test1);
    
    if(isdigit(test2)==1)
        printf("'%c' is a digit\n", test2);
    else
        printf("'%c' is NOT a digit\n", test2);
        
    /* Test isalpha */
    if(isalpha(test1)==1)
        printf("'%c' is an alphabetic character\n", test1);
    else
        printf("'%c' is NOT an alphabetic character\n", test1);
    
    if(isalpha(test2)==1)
        printf("'%c' is an alphabetic character\n", test2);
    else
        printf("'%c' is NOT an alphabetic character\n", test2);
        
    /* Test isalnum */
    if(isalnum(test1)==1)
        printf("'%c' is an alphanumeric character\n", test1);
    else
        printf("'%c' is NOT an alphanumeric character\n", test1);
    
    if(isalnum(test2)==1)
        printf("'%c' is an alphanumeric character\n", test2);
    else
        printf("'%c' is NOT an alphanumeric character\n", test2);
 
    /* Test isxdigit */
    if(isxdigit(test1)==1)
        printf("'%c' is a hex digit\n", test1);
    else
        printf("'%c' is NOT a hex digit\n", test1);
    
    if(isxdigit(test2)==1)
        printf("'%c' is a hex digit\n", test2);
    else
        printf("'%c' is NOT a hex digit\n", test2);
         
    /* Test islower */
    if(islower(test2)==1)
        printf("'%c' is lower case\n", test2);
    else
        printf("'%c' is NOT lower case\n", test2);
    
    if(islower(test3)==1)
        printf("'%c' is lower case\n", test3);
    else
        printf("'%c' is NOT lower case\n", test3);
         
    /* Test isupper */
    if(isupper(test2)==1)
        printf("'%c' is upper case\n", test2);
    else
        printf("'%c' is NOT upper case\n", test2);
    
    if(isupper(test3)==1)
        printf("'%c' is upper case\n", test3);
    else
        printf("'%c' is NOT upper case\n", test3);  
        
    /* Test isspace */
    if(isspace(test5)==1)
        printf("'%c' is a space character\n", test5);
    else
        printf("'%c' is NOT a space character\n", test5);
    
    if(isspace(test6)==1)
        printf("'%c' is a space character\n", test6);
    else
        printf("'%c' is NOT a space character\n", test6);
        
    /* Test iscntrl */
    if(iscntrl(test6)==1)
        printf("'%c' is a control character\n", test6);
    else
        printf("'%c' is NOT a control character\n", test6);
    
    if(iscntrl(test7)==1)
        printf("'NEWLINE' is a control character\n");
    else
        printf("'NEWLINE' is NOT a control character\n");
        
    /* Test iscntrl */
    if(ispunct(test5)==1)
        printf("'%c' is a punctuation character\n", test5);
    else
        printf("'%c' is NOT a punctuation character\n", test5);
    
    if(ispunct(test6)==1)
        printf("'%c' is a punctuation character\n", test6);
    else
        printf("'%c' is NOT a punctuation character\n", test6);

    /* Test isprint */
    if(isprint(test5)==1)
        printf("'%c' is a printing character\n", test5);
    else
        printf("'%c' is NOT a printing character\n", test5);
    
    if(isprint(test6)==1)
        printf("'%c' is a printing character\n", test6);
    else
        printf("'%c' is NOT a printing character\n", test6);

    /* Test isgraph */
    if(isgraph(test5)==1)
        printf("'%c' is a printing character except space\n", test5);
    else
        printf("'%c' is NOT a printing character except space\n", test5);
    
    if(isgraph(test6)==1)
        printf("'%c' is a printing character except space\n", test6);
    else
        printf("'%c' is NOT a printing character except space\n", test6);

    return 0;
}



int isdigit( int c )
{
    if(c<48 || c >57)
        return 0;
    return 1;
}


int isalpha( int c )
{
    if( (c>=65 && c<=90) || (c>=97 && c<=122) )
        return 1;
    return 0;
}


int isalnum( int c )
{
    if( (c>=48 && c <=57) || (c>=65 && c<=90) || (c>=97 && c<=122) )
        return 1;
    return 0;
}


int isxdigit( int c )
{
    if( (c>=48 && c <=57) || (c>=65 && c<=70) || (c>=97 && c<=102) )
        return 1;
    return 0;
}


int islower( int c )
{
    if( c>=97 && c<=122 )
        return 1;
    return 0;
}


int isupper( int c )
{
    if( c>=65 && c<=90 )
        return 1;
    return 0;
}


int isspace( int c )
{
    if( (c>=9 && c<=13) || c==32 )
        return 1;
    return 0;
}


int iscntrl( int c )
{
    if( c>=0 && c<=31 )
        return 1;
    return 0;
}


int ispunct( int c )
{
    if( iscntrl( c )==1 )
        return 0;
    else if( isalnum( c )==1 )
        return 0;
    else if( isspace( c )==1 )
        return 0;
    return 1;
}


int isprint( int c )
{
    if( c>=32 && c<=126 )
        return 1;
    return 0;
}


int isgraph( int c )
{
    if( c>=33 && c<=126 )
        return 1;
    return 0;
}

