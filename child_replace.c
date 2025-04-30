#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        // Error in forking
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // Child process

        // Replace child process with /bin/ls
        printf("Child process executing /bin/ls...\n");

        // Using execvp to execute /bin/ls
        char *argv[] = {"ls", "-l", NULL};  // Arguments for /bin/ls

        if (execvp("/bin/ls", argv) == -1) {
            // If execvp fails
            perror("execvp failed");
            exit(1);
        }
    } 
    else {
        // Parent process
        // Wait for child process to finish
        wait(NULL);  // Wait for the child to terminate
        printf("Parent process completed.\n");
    }

    return 0;
}
