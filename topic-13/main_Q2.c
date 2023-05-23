/*! program to demonstrate creating dynamic library
 * and linking with the main application code
 * multiply() and divide() functions defined in
 * math_Q2.c which is created as a dynamic library
 * and included while compiling this source file.
 * commands to link the dynamic library (libmath.so) 
 * with the application code is :-
 * export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
 * gcc -L. main_Q2.c -lmath
 */
#include <stdio.h>

extern int multiply(int op1, int op2);
extern int divide(int divisor, int dividend);

int main(void)
{
    int result;
    int num1, num2;

    printf("Enter any two numbers:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);    

    result = multiply(num1, num2);
    printf("multiplication result = %d\n", result);
    result = divide(num1, num2);
    printf("division result = %d\n", result);

    return 0;
}
