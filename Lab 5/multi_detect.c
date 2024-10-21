#include <stdio.h>
#include <stdlib.h>

#define Max 100

int n, m;
int alloc[Max][Max], req[Max][Max], avail[Max];
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
            fscanf(file, "%d", &req[i][j]);
        }
    }

    for (int i = 0; i < m; i++) {
        fscanf(file, "%d", &avail[i]);
    }

    fclose(file);
}

void dead_check() {
    int work[Max];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            int canProceed = 1;
            for (int j = 0; j < m; j++) {
                if (req[i][j] > work[j]) {
                    canProceed = 0;
                    break;
                }
            }
            if (!canProceed) {
                printf("Deadlock detected for process %d!\n", i);
                return;
            }
        }
    }
    printf("No deadlock detected.\n");
}

int main() {
    input("multi_instance_detection_input.txt");
    dead_check();
    return 0;
}
