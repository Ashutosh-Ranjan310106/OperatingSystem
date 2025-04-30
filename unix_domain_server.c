#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h> // For strncpy()

#define SOCKET_PATH "/tmp/unix.sock" // "/tmp" is commonly used for temporary files

int main(void) {
    int server_fd, client_socket;
    struct sockaddr_un address;

    // Create a UNIX domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sun_family = AF_UNIX;  // Set the address family to UNIX domain

    // Associate the actual path of the socket to the address variable
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    // Remove any existing socket file
    unlink(SOCKET_PATH);

    // Bind the socket to the specified address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections (max backlog of 5)
    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening at %s\n", SOCKET_PATH);

    while (1) {
        // Accept a client connection
        client_socket = accept(server_fd, NULL, NULL);  // Fixed the variable name here
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        char buffer[128];
        int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';  // Null-terminate the received string
            printf("Received: %s\n", buffer);
            send(client_socket, "Hello from server", 17, 0);
        }

        close(client_socket); // Close the client connection
    }

    close(server_fd); // Close the server socket
    return 0;
}
