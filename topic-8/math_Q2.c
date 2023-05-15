#include <limits.h>
#include <errno.h>

int divide(int a, int b)
{
    int result;

    if(b == 0) {
	printf("division by zero not supported\n");
	return -ERANGE;
    }
    result = a/b;
    return result;
}

int power(int base, int exp)
{
/* to check the maximum integer range, use long type */
    long result = 1;

    while (exp != 0) {
/* base gets divided for negative exponent */
	if(exp < 0) {
		result /= base;
		++exp;
	} else {	
		result *= base;
		--exp;
	}
	if(result > INT_MAX) {
		return -ERANGE;
    	}
    }
/* typecast to integer result */
    return (int)result;
}
