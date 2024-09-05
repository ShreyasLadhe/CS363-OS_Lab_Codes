#include <stdio.h>

int main() {
    int num1, num2;
    int *pNum1, *pNum2;

    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    pNum1 = &num1;
    pNum2 = &num2;

    if(*pNum1 > *pNum2) {
        printf("The larger number is: %d\n", *pNum1);
    } else {
        printf("The larger number is: %d\n", *pNum2);
    }

    return 0;
}