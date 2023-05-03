#include <stdio.h>

void print_binary(int num)
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
    for(i=31;i>=0;i--) {
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

int main(void)
{
    int number;
    int bitpos1, bitpos2;

    printf("Enter any 32-bit integer number\n");
    scanf("%d", &number);
    printf("binary representation of the number is \n");
    print_binary(number);
    printf("Enter any two bit positions between 0 and 31\n");
    scanf("%d", &bitpos1);
    scanf("%d", &bitpos2);

    number |= (1 << bitpos1);
    number |= (1 << bitpos2);
    printf("binary representation of the modified number is \n");
    print_binary(number);
    printf("Enter another two bit positions between 0 and 31\n");
    scanf("%d", &bitpos1);
    scanf("%d", &bitpos2);
    number &= ~(1 << bitpos1);
    number &= ~(1 << bitpos2);
    printf("binary representation of the final number is \n");
    print_binary(number);
    printf("final decimal number = %d\n", number);
    
    return 0;
}
