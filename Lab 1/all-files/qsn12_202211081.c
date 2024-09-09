#include <stdio.h>
#include <ctype.h>

void rot13(char *ch) {
    if (*ch >= 'a' && *ch <= 'z') {
        *ch = ((*ch - 'a' + 13) % 26) + 'a';
    } else if (*ch >= 'A' && *ch <= 'Z') {
        *ch = ((*ch - 'A' + 13) % 26) + 'A';
    }
}

int main() {
    char inpfile[100], outfile[100], ch;
    FILE *ifile, *ofile;

    printf("Enter the name of the file to read from: ");
    scanf("%s", inpfile);

    printf("Enter the name of the output file: ");
    scanf("%s", outfile);

    ifile = fopen(inpfile, "r");
    ofile = fopen(outfile, "w");
    while ((ch = fgetc(ifile)) != EOF) {
        rot13(&ch); 
        fputc(ch, ofile);
    }

    fclose(ifile);
    fclose(ofile);

    printf("The result has been written to %s.\n", outfile);

    return 0;
}
