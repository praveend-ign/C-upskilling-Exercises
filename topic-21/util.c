#include "util.h"

void print_array(int *array, int size)
{
     int i;

     for(i=0;i<size;i++) {
        printf("\t%d\n", array[i]);
     }
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void revstr(char *str1)
{
    int i, len, temp;
    len = strlen(str1);

    for (i = 0; i < len/2; i++)
    {
        temp = str1[i];
        str1[i] = str1[len - i - 1];
        str1[len - i - 1] = temp;
    }
}
