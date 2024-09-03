#include <stdio.h>

int main() {
    int num = 81;
    char ch = 's';
    char str[] = "This is Shreyas!";

    int *pNum = &num;
    char *pCh = &ch;
    char *pStr = str;

    printf("Address of integer variable 'num': %p\n", pNum);
    printf("Address of character variable 'ch': %p\n", pCh);
    printf("Address of string variable 'str': %p\n", pStr);

    return 0;
}
