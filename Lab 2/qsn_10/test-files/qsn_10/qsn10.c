#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    int printed = 0;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            printf("%s\n", argv[i]);
            printed = 1;
        }
    }

    if (!printed) {
    }

    return 0;
}

