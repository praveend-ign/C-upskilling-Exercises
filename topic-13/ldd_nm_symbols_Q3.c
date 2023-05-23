/*! program to define local, global,
 *  constant variables
 *
 */
#include <stdio.h>

#define EVEN	1
#define ODD	2

#define NOT_PRIME	3
#define PRIME		4

int global_var;
static int stat_value;


/*! function to check whether an integer is
 * even or odd
 */
int check_even_odd(int num)
{
    if(num % 2 == 0)
	   return EVEN;
    else
	   return ODD; 
}

/*! function to check whether an integer is
 * a prime number or not
 */
int check_prime(int number)
{
    int i;

    if (number == 0 || number == 1)
    	return NOT_PRIME;

    for (i = 2; i <= number / 2; ++i) {
    /*! if n is divisible by i, then n is not prime
     */
    	if (number % i == 0) {
      		return NOT_PRIME;
    	}
    }
    return PRIME;
}

int main(void)
{
    int localvar;
    const int const_num = 780;
    int result;

    global_var = 123;
    stat_value = 456;

    result = check_prime(global_var);
    if(result == PRIME)
	    printf("123 is a prime number\n");
    else
	    printf("123 is not prime number\n");

    result = check_even_odd(stat_value);
    if(result == EVEN)
	    printf("456 is even\n");
    else
	    printf("456 is odd\n");
 
    localvar = (global_var + stat_value);

    result = check_even_odd(localvar);
    if(result == EVEN)
	    printf("579 is even\n");
    else
	    printf("579 is odd\n");
 
    result = check_prime(const_num);
    if(result == PRIME)
	    printf("780 is a prime number\n");
    else
	    printf("780 is not prime number\n");

    return 0;
}
