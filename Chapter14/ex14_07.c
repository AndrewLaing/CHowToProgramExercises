/*
 * Filename:    ex14_07.c
 * Author:      Andrew Laing
 * Email:       parisianconnections@gmail.com
 * Date:        31/10/2017
 * Description: realloc example
 */
 
#include <stdio.h>      /* printf, scanf, puts */
#include <stdlib.h>     /* calloc, realloc, free, exit, NULL */

int main ()
{
    int arraySize, n;
    int *dataPtr; /* Create an int pointer to hold the array pointer */
    int *resizedArray = NULL;
    
    printf ("Enter size of array: ");
    scanf ("%d",&arraySize);
    
    /* Dynamically allocate space for the array and cast the returned
     * void pointer to the memory from calloc into the pData pointer */
    dataPtr = (int*) calloc (arraySize, sizeof(int));
    
    /* If calloc could not assign the space for the array exit */
    if (dataPtr==NULL) 
        exit (1);
    
    for (n=0; n<arraySize; n++)
    {
        printf ("Enter number #%d: ",n+1);
        scanf ("%d",&dataPtr[n]);
    }
    
    printf ("Original Array Contents: \n");
    
    for (n=0; n<arraySize; n++) 
        printf("%d ",dataPtr[n]);
    printf("\n");
    
    /* Resize the space allocated to the dataPtr array */
    resizedArray = (int*) realloc (dataPtr, ( arraySize/2 ) * sizeof(int));
    
    if (dataPtr!=NULL) 
    {
        dataPtr=resizedArray;
        resizedArray=NULL;
    }
    else 
    {
        free(dataPtr);
        puts("Error reallocating memory");
        exit(1);
    }
    
    printf ("Resized Array Contents: \n");
    
    for (n=0; n<(arraySize/2); n++) 
        printf("%d ",dataPtr[n]);
    printf("\n");
    
    
    /* Always free dynamically allocated memory to avoid memory leaks */
    free (dataPtr);

    return 0;
}

