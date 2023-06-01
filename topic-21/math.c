/*! sample C source code for
 * demonstration to build with 
 * Makefile
 */
#include "math.h"

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

