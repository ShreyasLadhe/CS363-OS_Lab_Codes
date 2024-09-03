#include <stdio.h>

int main() {
    int num1, num2, result;
    int *pNum1, *pNum2;

    printf("Enter first integer: ");
    scanf("%d", &num1);
    printf("Enter second integer: ");
    scanf("%d", &num2);

    pNum1 = &num1;
    pNum2 = &num2;
    result = *pNum1 + *pNum2;

    printf("Sum of %d and %d is %d\n", *pNum1, *pNum2, result);

    return 0;
}
