// Standard libraries for handling sockets, system calls, and basic functionality are included here. Specifically, sys/socket.h for socket APIs, linux/netlink.h for Netlink socket functionality, and others for memory operations, standard I/O, and process control.

#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Defines NETLINK_USER as 31, a protocol number for user-defined Netlink communication.
#define NETLINK_USER 31

struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;
struct msghdr msg;
// src_addr and dest_addr: Structures to store source and destination address information for the Netlink socket.
// nlh: Pointer to Netlink message header, which will be dynamically allocated.
// iov: I/O vector structure used to manage the Netlink message buffer.
// sock_fd: Socket file descriptor.
// msg: Message header for sending/receiving a message via the socket.

int main() {
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if(sock_fd < 0) {
        return -1;
    }
    // Creates a Netlink socket using PF_NETLINK as the protocol family, SOCK_RAW to specify raw communication, and NETLINK_USER as the Netlink protocol. If the socket creation fails, the program returns -1. 
    // Raw mode (by socket type SOCK_RAW) is basically there to allow you to bypass some of the way that your computer handles TCP/IP. Rather than going through the normal layers of encapsulation/decapsulation that the TCP/IP stack on the kernel does, you just pass the packet to the application that needs it. No TCP/IP processing -- so it's not a processed packet, it's a raw packet. The application that's using the packet is now responsible for stripping off the headers, analyzing the packet, all the stuff that the TCP/IP stack in the kernel normally does for you.

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid(); /* self pid */
    // Initializes the source address structure to zeros.
    // Sets nl_family to AF_NETLINK to use the Netlink family of addresses(Address Family - AF).
    // Assigns the process ID (getpid()) to nl_pid, making this socket unique to the process.

    // Binds the socket to the previously configured source address.
    bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));

    // Destination Address Setup:
    // Initializes the destination address structure.
    // Sets nl_family to AF_NETLINK.
    // nl_pid set to 0 indicates the message is intended for the kernel.
    // nl_groups set to 0 specifies it is a unicast message.
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; /* For Linux Kernel */
    dest_addr.nl_groups = 0; /* unicast */

    // Netlink Message Setup:
    // Allocates memory for the Netlink message header.
    // Clears the allocated space.
    // Sets the message length, process ID, and flags.
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(1024));
    memset(nlh, 0, NLMSG_SPACE(1024));
    nlh->nlmsg_len = NLMSG_SPACE(1024);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    // Copies the string "Hello" into the message data part of the Netlink message.
    strcpy(NLMSG_DATA(nlh), "Hello");

    // Message Vector Setup:
    // Configures the I/O vector to point to the Netlink message.
    // Prepares the message header for sending, associating it with the destination address and I/O vector.
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    memset(&msg, 0, sizeof(msg));
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    // Sending the message:
    // Sends the message to the kernel via the configured Netlink socket.
    sendmsg(sock_fd, &msg, 0);

    /* Receive message from kernel */
    recvmsg(sock_fd, &msg, 0);
    printf("Received message payload: %s\n", (char*)NLMSG_DATA(nlh));

    // Closes the socket file descriptor, cleaning up resources before exiting the program.
    close(sock_fd);
}
