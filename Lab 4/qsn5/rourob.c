#include <stdio.h>

struct Process {
    int id;     
    int bur_time;      
    int rem_time;  
    int arr_time;    
    int wait_time;    
    int turnar_time; 
};

void calc_time(struct Process processes[], int n, int time_quantum) {
    int curr_time = 0, comp_proc = 0;
    int i = 0;
    int total_wait_time = 0, total_turnar_time = 0;

    while (comp_proc < n) {
        if (processes[i].rem_time > 0 && processes[i].arr_time <= curr_time) {
            if (processes[i].rem_time > time_quantum) {
                curr_time += time_quantum;
                processes[i].rem_time -= time_quantum;
            } else {
                curr_time += processes[i].rem_time;
                processes[i].rem_time = 0;
                comp_proc++;

                processes[i].turnar_time = curr_time - processes[i].arr_time;
                processes[i].wait_time = processes[i].turnar_time - processes[i].bur_time;

                total_wait_time += processes[i].wait_time;
                total_turnar_time += processes[i].turnar_time;
            }
        }
        i = (i + 1) % n;
        if (curr_time < processes[i].arr_time) {
            curr_time++;
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int j = 0; j < n; j++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[j].id, processes[j].arr_time, processes[j].bur_time, processes[j].wait_time, processes[j].turnar_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wait_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnar_time / n);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; 
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arr_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].bur_time);
        processes[i].rem_time = processes[i].bur_time; 
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    calc_time(processes, n, time_quantum);

    return 0;
}
