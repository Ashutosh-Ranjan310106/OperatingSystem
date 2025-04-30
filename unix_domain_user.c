#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define NETLINK_USER 31

int main() {
    struct sockaddr_nl sa;
    struct nlmsghdr *nlh = NULL;
    int sock_fd;
    char msg[256];

    // Create a Netlink socket
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;

    // Prepare the Netlink message
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(256));
    memset(nlh, 0, NLMSG_SPACE(256));
    nlh->nlmsg_len = NLMSG_SPACE(256);
    nlh->nlmsg_pid = getpid();  // Set the PID of the sending process
    nlh->nlmsg_flags = 0;

    strcpy(NLMSG_DATA(nlh), "Hello from user-space");

    // Send the message to the kernel
    sendto(sock_fd, nlh, nlh->nlmsg_len, 0, (struct sockaddr*)&sa, sizeof(sa));

    // Receive the response from the kernel
    recv(sock_fd, nlh, NLMSG_SPACE(256), 0);
    printf("Received message from kernel: %s\n", (char*)NLMSG_DATA(nlh));

    // Clean up
    close(sock_fd);
    free(nlh);

    return 0;
}
