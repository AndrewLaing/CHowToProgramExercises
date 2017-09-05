/*
 * Filename:    ex08_29.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        30/06/2017.
 */

#include <stdio.h>

/* Using array subscripting */
int getchar1( void );
char *gets1( char * );
int putchar1( int );
int puts1( const char * );


int main()
{   

    printf("---- getchar1 ----\n");
    printf("Enter a character: ");
    char test = getchar1();
    printf("getchar1() returns %c\n\n",test);

    char test1[20];

    printf("---- gets1 ----\n");
    printf("Enter a string: ");
    printf("gets(test1) returns %s\n",gets1(test1));
    printf("test1 = %s\n\n",test1);
    
    char c = 'A';
    printf("---- putchar1 ----\n");
    printf(" <- putchar1('A') returns %d\n",putchar1(c) );
    if(putchar1(-1)==EOF)
        printf("putchar(-1) returns EOF\n");
    else
        printf("putchar(-1) does NOT return EOF\n");
    printf("\n"); 
    
    
    char *s = "Phenomenal";
    printf("---- puts1 ----\n");
    printf(" <- puts1(\"Phenomenal\") returns %d\n",puts1(s) );

    printf("\n");
    
    return 0;
}


int getchar1( void )
{
    char s[1]; 
    
    int c, i=0, maxLength=2;
    
    while( ( --maxLength > 0)  && ( (c=getc(stdin))!=EOF ) && ( c!='\n' ) )
        s[i++]=c;
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return s[0];    
}

char *gets1( char *s )
{
    int c, i=0;
    
    while(( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return s;
}

/* This version only allows ASCII printing characters and whitespace */
int putchar1( int c )
{
    if( !(c>=9 && c<=13) && !(c>=32 && c<=126) )
         return EOF;
         
    printf("%c",c);
    return c;
}

/* This version only allows ASCII printing characters and whitespace */
int puts1( const char *s )
{
    const char* copy = s;
    while(*s!='\0' && *s!=EOF) {
        if( !(*s>=9 && *s<=13) && !(*s>=32 && *s<=126) )
           return EOF;
        s++;
    }
        
    if(printf("%s\n",copy)==-1)
        return EOF;
    return 1;
}

