#include <stdio.h>
#include <stdlib.h>

int gvar;
static int svar;

void *allocate_memory(int n)
{
    char *ptr;

    if(n <= 0)
	  return NULL; 
    ptr = malloc(n);
    if(ptr == NULL) {
	printf("unable to alloc memory\n");
	return NULL;
    }
    return ptr;
}

void print_address(void *ptr)
{
    printf("address of the ptr variable = %p\n", ptr);
}

int main(void)
{
    int lvar;
    char *ptr;

    print_address(&lvar);
    print_address(&gvar);
    print_address(&svar);
    ptr = allocate_memory(32);
    print_address(ptr);

    return 0;
}
