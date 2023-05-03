#include <stdio.h>

union value_conv {
   unsigned int dec;
   float fltnum;
};

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
     float ghi;
     union value_conv jkl;

     printf("Enter any float number:\n");
     scanf("%f", &ghi);
     printf("float num = %f\n", ghi);
     jkl.fltnum = ghi;
     printf("float num in union = %f\n", ghi);
     jkl.dec = (unsigned int)ghi;
     printf(" integer value of float = %d\n", jkl.dec);
     print_binary(jkl.dec);
     return 0;
}
