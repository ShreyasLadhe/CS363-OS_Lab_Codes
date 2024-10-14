#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;             
    int bur_time;      
    int arr_time;    
    int prio;        
    int wait_time;    
    int turnar_time; 
    bool iscomp;      
};

int find_highprio_proc(struct Process processes[], int n, int curr_time) {
    int highest_prio = 100;
    int highest_prio_index = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arr_time <= curr_time && !processes[i].iscomp) {
            if (processes[i].prio < highest_prio) {
                highest_prio = processes[i].prio;
                highest_prio_index = i;
            }
        }
    }

    return highest_prio_index; 
}

void calc_times(struct Process processes[], int n) {
    int curr_time = 0;
    int iscomp_processes = 0;

    while (iscomp_processes < n) {
        int highest_prio_index = find_highprio_proc(processes, n, curr_time);

        if (highest_prio_index != -1) {
            struct Process *curr_proc = &processes[highest_prio_index];

            curr_time += curr_proc->bur_time;
            curr_proc->wait_time = curr_time - curr_proc->arr_time - curr_proc->bur_time;
            curr_proc->turnar_time = curr_time - curr_proc->arr_time;

            curr_proc->iscomp = true;
            iscomp_processes++;
        } else {
            curr_time++;
        }
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
    printf("\nProcess\tArrival Time\tBurst Time\tprio\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arr_time, processes[i].bur_time, processes[i].prio, processes[i].wait_time, processes[i].turnar_time);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; 
        processes[i].iscomp = false; 
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arr_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].bur_time);
        printf("Enter prio for process %d (lower number = higher prio): ", i + 1);
        scanf("%d", &processes[i].prio);
    }

    calc_times(processes, n);
    proc_details(processes, n);
    calc_avg_time(processes, n);

    return 0;
}