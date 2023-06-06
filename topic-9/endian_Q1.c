/*! program to find whether cpu
 *  is little endian or big endian
 */
#include <stdio.h>

union endian_test {
	unsigned char bytes[4];
	unsigned int word;
};

int main(void)
{
    union endian_test test_var;
    int temp;

    test_var.word = 0x010203F4;

    printf("value of first byte in array = %x\n",test_var.bytes[0]);
    if(test_var.bytes[0] == 0xF4) {
	printf("little endian\n");
    } else {
	printf("big endian\n");
    }

    temp = test_var.bytes[3];
    test_var.bytes[3] = test_var.bytes[0]; 
    test_var.bytes[0] = temp;

    temp = test_var.bytes[2];
    test_var.bytes[2] = test_var.bytes[1]; 
    test_var.bytes[1] = temp;

    printf("test_var.word = %x\n", test_var.word);

    return 0;
}
