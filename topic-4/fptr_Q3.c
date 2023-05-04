#include <stdio.h>

enum operations {
	ADD = 0,
	SUBTRACT,
	MULTIPLY,
	DIVIDE
};


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

int (*op_ptr[4])(int, int) = {add, subtract, multiply, divide};

int calculate(enum operations op, int a, int b)
{
     int result;

     result = (*op_ptr[op])(a, b);

     return result;
}

int main(void)
{
    int result;

    result = calculate(ADD, 85, 60);
    printf("addition of 85 + 60 = %d\n", result); 
    result = calculate(SUBTRACT, 97, 51);
    printf("sub of 97 - 51 = %d\n", result);
    result = calculate(MULTIPLY, 4, 50);
    printf("mul of 4 * 50 = %d\n", result);
    result = calculate(DIVIDE, 42, 21);
    printf("div of 42 / 21 = %d\n", result);
    return 0;
}
