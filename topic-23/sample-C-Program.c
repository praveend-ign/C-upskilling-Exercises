/*! sample C program for creating
 *  software requirement specification
 *  and software design document
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double num1, num2;
	char op;
	double result;

	printf("Enter the operator:\n");
	fflush(stdin);
	scanf("%c", &op);
	printf("Enter the first number:\n");
	scanf("%lf", &num1);

	printf("Enter the second number:\n");
	scanf("%lf", &num2);

	switch(op) {
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	case '*':
		result = num1 * num2;
		break;
	case '/':
		if(num2 == 0) {
			printf("Error:Division by zero\n");
			exit(1);
		}
		result = num1 / num2;
		break;
	default:
		printf("Error: Invalid operator\n");
		exit(1);
	}
	printf("result = %lf\n", result);	
	return 0;
}
