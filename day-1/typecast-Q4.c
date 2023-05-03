#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *ptr;
    int *iptr;
    int j, k, l, m;

    ptr = (char *)malloc(16);
    if(ptr == NULL) {
	printf("unable to alloc mem\n");
	return -1;
    }

    j = 12;
    k = 34;
    l = 56;
    m = 78;

    iptr = (int *)ptr;

    *iptr = j;
    iptr++;
    *iptr = k;
    iptr++;
    *iptr = l;
    iptr++;
    *iptr = m;

    iptr = (int *)ptr;

    printf("start addr of iptr or ptr = %p\n", iptr);
    printf("second int addr and first value = %p %d\n", iptr, *iptr++);
    printf("third int addr and second value = %p %d\n", iptr, *iptr++);
    printf("fourth int addr and third value = %p %d\n", iptr, *iptr++);
    printf("fourth int value = %d\n", *iptr);

    free(ptr);
    return 0;
}
