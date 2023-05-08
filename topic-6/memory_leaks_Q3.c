#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *create_array(int n)
{
    int *arr_ptr;

    arr_ptr = (int *)malloc(sizeof(int)*n);
    if(arr_ptr == NULL) {
	printf("unable to alloc memory\n");
	return NULL;
    }
    return arr_ptr;
}

void fill_array(int *array, int size)
{
    int data;
    int i;

    for(i=0;i<size;i++) {
    	data = rand();
    	array[i] = data;
    }
}

void print_array(int *array, int size)
{
     int i;

     for(i=0;i<size;i++) {
	printf("\t%d\n", array[i]);
     }
}

void memory_leaks(int *array, int size)
{
     /* accessing memory out of bounds */
     fill_array(array, size+8);
     print_array(array, size+32);
     /* accessing invalid pointer */
     print_array(array-0x7F0, size);
}

int main(void)
{
    int *array_ints;
    int value;

    srand(time(NULL));
    printf("Enter the array size:\n");
    scanf("%d", &value);

    array_ints = create_array(value); 
    fill_array(array_ints, value);
    print_array(array_ints, value);

    memory_leaks(array_ints, value);
    free(array_ints);
    /* dangling pointer */
    free(array_ints);
    return 0;
}
