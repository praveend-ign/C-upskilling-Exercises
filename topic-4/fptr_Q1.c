#include <stdio.h>


int add(int a, int b)
{
    int result;

    result = a + b;
    return result;
}

int subtract(int a, int b)
{
    int result;

    result = a - b;
    return result;
}

int multiply(int a, int b)
{
    int result;

    result = a * b;
    return result;
}

int divide(int a, int b)
{
    int result;

    result = a / b;
    return result;
}

int apply_operation(int (*fn_oper)(int, int), int x, int y)
{
     int result;

     result = (*fn_oper)(x, y);
}

int main(void)
{
    int d, e;
    int result;

    printf("Enter any two integers:\n");
    scanf("%d", &d);
    scanf("%d", &e);

    result = apply_operation((int (*)(int, int))add, d, e);
    printf("result of adding two numbers = %d\n", result);
    
    result = apply_operation((int (*)(int, int))subtract, d, e);
    printf("result of subtracting two numbers = %d\n", result);

    result = apply_operation((int (*)(int, int))multiply, d, e);
    printf("result of multiplying two numbers = %d\n", result);

    result = apply_operation((int (*)(int, int))divide, d, e);
    printf("result of multiplying two numbers = %d\n", result);

    return 0;
}
