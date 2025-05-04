#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    int src_fd, dest_fd;
    char buffer[4096];
    ssize_t bytes_read, bytes_written;


    // Open source file
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    // Open or create destination file
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);
        return EXIT_FAILURE;
    }

    // Copy data from source to destination
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return EXIT_FAILURE;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from source file");
    }

    // Close both files
    close(src_fd);
    close(dest_fd);

    return EXIT_SUCCESS;
}
