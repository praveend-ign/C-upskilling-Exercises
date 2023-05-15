#include <stdio.h>
#include "math_Q2.c"

int main(void)
{
    int m, n;
    int res;

    printf("Enter any two numbers:\n");
    scanf("%d", &m);
    scanf("%d", &n);
    res = divide(m, n);
    if(res == -ERANGE) {
	printf("result is overflow\n");
    } else {
	printf("result of division = %d\n", res);
    }
    res = power(m, n);
    if(res == -ERANGE) {
	printf("result is overflow\n");
    } else {
	printf("result of base power exponent = %d\n", res); 
    }
    return 0;
}
