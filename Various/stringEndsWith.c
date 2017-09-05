#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int string_ends_with(const char *str, const char *suffix);

int main()
{
    char *filename =  "drolegna.csv";
    char *filename1 = "puberty.mp4";
    char *suffix = ".csv";
    
    if(string_ends_with(filename, suffix))
        printf("%s ends with %s\n", filename, suffix ); 
    else
        printf("%s does not end with %s\n", filename, suffix ); 
        
    if(string_ends_with(filename1, suffix))
        printf("%s ends with %s\n", filename1, suffix ); 
    else
        printf("%s does not end with %s\n", filename1, suffix ); 
    
    return 0;
}

int string_ends_with(const char *s, const char *suffix)
{
  int sLength = strlen(s);
  int suffixLength = strlen(suffix);

  return (sLength >= suffixLength) &&
         (strcmp(s + (sLength-suffixLength), suffix) == 0);
}
