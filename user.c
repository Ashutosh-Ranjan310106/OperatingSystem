#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define NETLINK_TEST 17
#define MAX_PAYLOAD 1024 


int main() {
    struct sockaddr_nl src_addr, dest_addr;
    struct nlmsghdr *nlh = NULL;
    struct iovec iov;
    int sock_fd;
    struct msghdr msg;
    char* user_message = "Hello from user space!";

    // Create socket
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_TEST);
    if (sock_fd < 0) {
        perror("socket creation failed");
        return -1;
    }

    // Zero out address structs
    memset(&src_addr, 0, sizeof(src_addr));
    memset(&dest_addr, 0, sizeof(dest_addr));

    // Source address (this process)
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();  // self pid
    bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

    // Destination address (kernel)
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;   // kernel
    dest_addr.nl_groups = 0; // unicast

    // Allocate Netlink message buffer
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = NLMSG_SPACE(strlen(user_message)+1);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    // Copy message into payload
    strcpy(NLMSG_DATA(nlh), user_message);

    // Setup IO vector
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;

    // Setup message
    memset(&msg, 0, sizeof(msg));
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    // Send message to kernel
    printf("Sending message to kernel: %s\n", (char *)NLMSG_DATA(nlh));
    sendmsg(sock_fd, &msg, 0);

    // Receive message from kernel
    recvmsg(sock_fd, &msg, 0);
    printf("Received message from kernel: %s\n", (char *)NLMSG_DATA(nlh));

    // Cleanup
    close(sock_fd);
    free(nlh);
    return 0;
}