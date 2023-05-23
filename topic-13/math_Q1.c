/*! program to demonstrate creating static library
 * and linking with the main application code
 * commands to create static library from c source file
 * is :- 
 * gcc -c -fpic math_Q1.c
 * ar rcs libmath.a math_Q1.o
 */
#include <stdio.h>

/*! function for addition of two integer numbers */
int add(int operand1, int operand2)
{
    int result;

    result = operand1 + operand2;

    return result;
}

/*! function for subtraction of two integers */
int subtract(int op1, int op2)
{
    int result;

    result = op1 - op2;

    return result;
}
