#include <stdio.h>
#include <stdlib.h>

#define Max 10

int n, m;

int alloc[Max][Max];
int req[Max][Max];
int avail[Max];
int adj[Max][Max]; 

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
    for (int i = 0; i < m; i++) {
        fscanf(file, "%d", &avail[i]);
    }
    fclose(file);
}

int isSafe() {
    int work[Max];
    int finish[Max] = {0};
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    while (1) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int canAlloc = 1;
                for (int j = 0; j < m; j++) {
                    if (req[i][j] > work[j]) {
                        canAlloc = 0;
                        break;
                    }
                }
                if (canAlloc) {
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
    input("single_instance_input.txt");
    if (isSafe()) {
        printf("In safe state.\n");
    } else {
        printf("Not in safe state.\n");
    }
    return 0;
}
