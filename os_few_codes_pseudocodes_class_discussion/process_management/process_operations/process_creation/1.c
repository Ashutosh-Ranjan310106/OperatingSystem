#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    pid_t pid;

    /* fork a child process */
    pid = fork();

    if (pid < 0) {  /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) {  /* child process */
        printf("\nI am the child: %d\n", getpid());
        // for (;;){}
        execlp("/bin/ls", "ls", NULL);  // Replace the child process with a new program
    }
    else {  /* parent process */
        printf("\n\nI am the parent process. My PID is %d\n", getpid());
        printf("& I am the parent of %d\n", pid);
        // for (;;){}
        wait(NULL);  // Parent waits for the child to complete
        printf("Child Complete\n");
    }

    return 0;
}

