// Compile using the following command
// gcc -o receiver receiver.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024
#define PERMISSIONS 0660

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    ssize_t bytes_read;

    // Set the queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Create the message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, PERMISSIONS, &attr);
    if (mq == -1) {
        perror("Message queue creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Receiver up and running.\n");

    // Receive the message
    while (1) {
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0';
            printf("Received: %s\n", buffer);
        }
        else {
            perror("mq_receive");
            break;
        }
    }

    // Cleanup
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}
