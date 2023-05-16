#include <stdio.h>

int copy_string(char *src_str, char *dest_str)
{
    int copied_len;

    copied_len = 0;

    while(*src_str != '\0') {
	*dest_str++ = *src_str++;
	copied_len++;
    }
    /*! copy NULL character also */
    *dest_str = *src_str;
    return copied_len;
}

int main(void)
{
    char array1[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'};
    char array2[5] = {0};
    int i;
    int len;

    printf("array1 = %s\n", array1);
    len = copy_string(array1, array2);
    printf("number of bytes copied = %d\n", len);
    printf("array2 = %s\n", array2);

    return 0;
}
