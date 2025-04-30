#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "127.0.0.1:8080"
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    // Remove any existing socket file
    unlink(SOCKET_PATH);

    // Set up socket address struct
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    // Accept a connection

    while (buffer[0] != 'q') {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            perror("accept error");
            exit(EXIT_FAILURE);
        }
        // Receive message

        read(client_fd, buffer, BUFFER_SIZE);

        printf("Received from client: %s\n", buffer);

        // Send response
        write(client_fd, "Hello from server!", 19);
    }
    // Close sockets
    close(client_fd);
    close(server_fd);

    // Remove socket file
    unlink(SOCKET_PATH);

    return 0;
}
