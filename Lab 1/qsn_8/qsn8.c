#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char ch;
    int wordCount = 0, charCount = 0;
    int inWord = 0;

    printf("Enter the name of the file to open: ");
    scanf("%s", filename);

    filePointer = fopen(filename, "r");

    if (filePointer == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    while ((ch = fgetc(filePointer)) != EOF) {
        charCount++;

        if (isspace(ch)) {
            if (inWord) {
                wordCount++;
                inWord = 0;
            }
        } else {
            inWord = 1;
        }
    }

    if (inWord) {
        wordCount++;
    }

    fclose(filePointer);
    printf("The file %s has %d characters and %d words.\n", filename, charCount, wordCount);

    return 0;
}
