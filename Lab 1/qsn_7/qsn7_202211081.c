#include <stdio.h>

int main() {
    FILE *filePointer;
    char filename[100];
    char data[1000];

    printf("Enter the name of the file to create: ");
    scanf("%s", filename);

    filePointer = fopen(filename, "w");

    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter information to store in the file:\n");
    getchar();
    fgets(data, sizeof(data), stdin);


    fprintf(filePointer, "%s", data);
    fclose(filePointer);

    printf("Data successfully written to %s\n", filename);

    return 0;
}
