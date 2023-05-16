#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_string(char *str)
{
    printf("%s\n", str);
}

int main(void)
{
    char *str1 = NULL;
    char *str2 = "Hello";
    char *str3;

    print_string(str2);
   /*!  what happens if NULL pointer is accessed */
    /*! print_string(str1); */

    str3 = malloc(16);
    if(str3 == NULL) {
	printf("unable to alloc memory\n");
        return -1;
    }
    strcpy(str3, "world");
    print_string(str3);

    /*! now free the pointer, which makes it dangling pointer when used */
    free(str3);

    print_string(str3);
    printf("do we reach here\n");
    return 0;
}
