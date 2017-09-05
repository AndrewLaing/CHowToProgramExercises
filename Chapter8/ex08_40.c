/*
 * Filename:    ex08_40.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        14/07/2017.
 * Todo:        Add more measurement types - e.g., weights etc
 *              Change the formatting to allow more decimal places for
 *              very small to large conversions (eg inches to miles)
 *              Improve the parser
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PERMITTEDLENGTH 80
#define MAXLENGTHS 8
#define MAXTEMPERATURES 3  

enum measureTypes {
    LENGTH=1, TEMPERATURE=2
};

enum lengthTypes {
    MILES, YARDS, FEET, INCHES, KILOMETRES, METRES, CENTIMETRES, MILLIMETRES
};

enum temperatureTypes {
    FAHRENHEIT, CENTIGRADE, KELVIN
};


void doMilesConversion( int toIndex, double number );
void doYardsConversion( int toIndex, double number );
void doFeetConversion( int toIndex, double number );
void doInchesConversion( int toIndex, double number );
void doKilometresConversion( int toIndex, double number );
void doMetresConversion( int toIndex, double number );
void doCentimetresConversion( int toIndex, double number );
void doMillimetresConversion( int toIndex, double number );
void printLengthResult( int fromIndex, int toIndex, double number );

void doFahrenheitConversion( int toIndex, double number );
void doCentigradeConversion( int toIndex, double number );
void doKelvinConversion( int toIndex, double number );
void printTemperatureResult( int fromIndex, int toIndex, double number );

void printResult(int measurementType, int fromIndex, int toIndex, double number);
int parseInput( const char *sentence );
int getLine( char [], int );
int isLength(char test[MAXLENGTHS]);
int isTemperature(char test[MAXTEMPERATURES]);
int isNumeric1( const char* s1);
double atof1(const char *str);
int strcmp1( const char* s1, const char *s2 );

/* Prototypes for conversion functions */

double milesToKm( double miles );
double milesToYards( double miles );
double milesToFeet( double miles );
double milesToInches( double miles );
double milesToMetres( double miles );
double milesToCentimetres( double miles );
double milesToMillimetres( double miles );

double yardsToInches( double yards );
double yardsToFeet( double yards );
double yardsToMiles( double yards );
double yardsToKilometres( double yards );
double yardsToMetres( double yards );
double yardsToCentimetres( double yards );
double yardsToMillimetres( double yards );

double feetToInches( double feet );
double feetToYards( double feet );
double feetToMiles( double feet );
double feetToKilometres( double feet );
double feetToMetres( double feet );
double feetToCentimetres( double feet );
double feetToMillimetres( double feet );

double inchesToFeet( double inches );
double inchesToYards( double inches );
double inchesToMiles( double inches );
double inchesToKilometres( double inches );
double inchesToMetres( double inches );
double inchesToCentimetres( double inches );
double inchesToMillimetres( double inches );

double kmToMiles( double km );
double kmToYards( double km );
double kmToFeet( double km );
double kmToInches( double km );
double kmToMetres( double km );
double kmToCentimetres( double km );
double kmToMillimetres( double km );

double metresToMiles( double metres );
double metresToYards( double metres );
double metresToFeet( double metres );
double metresToInches( double metres );
double metresToKm( double metres );
double metresToCentimetres( double metres );
double metresToMillimetres( double metres );

double centimetresToMiles( double centimetres );
double centimetresToYards( double centimetres );
double centimetresToFeet( double centimetres );
double centimetresToInches( double centimetres );
double centimetresToKm( double centimetres );
double centimetresToMetres( double centimetres );
double centimetresToMillimetres( double centimetres );

double millimetresToMiles( double millimetres );
double millimetresToYards( double millimetres );
double millimetresToFeet( double millimetres );
double millimetresToInches( double millimetres );
double millimetresToKm( double millimetres );
double millimetresToMetres( double millimetres );
double millimetresToCentimetres( double millimetres );

double fahrenheitToCentigrade( double fahrenheit );
double fahrenheitToKelvin( double fahrenheit );
double centigradeToFahrenheit( double centigrade );
double centigradeToKelvin( double centigrade );
double kelvinToCentigrade( double kelvin );
double kelvinToFahrenheit( double kelvin );



char lengths[MAXLENGTHS][12] = { "miles","yards","feet","inches",
                            "kilometres","metres","centimetres","millimetres"};
                 
char temperatures[MAXTEMPERATURES][11] = { "fahrenheit", "centigrade", "kelvin" };



int main()
{
    char sentence[PERMITTEDLENGTH];
    
    printf("Please enter the conversion you would like to make\n");
    printf(" ( Example - 'Convert 20 miles to kilometres' )\n> ");
    getLine(sentence, PERMITTEDLENGTH); 
    
    parseInput( sentence );


    return 0;
}

void doMilesConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case YARDS:
            printf("%0.2f %s\n" ,milesToYards(number), lengths[YARDS]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,milesToFeet(number), lengths[FEET]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,milesToFeet(number), lengths[INCHES]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,milesToKm(number), lengths[KILOMETRES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,milesToMetres(number), lengths[METRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,milesToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,milesToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doYardsConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,yardsToMiles(number), lengths[MILES]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,yardsToFeet(number), lengths[YARDS]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,yardsToInches(number), lengths[INCHES]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,yardsToKilometres(number), lengths[KILOMETRES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,yardsToMetres(number), lengths[METRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,yardsToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,yardsToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doFeetConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,feetToMiles(number), lengths[MILES]); 
            break;
        case YARDS:
            printf("%0.2f %s\n" ,feetToYards(number), lengths[YARDS]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,feetToInches(number), lengths[INCHES]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,feetToKilometres(number), lengths[KILOMETRES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,feetToMetres(number), lengths[METRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,feetToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,feetToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doInchesConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,inchesToMiles(number), lengths[INCHES]); 
            break;
        case YARDS:
            printf("%0.2f %s\n" ,inchesToYards(number), lengths[YARDS]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,inchesToFeet(number), lengths[FEET]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,inchesToKilometres(number), lengths[KILOMETRES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,inchesToMetres(number), lengths[METRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,inchesToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,inchesToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doKilometresConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,kmToMiles(number), lengths[MILES]); 
            break;
        case YARDS:
            printf("%0.2f %s\n" ,kmToYards(number), lengths[YARDS]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,kmToFeet(number), lengths[FEET]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,kmToInches(number), lengths[INCHES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,kmToMetres(number), lengths[METRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,kmToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,kmToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doMetresConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,metresToMiles(number), lengths[MILES]); 
            break;
        case YARDS:
            printf("%0.2f %s\n" ,metresToYards(number), lengths[YARDS]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,metresToFeet(number), lengths[FEET]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,metresToInches(number), lengths[INCHES]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,metresToKm(number), lengths[KILOMETRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,metresToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,metresToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doCentimetresConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,centimetresToMiles(number), lengths[MILES]); 
            break;
        case YARDS:
            printf("%0.2f %s\n" ,centimetresToYards(number), lengths[YARDS]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,centimetresToFeet(number), lengths[FEET]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,centimetresToInches(number), lengths[INCHES]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,centimetresToKm(number), lengths[KILOMETRES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,centimetresToMetres(number), lengths[METRES]); 
            break;
        case MILLIMETRES:
            printf("%0.2f %s\n" ,centimetresToMillimetres(number), lengths[MILLIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doMillimetresConversion( int toIndex, double number )
{
    switch(toIndex) 
    {
        case MILES:
            printf("%0.2f %s\n" ,millimetresToMiles(number), lengths[MILES]); 
            break;
        case YARDS:
            printf("%0.2f %s\n" ,millimetresToYards(number), lengths[YARDS]); 
            break;
        case FEET:
            printf("%0.2f %s\n" ,millimetresToFeet(number), lengths[FEET]); 
            break;
        case INCHES:
            printf("%0.2f %s\n" ,millimetresToInches(number), lengths[INCHES]); 
            break;
        case KILOMETRES:
            printf("%0.2f %s\n" ,millimetresToKm(number), lengths[KILOMETRES]); 
            break;
        case METRES:
            printf("%0.2f %s\n" ,millimetresToMetres(number), lengths[METRES]); 
            break;
        case CENTIMETRES:
            printf("%0.2f %s\n" ,millimetresToCentimetres(number), lengths[CENTIMETRES]); 
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }   
}


void printLengthResult( int fromIndex, int toIndex, double number )
{
    switch(fromIndex) 
    {
        case MILES:
            doMilesConversion(toIndex, number); 
            break;
        case YARDS:
            doYardsConversion(toIndex, number); 
            break;
        case FEET:
            doFeetConversion(toIndex, number);  
            break;
        case INCHES:
            doInchesConversion(toIndex, number);  
            break;
        case KILOMETRES:
            doKilometresConversion(toIndex, number);   
            break;
        case METRES:
            doMetresConversion(toIndex, number);  
            break;
        case CENTIMETRES:
            doCentimetresConversion(toIndex, number);  
            break;
        case MILLIMETRES:
            doMillimetresConversion(toIndex, number);  
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}


void doFahrenheitConversion( int toIndex, double number )
{
    switch(toIndex)
    {
        case CENTIGRADE:
            printf("%0.2f %s\n" ,fahrenheitToCentigrade(number), temperatures[CENTIGRADE] );
            break;
        case KELVIN:
            printf("%0.2f %s\n" ,fahrenheitToKelvin(number), temperatures[KELVIN] );  
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}

void doCentigradeConversion( int toIndex, double number )
{
    switch(toIndex)
    {
        case FAHRENHEIT:
            printf("%0.2f %s\n" ,centigradeToFahrenheit(number), temperatures[FAHRENHEIT] );
            break;
        case KELVIN:
            printf("%0.2f %s\n" ,centigradeToKelvin(number), temperatures[KELVIN] );  
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }   
}

void doKelvinConversion( int toIndex, double number )
{
    switch(toIndex)
    {
        case CENTIGRADE:
            printf("%0.2f %s\n" ,kelvinToCentigrade(number), temperatures[CENTIGRADE]);
            break;
        case FAHRENHEIT:
            printf("%0.2f %s\n" ,kelvinToFahrenheit(number), temperatures[FAHRENHEIT]);  
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}


void printTemperatureResult( int fromIndex, int toIndex, double number )
{
    switch(fromIndex) 
    {
        case FAHRENHEIT:
            doFahrenheitConversion( toIndex, number ); 
            break;
        case CENTIGRADE:
            doCentigradeConversion( toIndex, number );
            break;
        case KELVIN:
            doKelvinConversion( toIndex, number );  
            break;
        default:
            printf("Something went wrong with the input!\n");
            printf("Please contact your System Administrator.\n");
            break;
    }
}


void printResult(int measurementType, int fromIndex, int toIndex, double number)
{
    if( measurementType == LENGTH) 
        printLengthResult( fromIndex, toIndex, number );
    else if( measurementType == TEMPERATURE ) 
        printTemperatureResult( fromIndex, toIndex, number );
}



int parseInput(const char *sentence)
{
    char *tokenPtr;
    
    int measurementType = -1;
    int fromType = -1;
    int toType = -1;
    double number = 1.0;
    int test;
    
    
    tokenPtr = strtok( sentence, " .,;:?" );
    
    while( tokenPtr != NULL ) 
    {   
        if(fromType == -1)
        {
            test = isLength(tokenPtr);
            if(test!=-1) {
                measurementType = LENGTH;
                fromType = test;
            } 
            else {
                test = isTemperature(tokenPtr);
                if(test!=-1) {
                    measurementType = TEMPERATURE;
                    fromType = test;
                } 
            }
        }
        else if(toType == -1)
        {
            test = isLength(tokenPtr);
            if(test!=-1) {
                if(measurementType!=LENGTH) {
                    printf("Error - Invalid conversion!");
                    return -1;
                }
                toType = test;
            } 
            else {
                test = isTemperature(tokenPtr);
                if(test!=-1) {
                    if(measurementType!=TEMPERATURE) {
                        printf("Error - Invalid conversion!");
                        return -1;
                    }
                    toType = test;
                } 
            }
        }
        if( isNumeric1( tokenPtr )==1 ) {
            if(number == 1)
                number = atof1(tokenPtr);
        }
        
        
        //p = updateList( p, tokenPtr );
        tokenPtr = strtok( NULL, " .,;:?" );
    }   

    
    if(fromType!=-1 && toType!=-1)
        printResult( measurementType, fromType, toType, number);
    
    return 0;
}



/* Read a string into a character array and return the length of the array */
int getLine( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    /* Clear any overflow*/
    fflush(stdin);
    
    return i;   
}


int isLength(char test[MAXLENGTHS])
{
    int i;
    for(i=0; i<MAXLENGTHS; i++)
    {
        if(strcmp1(test, lengths[i])==0)
            return i;
    }
    return -1;
}


int isTemperature(char test[MAXTEMPERATURES])
{
    int i;
    for(i=0; i<MAXTEMPERATURES ; i++)
    {
        if(strcmp1(test, temperatures[i])==0)
            return i;
    }
    return -1;
}


/* If strings are equal returns 0, otherwise 1 */
int strcmp1( const char* s1, const char *s2 )
{
    size_t i=0;
    
    while(s2[i]!='\0') {
        if(tolower(s1[i]) != s2[i])
            return 1;
        i++;
    }

    return 0;   
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


double atof1(const char *str)
{
    double result;
    sscanf(str, "%lf", &result);
    
    return result;
}


double milesToKm( double miles )
{
    return miles/0.62137;
}

double milesToYards( double miles )
{
    return miles * 1760.0;
}

double milesToFeet( double miles )
{
    return miles * 5280.0;
}

double milesToInches( double miles )
{
    return miles * 63360.0;
}

double milesToMetres( double miles )
{
    return miles * 1609.34;
}

double milesToCentimetres( double miles )
{
    return miles * 160934;
}

double milesToMillimetres( double miles )
{
    return miles * 1609340;
}


double yardsToInches( double yards )
{
    return yards * 36.0;
}

double yardsToFeet( double yards )
{
    return yards * 3.0;
}

double yardsToMiles( double yards )
{
    return yards / 1760.0;
}

double yardsToKilometres( double yards )
{
    return yards * 0.0009144;
}

double yardsToMetres( double yards )
{
    return yards * 0.9144;
}

double yardsToCentimetres( double yards )
{
    return yards * 91.44;
}

double yardsToMillimetres( double yards )
{
    return yards * 914.4;
}

double feetToInches( double feet )
{
    return feet * 12.0;
}

double feetToYards( double feet )
{
    return feet/3.0;
}

double feetToMiles( double feet )
{
    return feet/5280.0;
}

double feetToKilometres( double feet )
{
    return feet*0.0003048;
}

double feetToMetres( double feet )
{
    return feet/3.2808;
}

double feetToCentimetres( double feet )
{
    return feet * 30.48;
}

double feetToMillimetres( double feet )
{
    return feet * 304.8;
}

double inchesToFeet( double inches )
{
    return inches/12.0;
}

double inchesToYards( double inches )
{
    return inches/36.0;
}

double inchesToMiles( double inches )
{
    return inches/63360.0;
}

double inchesToKilometres( double inches )
{
    return inches/0.039370;
}

double inchesToMetres( double inches )
{
    return inches/39.370;
}

double inchesToCentimetres( double inches )
{
    return inches*2.54;
}

double inchesToMillimetres( double inches )
{
    return inches*25.4; 
}


double kmToMiles( double km )
{
    return km * 0.62137;
}

double kmToYards( double km )
{
    return km * 1093.61;    
}

double kmToFeet( double km )
{
    return km * 3280.84;    
}

double kmToInches( double km )
{
    return km * 39370.1;    
};

double kmToMetres( double km )
{
    return km * 1000.0;
}

double kmToCentimetres( double km )
{
    return km * 100000.0;
}

double kmToMillimetres( double km )
{
    return km * 1000000.0;
}

double metresToMiles( double metres )
{
    return metres * 0.00062137;
}

double metresToYards( double metres )
{
    return metres * 1.09361;    
}

double metresToFeet( double metres )
{
    return metres * 3.2808; 
}

double metresToInches( double metres )
{
    return metres * 39.3696;    
}

double metresToKm( double metres )
{
    return metres / 1000.0;
}

double metresToCentimetres( double metres )
{
    return metres * 100.0;
}

double metresToMillimetres( double metres )
{
    return metres * 1000.0;
}

double centimetresToMiles( double centimetres )
{
    return centimetres* 0.0000062137;
}

double centimetresToYards( double centimetres )
{
    return centimetres * 0.0109361; 
}

double centimetresToFeet( double centimetres )
{
    return centimetres * 328.08;    
}

double centimetresToInches( double centimetres )
{
    return centimetres * 3936.96;   
}

double centimetresToKm( double centimetres )
{
    return centimetres / 100000.0;
}

double centimetresToMetres( double centimetres )
{
    return centimetres / 100.0;
}

double centimetresToMillimetres( double centimetres )
{
    return centimetres * 10.0;
}


double millimetresToMiles( double millimetres )
{
    return millimetres * 0.000000621371;
}

double millimetresToYards( double millimetres )
{
    return millimetres * 1.09361;   
}

double millimetresToFeet( double millimetres )
{
    return millimetres * 3280.8;    
}

double millimetresToInches( double millimetres )
{
    return millimetres * 39369.6;   
}

double millimetresToKm( double millimetres )
{
    return millimetres / 1000000.0;
}

double millimetresToMetres( double millimetres )
{
    return millimetres / 1000.0;
}

double millimetresToCentimetres( double millimetres )
{
    return millimetres / 10.0;
}


double fahrenheitToCentigrade( double fahrenheit )
{
    return (fahrenheit-32)/1.8;
}

double fahrenheitToKelvin( double fahrenheit )
{
    return ((fahrenheit-32)/1.8) + 273.15;
}

double centigradeToFahrenheit( double centigrade )
{
    return centigrade * 1.8000 + 32.00;
}

double centigradeToKelvin( double centigrade )
{
    return centigrade + 273.15;
}

double kelvinToCentigrade( double kelvin )
{
    return kelvin - 273.15;
}

double kelvinToFahrenheit( double kelvin )
{
    return (kelvin - 273.15) * 1.8000 + 32.00;
}


