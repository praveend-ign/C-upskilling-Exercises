/*! program to demonstrate creating static library
 * and linking with the main application code
 * commands to create dynamic library from c source file
 * is :- 
 * gcc -c -fpic math_Q2.c
 * gcc -shared -o libmath.so math_Q2.o
 */
#include <stdio.h>

/*! function for multiplication of two integers */
int multiply(int op1, int op2)
{
    return (op1 * op2);
}

/*! function for division of two integers */
int divide(int divisor, int dividend)
{
    return (divisor/dividend);
}
