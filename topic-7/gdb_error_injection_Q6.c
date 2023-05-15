#include <stdio.h>

long factorial(int s)
{
    if(s==0)
	    return 1;
    return (s*factorial(s-1));
}

int main(void)
{
    int num;
    long result;

    printf("Enter a num:\n");
    scanf("%d", &num);

    result = factorial(num);
    printf("factorial of %d = %ld\n", num, result);
    printf("factorial of %d = %ld\n", num, factorial(num));

    return 0;
}
