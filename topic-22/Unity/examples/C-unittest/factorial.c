#include "factorial.h"

long long factorial(int n)
{
	long long result = 1;
	int i;

	if(n < 0) {
		return -1;
	}
	if((n==0) || (n==1)) {
		return 1;
	}
	for(i=2;i<=n;i++) {
		result *= i;
	}
	return result;
}
