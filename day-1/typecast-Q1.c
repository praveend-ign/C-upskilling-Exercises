#include <stdio.h>
/* take input two integers and calculate the float type average 
 * of two integers using implicit typecasting */

int main(void)
{
    int num1, num2;
    float average;

    printf("Enter two integer numbers:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);

    average = (num1 + num2)/2.0;

    printf("average of two nums = %.2f\n", average);

    return 0;
}
