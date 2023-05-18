/*! program to demostrate the usage of stack and
 *  heap segments in storing local variables and 
 *  assigning addresses to pointer variables
 */
#include <stdio.h>
#include <stdlib.h>

#define ALLOC_SIZE_USER1	24
#define ALLOC_SIZE_USER2	64
#define ARRAY_SIZE		32

/*! function for allocating some bytes of memory */
void *allocate_memory(int alloc_size)
{
    char *ptr;

    ptr = malloc(alloc_size);
    if(ptr == NULL)
	    printf("unable to alloc memory\n");

    return ptr;
}

/*! function to print starting address of pointer
 *  variable allocated from heap memory
 */
void print_address(void *ptr)
{
    printf("pointer address = %p\n", ptr);
}

void print_local(void)
{
     char ch_variable;
     int num, var;

     printf("addr of ch_variable = %p\n", &ch_variable);
     printf("addr of num = %p\n", &num);
     printf("addr of var = %p\n", &var);
}

int main(void)
{
    int *integer_ptr;
    char *bytes_ptr;
    int main_local;
    char local_array[ARRAY_SIZE];

    integer_ptr = allocate_memory(sizeof(int)*ALLOC_SIZE_USER1);
    bytes_ptr = allocate_memory(ALLOC_SIZE_USER2);
    print_address(integer_ptr);
    print_address(bytes_ptr);
    print_local();
    free(integer_ptr);
    free(bytes_ptr);

    printf("addr of main_local = %p\n", &main_local);
    printf("location of array variable = %p\n", local_array);
    return 0;
}
