#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("Child process (PID: %d) is running...\n", getpid());
        sleep(2);  
        printf("Child process (PID: %d) is exiting...\n", getpid());
        return 0; 
    } else {
        printf("Parent process (PID: %d) created child process (PID: %d).\n", getpid(), pid);
        sleep(5);
        wait(NULL);
        printf("Parent process (PID: %d) has collected the child's exit status.\n", getpid());
    }

    return 0;
}
