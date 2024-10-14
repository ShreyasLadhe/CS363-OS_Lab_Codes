#include <stdio.h>

struct Process {
    int id;           
    int bur_time;   
    int arr_time; 
    int wait_time; 
    int turnar_time; 
};

void calc_wait_time(struct Process processes[], int n) {
    processes[0].wait_time = 0; 

    for (int i = 1; i < n; i++) {
        processes[i].wait_time = (processes[i - 1].bur_time + processes[i - 1].wait_time + processes[i - 1].arr_time) - processes[i].arr_time;
        
        if (processes[i].wait_time < 0) {
            processes[i].wait_time = 0;
        }
    }
}

void calc_turnar_time(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnar_time = processes[i].bur_time + processes[i].wait_time;
    }
}

void calc_avg_time(struct Process processes[], int n) {
    int total_wait_time = 0, total_turnar_time = 0;

    for (int i = 0; i < n; i++) {
        total_wait_time += processes[i].wait_time;
        total_turnar_time += processes[i].turnar_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnar_time / n);
}

void proc_details(struct Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arr_time, processes[i].bur_time, processes[i].wait_time, processes[i].turnar_time);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; 
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arr_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].bur_time);
    }

    calc_wait_time(processes, n);
    calc_turnar_time(processes, n);

    proc_details(processes, n);
    calc_avg_time(processes, n);

    return 0;
}
