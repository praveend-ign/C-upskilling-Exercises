#include <stdio.h>

long power_fn(int base, int exp)
{
   long result;

    if(exp == 0) {
	return 1;
    }
    return (base * power_fn(base, exp-1));
}

int main(void)
{
    int a, b;
    long result;

    printf("Enter base and exponent:\n");
    scanf("%d", &a);
    scanf("%d", &b);
    result = power_fn(a, b);
    printf("base to the power of exponent = %ld\n", result);
    return 0;
}
