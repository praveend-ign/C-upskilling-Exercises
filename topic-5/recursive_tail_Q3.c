#include <stdio.h>
#include <time.h>
#include <errno.h>

long factorial(int s)
{
    if(s==0)
	    return 1;
    return (s*factorial(s-1));
}

long factorial_tail(int s, int result)
{
    if(s==0)
	    return result;
    return factorial_tail(s-1, s*result);
}

int main(void)
{
    int num;
    long result;
    struct timespec ts1, ts2;
    long t_diff;

    printf("Enter a num:\n");
    scanf("%d", &num);

    if(clock_gettime(CLOCK_MONOTONIC_RAW, &ts1))
	    printf("clock_gettime returned error %d\n", errno);
    result = factorial(num);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);
    printf("factorial of %d = %ld\n", num, result);
    t_diff = ((ts2.tv_sec-ts1.tv_sec)*(1000*1000*1000) + (ts2.tv_nsec-ts1.tv_nsec));
    printf("time taken by factorial = %lu nsecs\n", t_diff);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts1);
    result = factorial_tail(num, 1);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts2);
    printf("tail recursive factorial of %d = %ld\n", num, result);
    t_diff = ((ts2.tv_sec-ts1.tv_sec)*(1000*1000*1000) + (ts2.tv_nsec-ts1.tv_nsec));
    printf("time taken by tail recursive factorial = %lu nsecs\n", t_diff);
    return 0;
}

