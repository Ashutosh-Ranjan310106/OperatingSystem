#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int status;
    pid_t pid1, pid2;

    int a;

    pid1 = fork();
    if (pid1 == 0) {
        // First child process
        printf("First child process running with PID: %d\n", getpid());
        sleep(3); // Simulate some work

        printf("First child exiting\n");
        exit(0);  // Exit with status 0
    }
    else {
        pid2 = fork();
        if (pid2 == 0) {
            // Second child process
            printf("Second child process running with PID: %d\n", getpid());
            sleep(5); // Simulate some work

            printf("Second child exiting\n");
            exit(0);  // Exit with status 0
        } 
        else {
            // Parent process
            pid_t finished_pid;
            printf("Parent waiting for children to exit\n");

            while ((finished_pid = wait(&status)) > 0) {
                if (WIFEXITED(status)) {
                    printf("Child with PID %d exited with status %d.\n", finished_pid, WEXITSTATUS(status));
                }
            }
            printf("All children have exited.\n");
        }
    }

    return 0;
}
