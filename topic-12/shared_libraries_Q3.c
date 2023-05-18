/*! program to use the shared libraries
 * and understand when the shared libraries
 * are loaded into the memory.
 * compile this program with -lm flag
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    double num;
    double result;
    double base, expo;

    printf("Enter any number for sqrt:\n");
    scanf("%lf", &num);

    result = sqrt(num);
    printf("sqrt of %lf = %lf\n", num, result);

    printf("Enter two numbers for base power exponent:\n");
    scanf("%lf", &base);
    scanf("%lf", &expo);
    result = pow(base, expo);
    printf("%lf power of %lf = %lf\n", base, expo, result);
 
    result = sin(base);
    printf("sin of %lf = %lf\n", base, result);

    result = cos(base);
    printf("cos of %lf = %lf\n", base, result);

    return 0;
}
