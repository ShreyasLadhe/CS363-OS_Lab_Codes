#include <stdio.h>
#include <ctype.h>

int main() {
    char input[1000];
    char filename[100];
    FILE *outputFile;
    int nonalphacount = 0, lowcount = 0, upcount = 0;

    printf("Enter a string:\n");
    fgets(input, sizeof(input), stdin); 

    printf("Enter the name of the output file: ");
    scanf("%s", filename);

    outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        printf("Could not open file %s for writing\n", filename);
        return 1;
    }

    for (int i = 0; input[i] != '\0'; i++) {
        if (islower(input[i])) {
            lowcount++;
        }
        else if (isupper(input[i])) {
            upcount++;
        }
        else {
            nonalphacount++;
        }
        if (isalnum(input[i])) {
            fputc(input[i], outputFile);
        }
    }
    fclose(outputFile);

    printf("Lowercase letters: %d\n", lowcount);
    printf("Uppercase letters: %d\n", upcount);
    printf("Non-alphabetic characters: %d\n", nonalphacount);

    printf("Characters have been written to the file '%s'.\n", filename);

    return 0;
}
