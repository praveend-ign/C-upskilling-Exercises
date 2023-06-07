/*! program to demonstrate the effects
 *  of buffer overflow
 */
#include <stdio.h>

/*! function which copies source string
 *  to destination string
 */
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
    char array1[10] = "abcdefghijklmnop";
    char array2[5];
    int i;
    int len;

    printf("array1 = %s\n", array1);
    len = copy_string(array1, array2);
    printf("number of bytes copied = %d\n", len);
    printf("array2 = %s\n", array2);
/*! stack smashing detected error is displayed
 *  if array1 is declared as char *
 *  otherwise no overflow is detected for
 *  char array1[10] declaration but 10 bytes
 *  are only copied 
 */
    return 0;
}
