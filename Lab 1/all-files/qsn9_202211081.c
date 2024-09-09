#include <stdio.h>

int main() {
    FILE *file1, *file2, *file3;
    char file1Name[100], file2Name[100], file3Name[100];
    char ch;

    printf("Enter the name of the first file: ");
    scanf("%s", file1Name);

    printf("Enter the name of the second file: ");
    scanf("%s", file2Name);

    printf("Enter the name of the new file to write the merged content: ");
    scanf("%s", file3Name);

    file1 = fopen(file1Name, "r");
    file2 = fopen(file2Name, "r");
    file3 = fopen(file3Name, "w");
    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, file3);
    }
    while ((ch = fgetc(file2)) != EOF) {
        fputc(ch, file3);
    }

    fclose(file1);
    fclose(file2);
    fclose(file3);

    printf("Files %s and %s have been merged into %s successfully.\n", file1Name, file2Name, file3Name);

    return 0;
}
