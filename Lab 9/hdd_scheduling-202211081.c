#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void fcfs(int requests[], int n, int head) {
    int seek_distance = 0, current = head;
    printf("FCFS Order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
        seek_distance += abs(requests[i] - current);
        current = requests[i];
    }
    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

void sstf(int requests[], int n, int head) {
    int *visited = calloc(n, sizeof(int));
    int seek_distance = 0, current = head;
    printf("SSTF Order: ");
    for (int i = 0; i < n; i++) {
        int min_distance = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(requests[j] - current) < min_distance) {
                min_distance = abs(requests[j] - current);
                index = j;
            }
        }
        visited[index] = 1;
        printf("%d ", requests[index]);
        seek_distance += min_distance;
        current = requests[index];
    }
    free(visited);
    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

void scan(int requests[], int n, int head, int direction, int max_cylinder) {
    printf("SCAN Order: ");
    int *sorted_requests = malloc((n + 2) * sizeof(int));
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];
    sorted_requests[n] = 0; // Add the boundary cylinder
    sorted_requests[n + 1] = max_cylinder;
    qsort(sorted_requests, n + 2, sizeof(int), compare);

    int seek_distance = 0, current = head;
    int pos = 0;
    while (pos < n + 2 && sorted_requests[pos] < head) pos++;

    if (direction == 1) { 
        for (int i = pos; i < n + 2; i++) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
    } else { 
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
        for (int i = pos; i < n + 2; i++) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
    }
    free(sorted_requests);
    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

void cscan(int requests[], int n, int head, int max_cylinder) {
    printf("C-SCAN Order: ");
    int *sorted_requests = malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];
    sorted_requests[n] = max_cylinder;
    qsort(sorted_requests, n + 1, sizeof(int), compare);

    int seek_distance = 0, current = head;
    int pos = 0;
    while (pos < n + 1 && sorted_requests[pos] < head) pos++;

    for (int i = pos; i < n + 1; i++) {
        printf("%d ", sorted_requests[i]);
        seek_distance += abs(sorted_requests[i] - current);
        current = sorted_requests[i];
    }
    for (int i = 0; i < pos; i++) {
        printf("%d ", sorted_requests[i]);
        seek_distance += abs(sorted_requests[i] - current);
        current = sorted_requests[i];
    }
    free(sorted_requests);
    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

void look(int requests[], int n, int head, int direction) {
    printf("LOOK Order: ");
    int *sorted_requests = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];
    qsort(sorted_requests, n, sizeof(int), compare);

    int seek_distance = 0, current = head;
    int pos = 0;
    while (pos < n && sorted_requests[pos] < head) pos++;

    if (direction == 1) { // Towards larger cylinders
        for (int i = pos; i < n; i++) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
    } else { // Towards smaller cylinders
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
        for (int i = pos; i < n; i++) {
            printf("%d ", sorted_requests[i]);
            seek_distance += abs(sorted_requests[i] - current);
            current = sorted_requests[i];
        }
    }
    free(sorted_requests);
    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

void clook(int requests[], int n, int head) {
    printf("C-LOOK Order: ");
    int *sorted_requests = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];
    qsort(sorted_requests, n, sizeof(int), compare);

    int seek_distance = 0, current = head;
    int pos = 0;
    while (pos < n && sorted_requests[pos] < head) pos++;

    for (int i = pos; i < n; i++) {
        printf("%d ", sorted_requests[i]);
        seek_distance += abs(sorted_requests[i] - current);
        current = sorted_requests[i];
    }
    for (int i = 0; i < pos; i++) {
        printf("%d ", sorted_requests[i]);
        seek_distance += abs(sorted_requests[i] - current);
        current = sorted_requests[i];
    }
    free(sorted_requests);
    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

int main() {
    int n, head, direction, max_cylinder;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }
    
    int *requests = malloc(n * sizeof(int));
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the maximum cylinder size: ");
    scanf("%d", &max_cylinder);
    printf("Enter the scanning direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    printf("\n--- Disk Scheduling Simulation ---\n");
    fcfs(requests, n, head);
    printf("\n");
    sstf(requests, n, head);
    printf("\n");
    scan(requests, n, head, direction, max_cylinder);
    printf("\n");
    cscan(requests, n, head, max_cylinder);
    printf("\n");
    look(requests, n, head, direction);
    printf("\n");
    clook(requests, n, head);

    free(requests);
    return 0;
}
