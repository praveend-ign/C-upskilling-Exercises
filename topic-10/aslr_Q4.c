#include <stdio.h>
#include <string.h>

/*! Address space layout randomization.
 * compile this code with -fno-stack-protector flag
 * and observe how secret() function could be executed
 * without actually calling it. By enabling address space
 * layout randomization, above flaw can be overcome
 */

void vulnerable(char *str)
{
    char local_array[10];

    strcpy(local_array, str);

    printf("address of printed string in vulnerable function = %p\n", local_array);
}

void secret(void)
{
    char secret_str[] = "ASLR demonstration";

    printf("%s\n", secret_str);
}

int main(int argc, char *argv[])
{
    if(argc < 2) {
	printf("enter any string as an argument\n");
	return -1;
    }
    /*! if the entered string is greater than 10 bytes,
     *  and compiled with -fno-stack-protector flag,
     *  then segmentation fault is occurred. if compiled
     *  without any flag, and entered string is > 10 bytes
     *  then stack smashing detected exception occurs
     */
    printf("entered string is %s\n", argv[1]);
    printf("vulnerable fn addr = %p\n", vulnerable);
    printf("secret fn addr = %p\n", secret);
    vulnerable(argv[1]);
    return 0;
}
