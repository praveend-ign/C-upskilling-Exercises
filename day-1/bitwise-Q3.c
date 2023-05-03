#include <stdio.h>

void print_binary(unsigned char num)
{
    char bit_arr[32] = {0};
    int i;
    int leadzeros = 0;
    int skip_flag;

    i = 0;
    while (num > 0) {
       if (num & 1)
	       bit_arr[i] = 1;
       else
	      bit_arr[i] = 0;
       num = num >> 1;
       i++;
    }
    skip_flag = 1;
    for(i=7;i>=0;i--) {
	    leadzeros = bit_arr[i];
	    if(leadzeros == 0 && skip_flag == 1) { 
		    continue;
	    }
	    else {
		    skip_flag = 2;
	    }
	    if(skip_flag == 2)
	    	printf("%d", bit_arr[i]);
    }
    if(skip_flag == 1)
	    printf("0");
    printf("\n");
}

unsigned int power_of_two(unsigned int exponent)
{
    unsigned int result = 1;
    while (exponent != 0) {
        result *= 2;
        --exponent;
    }
    return result;
}

unsigned char bitarray_to_char(char *bitmask)
{
    int i;
    unsigned int charvalue = 0;
    unsigned int powvalue;

    for(i=0;i<8;i++) {
	powvalue = power_of_two(i);
    	charvalue += (*bitmask++)*(powvalue);
    }

    return (unsigned char)charvalue;
}

int main(void)
{
    unsigned char a;
    char bitmask[8] = {0};
    int i;
    unsigned char result;

    printf("Enter any number:\n");
    scanf("%d", &a);
    printf("binary representation of num =\n");
    print_binary(a);
    printf("enter 8-bit pattern mask:\n");
    for(i=0;i<8;i++)
    	scanf("%d", &bitmask[i]);

    printf("bitmask = ");
    for(i=0;i<8;i++)
	    printf("%d", bitmask[i]);
    printf("\n");

    result = bitarray_to_char(&bitmask[0]);
    printf("bitmask array to char = %x\n", result);
    result &= a;
    printf("binary rep of masked variable =\n");
    print_binary(result);
    printf("decimal value = %x\n", result);
    
    return 0;
}
