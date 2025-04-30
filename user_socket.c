#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <netinet/in.h>

// Define a Netlink protocol
#define NETLINK_USER 31

// Define the message structure
struct nl_msg {
    struct nlmsghdr nlh;
    char msg[1024];
};

int main() {
    // Create a Netlink socket
    int sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Set up the Netlink message
    struct nl_msg message;
    memset(&message, 0, sizeof(message));
    
    // Prepare the Netlink header
    message.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(message.msg));
    message.nlh.nlmsg_type = NLMSG_DONE;
    message.nlh.nlmsg_flags = 0;
    message.nlh.nlmsg_seq = 0;
    message.nlh.nlmsg_pid = getpid();  // PID of the sending process

    // Add the message content
    strcpy(message.msg, "Hello Kernel from User Space!");

    // Define the address for the kernel
    struct sockaddr_nl sa_kernel;
    memset(&sa_kernel, 0, sizeof(sa_kernel));
    sa_kernel.nl_family = AF_NETLINK;

    // Send the message to the kernel (unicast)
    int send_len = sendto(sock_fd, &message, sizeof(message), 0, 
                          (struct sockaddr*)&sa_kernel, sizeof(sa_kernel));
    if (send_len < 0) {
        perror("Message sending failed");
        close(sock_fd);
        return -1;
    }
    printf("Message sent to kernel: %s\n", message.msg);

    // Receive a response from the kernel
    struct nlmsghdr *nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(1024));
    struct sockaddr_nl sa_user;
    socklen_t sa_user_len = sizeof(sa_user);

    int recv_len = recvfrom(sock_fd, nlh, NLMSG_SPACE(1024), 0, 
                            (struct sockaddr*)&sa_user, &sa_user_len);
    if (recv_len < 0) {
        perror("Receiving failed");
        close(sock_fd);
        return -1;
    }
    printf("Received message from kernel: %s\n", (char *)NLMSG_DATA(nlh));

    // Close the socket
    close(sock_fd);
    return 0;
}
