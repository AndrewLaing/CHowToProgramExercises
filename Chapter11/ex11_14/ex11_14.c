/*
 * Filename:    ex11_14.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        29/07/2017.
 * Todo:        Implement a binary search method using random access on the
 *              dictionary files, or load the contents into an array because
 *              the time taken to search is looooonnnnnnggggggggggggg
 *              Maybe add a flag which allows the user to stick to the
 *              7 letter wordlist (using args)
 */
 
#include <stdio.h>
#define INPUTLENGTH 9 /* max user input length */
#define MAXDIGITS 7   /* max digits in phone number */

int extractNumbers(char *, int [MAXDIGITS]);
void produceWordlist( FILE *, char * );
int isvaliddigit( int c );
int getLine( char [], int );
int strlen2( const char * );
int strcmp2( const char *, const char * );
int isInDictionary( char * );
int isInDictionary1( char * );

char letters[][3] = {"","","ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};


int main()
{   
    char phoneNumber[INPUTLENGTH];
    
    FILE *ofPtr;
 
    if ( ( ofPtr = fopen( "genwordList.txt", "w" ) ) == NULL )
    {
        printf("Error - unable to create file \"wordList.txt\"\n");
        return -1;
    }
    

    printf("Enter phone number: ");
    int numLen = getLine( phoneNumber, INPUTLENGTH );
    
    if( numLen < MAXDIGITS ) {
        printf("Error - Invalid phone number");
    }
    else
    {
        produceWordlist( ofPtr, phoneNumber );
    }

    fclose( ofPtr );
    
    return 0;
}


int extractNumbers(char *phoneNum, int nums[MAXDIGITS])
{
    int totalExtracted = 0;
    int i, phoneNumLen;
    char c;
    
    phoneNumLen = strlen2(phoneNum); 
    
    for( i=0; i<phoneNumLen; i++ )
    {
        c = phoneNum[i];
        if( isvaliddigit(c) ) {
            if(totalExtracted > MAXDIGITS ) /* To prevent an overflow */
                return -1;
            nums[totalExtracted++] = c-48; /* Convert char to number  */
        }
    }
    
    return totalExtracted;
}


/* Rewrite this to take a char* representing a phone number
 * split the phone number into 7 digits */
void produceWordlist(  FILE *ofPtr, char *phoneNum )
{
    int nums[MAXDIGITS];
    char temp[ 50 ];
    int totalNums = extractNumbers( phoneNum, nums );
    if(totalNums != 7) {
        printf("Error - Invalid phone number");
        return;
    }

    int i,j,k,l,m,n,o;
    
    for(i=0; i<3; i++)      
     for(j=0; j<3; j++) 
      for(k=0; k<3; k++)    
       for(l=0; l<3; l++)   
        for(m=0; m<3; m++)  
         for(n=0; n<3; n++) 
          for(o=0; o<3; o++) {
              sprintf( temp, "%c%c%c%c%c%c%c", letters[ nums[0] ][i], 
                          letters[ nums[1] ][j], letters[ nums[2] ][k], 
                          letters[ nums[3] ][l], letters[ nums[4] ][m], 
                          letters[ nums[5] ][n], letters[ nums[6] ][o]);  

              if(isInDictionary(temp)==0) {
                  printf("adding  %s\n", temp);
                  fprintf( ofPtr, "%s\n", temp); 
              }     
              else if(isInDictionary1(temp)==0) {
                  printf("adding  %s\n", temp);
                  fprintf( ofPtr, "%s\n", temp); 
              }  
          }
}


/* Only the numbers 2-9 are allowed in this program */
int isvaliddigit( int c )
{
    if(c<50 || c >57)
        return 0;
    return 1;
}


/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    if(c=='\n')
        s[i++]=c;
    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


/* Using pointer arithmetic */
int strlen2( const char* s )
{
    int i=0;
    
    while(*s++!='\0')
        i++;

    return i;
}


int strcmp2( const char *s1, const char *s2 )
{      
    while(*s2!='\0') {
        if(*s1<*s2)
            return -1;
        else if(*s1>*s2)
            return 1;
        s1++;
        s2++;           
    }

    return 0;   
}


int isInDictionary(char *query)
{
    char line  [ 50 ]; /* or other suitable maximum line size */

    int res;
    FILE *searchFPtr = fopen("7LetterWordlist.txt", "r");

    if( searchFPtr == NULL )
        printf( "Search file could not be opened.\n" );
    else 
    {
        while ( fgets ( line, sizeof line, searchFPtr ) != NULL )
        {
            res = strcmp2(  line, query );
            if(res==0) {
                printf("found %s\n", query );
                fclose( searchFPtr );
                return 0;
            }
            else if (res>0) {
                fclose( searchFPtr );
                return 1;
            }   
        }       
    }

    return 1;
}


int isInDictionary1(char *query)
{
    char line  [ 50 ]; /* or other suitable maximum line size */

    int res;
    FILE *searchFPtr = fopen("3plus4Wordlist.txt", "r");

    if( searchFPtr == NULL )
        printf( "Search file could not be opened.\n" );
    else 
    {
        while ( fgets ( line, sizeof line, searchFPtr ) != NULL )
        {
            res = strcmp2(  line, query );
            if(res==0) {
                printf("found %s\n", query );
                fclose( searchFPtr );
                return 0;
            }
            else if (res>0) {
                fclose( searchFPtr );
                return 1;
            }   
        }       
    }

    return 1;
}

