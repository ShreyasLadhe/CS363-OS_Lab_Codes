#include <stdio.h>
#include <stdlib.h>

#define Max 100

int n, m;
int alloc[Max][Max], MaxNeed[Max][Max], need[Max][Max], available[Max];
int finish[Max];

void input(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file.\n");
        exit(1);
    }
    fscanf(file, "%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%d", &alloc[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%d", &MaxNeed[i][j]);
            need[i][j] = MaxNeed[i][j] - alloc[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        fscanf(file, "%d", &available[i]);
    }

    fclose(file);
}

int isSafe() {
    int work[Max];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            for (int i = 0; i < n; i++) {
                if (!finish[i]) {
                    return 0;
                }
            }
            return 1;
        }
    }
}

int main() {
    input("multi_instance_input.txt");
    if (isSafe()) {
        printf("In safe state.\n");
    } else {
        printf("Not in safe state.\n");
    }
    return 0;
}
