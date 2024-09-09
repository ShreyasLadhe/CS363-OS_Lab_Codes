#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char ch;
    int wcount = 0, ccount = 0;
    int inWord = 0;

    printf("Enter the name of the file to open: ");
    scanf("%s", filename);

    filePointer = fopen(filename, "r");
    while ((ch = fgetc(filePointer)) != EOF) {
        ccount++;

        if (isspace(ch)) {
            if (inWord) {
                wcount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }

    if (inWord) {
        wcount++;
    }

    fclose(filePointer);
    printf("The file %s has %d characters and %d words.\n", filename, ccount, wcount);

    return 0;
}
