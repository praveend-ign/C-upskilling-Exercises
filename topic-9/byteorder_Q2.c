/*! program to convert little endian 
 *  to bigendian or vice-versa
 */
#include <stdio.h>

/*! function to reverse byte ordering */
unsigned int swap_bytes(unsigned int word)
{
    unsigned int result;

    result = (word << 24) | ((word & 0xFF00) << 8) | ((word & 0xFF0000) >> 8) | ((word & 0xFF000000) >> 24);

    return result;
}

int main(void)
{
    unsigned int hex_num;

    printf("Enter any hexadecimal integer:\n");
    scanf("%x", &hex_num);

    hex_num = swap_bytes(hex_num);
    printf("reversed bytes = %x\n", hex_num);
    return 0;
}
