/*! program to demonstrate the 
 *  effects of memory leaks and
 *  memory corruption
 */
#include <stdio.h>
#include <stdlib.h>

/*! function to allocate an
 *  array with the given size
 *  of the array
 */
void *create_array(int size)
{
    int *array_ptr;

    array_ptr = (int *)malloc(size*sizeof(int));
    if(array_ptr == NULL) {
	    printf("unable to alloc memory\n");
	    return NULL;
    }
    return array_ptr;
}

/*! initialize the array elements with
 *  with some values
 */
void fill_array(int *ptr, int array_len)
{
    int i;

    for(i=0;i<array_len;i++) {
	ptr[i] = i*array_len;
    }
}

/*! print the array elements of an
 *  array
 */
void print_array(int *ptr, int array_size)
{
    int i;

    printf("array values =\n");
    for(i=0;i<array_size;i++) {
	printf("\t%d", ptr[i]);
    }
    printf("\n");
}

int main(void)
{
    int *array_ptr;
    int size;

    printf("Enter array size:\n");
    scanf("%d", &size);
    array_ptr = create_array(size);
    fill_array(array_ptr, size);
    print_array(array_ptr, size);

    /*! allocate array with different sizes */
    size = 2*size;
    array_ptr = create_array(size);
    fill_array(array_ptr, size);
    print_array(array_ptr, size);

    size = 3*size;
    array_ptr = create_array(size);
    fill_array(array_ptr, size);
    print_array(array_ptr, size);

    size = 4*size;
    array_ptr = create_array(size);
    fill_array(array_ptr, size);
    print_array(array_ptr, size);

/*! gdb command := x/200b ptr-20 
 *  prints the heap memory address of ptr
 *  with difference of 20 bytes before and
 *  after the ptr address 
 */    

    return 0;
}
