#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
// sys/socket.h provides the necessary functions and structures for socket programming.
// sys/un.h contains definitions for UNIX domain sockets.
// unistd.h provides access to the POSIX operating system API, including system calls like unlink.


#define SOCKET_PATH "/tmp/unix.sock"
// SOCKET_PATH defines the file system path where the socket file will be created. This path is used by both the server and any clients to identify the socket.


int main(void) {
    int server_fd, client_socket;
    struct sockaddr_un address;
    // server_fd will hold the file descriptor of the server socket.
    // client_socket will hold the file descriptor for the client socket once a connection is accepted.
    // address is a structure that will hold the address of the UNIX domain socket.

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    // AF_UNIX (also known as AF_LOCAL): This constant represents the "Address Family" for UNIX domain sockets.
    // SOCK_STREAM: This constant represents the socket type and specifies that the socket is stream-oriented. In the context of AF_UNIX, it means that the socket operates like a TCP socket over IP, providing reliable, two-way, connection-based byte streams.
    if (server_fd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    // Socket Creation:
    // Creates a UNIX domain socket of type stream (SOCK_STREAM). If the socket creation fails, it prints an error message and exits.

    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);
    unlink(SOCKET_PATH);
    // sets the family of the address
    // copies the socket path to the address.sun_path
    // remove any file at the socket path
    
    
    
    // Address Setup and Cleanup:
    // Sets the family of the address to UNIX (AF_UNIX).
    // Copies the socket path to address.sun_path. The path is truncated to ensure it doesn't exceed the size of sun_path.
    // Calls unlink to remove any existing file at the socket path, ensuring that the bind operation will succeed.

    // Binding:
    // Binds the server socket to the specified address. If binding fails, it prints an error message and exits.
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening:
    // Marks the socket as a passive socket that will be used to accept incoming connection requests. The 5 specifies the maximum number of pending connections.
    if (listen(server_fd, 5) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening at %s\n", SOCKET_PATH);
    // Server Ready:
    // Informs the user that the server is set up and listening for connections on the specified socket path.

    while (1) {
        client_socket = accept(server_fd, NULL, NULL);
        if (client_socket == -1) {
            perror("accept failed");
            continue;
        }
        // Connection Acceptance:
        // Infinitely loops to accept incoming connections. When a client connects, accept returns a new socket that is connected to the client.
        // If accept fails, it logs an error and waits for the next connection.

        char buffer[128];
        int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_read > 0) {
            printf("Received: %s\n", buffer);
            send(client_socket, "Hello from server", 17, 0);
            // 17: This parameter specifies the length of the message in bytes that should be sent. In this case, the string "Hello from server" is 17 characters long, including the null terminator \0 that marks the end of the string in C. However, in network transmissions using send(), the null terminator is typically not needed unless the receiving side expects it for string processing. It's crucial to ensure that this length accurately reflects the number of bytes you intend to send to avoid truncation or memory access errors.
        }
        close(client_socket);
        // Communication:
        // Reads data sent by the client into buffer using recv.
        // If data is received (bytes_read > 0), it prints the data and sends a response back to the client.
        // Closes the client socket after handling the communication.
    }

    close(server_fd);
    return 0;
}
