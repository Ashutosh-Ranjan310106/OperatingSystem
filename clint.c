#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "127.0.0.1:8080"
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    // Set up socket address struct
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    // Connect to server
    if (connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect error");
        exit(EXIT_FAILURE);
    }

    // Send message
    printf("enter message to send to server: ");
    char msg[BUFFER_SIZE];
    scanf("%s", msg);
    write(client_fd, msg, strlen(msg));

    // Receive response
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Received from server: %s\n", buffer);

    // Close socket
    close(client_fd);

    return 0;
}
