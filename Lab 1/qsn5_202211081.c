#include <stdio.h>

int main() {
    char str[100];
    char *pStr = str; 
    int length = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    while (*pStr != '\0') {
        length++;
        pStr++;
    }
    if (str[length - 1] == '\n') {
        length--;
    }

    printf("The length of the string is: %d\n", length);

    return 0;
}
