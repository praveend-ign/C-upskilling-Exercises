/*! program to demonstrate creating static library
 * and linking with the main application code
 * add() and subtract() functions defined in
 * math_Q1.c which is created as a static library
 * and included while compiling this source file
 */
#include <stdio.h>

extern int add(int operand1, int operand2);
extern int subtract(int op1, int op2);

int main(void)
{
    int num1;
    int num2;
    int result;

    printf("Enter any two numbers for addition and subtraction:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    result = add(num1, num2);
    printf("result of add = %d\n", result);
    result = subtract(num1, num2);
    printf("result of subtract = %d\n", result);
    return 0;
}
