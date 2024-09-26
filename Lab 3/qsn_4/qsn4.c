#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void createProcesses(int level, int maxLevel) {
    if (level > maxLevel) {
        return;
    }

    pid_t pid = fork(); 

    if (pid == 0) {
        printf("Child Process: PID = %d, Parent PID = %d, Level = %d\n", getpid(), getppid(), level);
        createProcesses(level + 1, maxLevel); 
    } else {
        printf("Parent Process: PID = %d, Child PID = %d, Level = %d\n", getpid(), pid, level);
        wait(NULL);
    }
}

int main() {
    int maxLevel = 5;
    printf("Starting process...\n");
    createProcesses(1, maxLevel);
    printf("Process complete.\n");
    return 0;
}
