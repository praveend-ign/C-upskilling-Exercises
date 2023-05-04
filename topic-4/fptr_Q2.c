#include <stdio.h>

#define TRUE     1
#define FALSE    0

typedef int bool;

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_array(int arr[], int size, void (*sort_fn)(int *, int))
{
    (*sort_fn)(arr, size);
}

bool ascend_order(int a, int b)
{
    if(a > b)
	return TRUE;

    return FALSE;
}

bool descend_order(int a, int b)
{
    if (a < b)
	    return TRUE;
    return FALSE;
}

void ascend_sort(int *arr, int size)
{
    int i, j;
    for(i=0;i<(size-1);i++) {
	for(j=0;j<(size-i-1);j++) {
		if(ascend_order(arr[j], arr[j+1]))
			swap(&arr[j], &arr[j+1]);
	}
    }
}

void descend_sort(int *arr, int size)
{
    int i, j;
    for(i=0;i<(size-1);i++) {
	for(j=0;j<(size-i-1);j++) {
		if(descend_order(arr[j], arr[j+1]))
			swap(&arr[j], &arr[j+1]);
	}
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int arr[] = {23, 1, 58, 93, 14, 76};
    int size;

    size = sizeof(arr)/sizeof(arr[0]);
    printf("array sorted in ascending = \n");
    sort_array(arr, size, (void (*)(int *, int))ascend_sort);
    printArray(arr, size);
 
    printf("array sorted in descending = \n");
    sort_array(arr, size, (void (*)(int *, int))descend_sort);
    printArray(arr, size);
    return 0;
}
