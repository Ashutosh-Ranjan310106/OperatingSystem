#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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
        int a;
        scanf("%d", &a);
        printf("This is the child process. My PID is %d\n", getpid());
    } 
    else {
        // Parent process
        printf("This is the parent process. My PID is %d, and my child's PID is %d\n", getpid(), pid);
        int a;
        scanf("%d", &a);
    }

    return 0;
}
