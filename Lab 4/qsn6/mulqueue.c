#include <stdio.h>

#define MAX 100

struct Process {
    int id;
    int bur_time;
    int arr_time;
    int prio;
    int wait_time;
    int turnar_time;
};

void sort_arr_time(struct Process queue[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (queue[i].arr_time > queue[j].arr_time) {
                temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }
}

void calc_time(struct Process queue[], int n) {
    int curr_time = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i].arr_time > curr_time) {
            curr_time = queue[i].arr_time;
        }
        queue[i].wait_time = curr_time - queue[i].arr_time;
        queue[i].turnar_time = queue[i].wait_time + queue[i].bur_time;
        curr_time += queue[i].bur_time;
    }
}

void proc_details(struct Process queue[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tprio\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", queue[i].id, queue[i].arr_time, queue[i].bur_time, queue[i].prio, queue[i].wait_time, queue[i].turnar_time);
    }
}

int main() {
    int n, i, high_prio_count = 0, low_prio_count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n], high_prio_queue[MAX], low_prio_queue[MAX];

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arr_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].bur_time);
        printf("Enter prio for process %d (0 for high, 1 for low): ", i + 1);
        scanf("%d", &processes[i].prio);

        if (processes[i].prio == 0) {
            high_prio_queue[high_prio_count++] = processes[i];
        } else {
            low_prio_queue[low_prio_count++] = processes[i];
        }
    }

    sort_arr_time(high_prio_queue, high_prio_count);
    sort_arr_time(low_prio_queue, low_prio_count);

    printf("\nHigh prio Queue (prio 0)\n");
    calc_time(high_prio_queue, high_prio_count);
    proc_details(high_prio_queue, high_prio_count);

    printf("\nLow prio Queue (prio 1)\n");
    calc_time(low_prio_queue, low_prio_count);
    proc_details(low_prio_queue, low_prio_count);

    return 0;
}
