#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void child_process() {
    srandom(time(NULL) ^ (getpid() << 16));  // Seed random number generator uniquely for each child
    int iterations = random() % 30;  // Random number of iterations (no more than 30)

    for (int i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep(random() % 10);  // Sleep for a random time (no more than 10 seconds)
        printf("Child Pid: %d is awake! Where is my Parent: %d?\n", getpid(), getppid());
    }

    exit(0);  // Terminate the child process
}

int main() {
    pid_t pid1, pid2;
    int status;

    // Fork the first child
    pid1 = fork();
    if (pid1 == 0) {
        child_process();
    }

    // Fork the second child
    pid2 = fork();
    if (pid2 == 0) {
        child_process();
    }

    // Parent waits for both children to terminate
    for (int i = 0; i < 2; i++) {
        pid_t pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Child Pid: %d has completed with status: %d\n", pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
