#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "ls", NULL);
        return 1;
    } else if (pid > 0) {
        wait(NULL);

        pid = fork();
        if (pid == 0) {
            execl("/usr/bin/pstree", "pstree", NULL);
            return 1;
        }
    }

    return 0;
}
