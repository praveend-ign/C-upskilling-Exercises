#include <stdio.h>

union endian_test {
	char bytes[4];
	unsigned int word;
};

int main(void)
{
    union endian_test test_var;

    test_var.word = 0x01020304;

    printf("value of first byte in array = %x\n",test_var.bytes[0]);

    return 0;
}
