/*
 * Filename:    fig08_21.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        19/06/2017.
 * Description: Using strcmp and strncmp
 */

#include <stdio.h>
#include <string.h>

int main()
{       
    const char *s1 = "Happy New Year";
    const char *s2 = "Happy New Year";
    const char *s3 = "Happy Holidays";
       
    printf( "%s%s\n%s%s\n%s%s\n\n%s%2d\n%s%2d\n%s%2d\n\n",
            "s1 = ", s1, "s2 = ", s2, "s3 = ", s3,
            "strcmp(s1, s2) = ", strcmp(s1, s2),
            "strcmp(s1, s3) = ", strcmp(s1, s3),
            "strcmp(s3, s1) = ", strcmp(s3, s1) );
            
    printf ("%s%2d\n%s%2d\n%s%2d\n",
            "strncmp(s1, s2, 6) = ", strncmp(s1, s2, 6),
            "strncmp(s1, s3, 7) = ", strncmp(s1, s3, 7),
            "strncmp(s3, s1, 7) = ", strncmp(s3, s1, 7) );

    return 0;
}


