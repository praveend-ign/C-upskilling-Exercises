#include <stdio.h>

int main(void)
{
    int num1, num2;
    float average;

    printf("Enter two integer numbers:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);

    average = (float)(num1 + num2)/(float)2;

    printf("average of two nums = %f\n", average);

    return 0;
}
