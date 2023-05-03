#include <stdio.h>

int main(void)
{
    unsigned char abc;
    unsigned short int ascii;

    printf("Enter any character:\n");
    scanf("%c", &abc);
    printf("%x\n", (unsigned short int)abc);
    ascii = (unsigned short int)abc;
    if(ascii >= 97 && ascii <= 122) {
	printf("%x", ((int)abc - 32));
    }
    printf("\n");
    return 0;
}
