// Compile using the following command
// gcc -o sender sender.c -lrt


#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024
#define PERMISSIONS 0660

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];

    // Open the message queue
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        perror("Opening message queue failed");
        exit(EXIT_FAILURE);
    }

    printf("Send to queue: ");
    fflush(stdout);
    memset(buffer, 0, MAX_SIZE);
    fgets(buffer, MAX_SIZE, stdin);

    // Send the message
    if (mq_send(mq, buffer, strlen(buffer), 0) == -1) {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    mq_close(mq);
    return 0;
}
