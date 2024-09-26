#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        sleep(1);
        printf("A) My PID = %d\n", getpid());
        printf("B) My Parent PID = %d\n", getppid());
    } else {
        printf("C) My PID = %d\n", getpid());
        wait(NULL);
        printf("D) My Child PID = %d\n", pid);
    }

    return 0;
}
