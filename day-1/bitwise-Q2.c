#include <stdio.h>

int main(void)
{
    int x, y;

    printf("enter two numbers:\n");
    scanf("%d", &x);
    scanf("%d", &y);
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    printf("x = %d\n", x);
    printf("y = %d\n", y);


}
