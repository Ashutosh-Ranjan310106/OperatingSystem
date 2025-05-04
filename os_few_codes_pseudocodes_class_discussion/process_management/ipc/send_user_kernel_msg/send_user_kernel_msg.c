// LKM code

// linux/module.h: Needed for all kernel modules.
// linux/netlink.h: Provides the definitions and functions for Netlink sockets.
// net/sock.h: Includes definitions for the socket interface.
#include <linux/module.h>
#include <linux/netlink.h>
#include <net/sock.h>

// Protocol Number: In Netlink, the protocol number identifies the specific communication type or service within the Netlink family. It serves a similar role to the protocol field in the IP header, which tells the networking stack how to interpret the contents of a packet (e.g., TCP, UDP).
// Defines NETLINK_USER as 31, which is the protocol number used for creating the Netlink socket. Protocol numbers can vary, and 31 is typically used for custom or user-defined purposes.
#define NETLINK_USER 31

struct sock *nl_sk = NULL;
// nl_sk is a pointer to a sock structure, used to represent the Netlink socket. Initialized to NULL.

// nl_recv_msg is a function that handles incoming Netlink messages. It takes a pointer to a struct sk_buff, which is the standard buffer structure for storing network data in the Linux kernel.
static void nl_recv_msg(struct sk_buff *skb) {

    struct nlmsghdr *nlh;
    int pid;
    struct sk_buff *skb_out;
    int msg_size;
    char *msg = "Hello from kernel";
    int res;
// nlh: Pointer to Netlink message header.
// pid: Process ID of the sending process.
// skb_out: Socket buffer that will be used for outgoing messages.
// msg_size: Size of the outgoing message.
// msg: Pointer to the message "Hello from kernel".
// res: Used to store the result of sending the message.

    nlh = (struct nlmsghdr*)skb->data;
    pid = nlh->nlmsg_pid; /* pid of sending process */
    printk(KERN_INFO "Kernel module received msg payload:%s\n", (char *)nlmsg_data(nlh));
// Extracts the Netlink message header from the received socket buffer (skb).
// Retrieves the PID from the message header, which is used for sending the response.
// Logs the received message using printk, a function to output messages to the kernel log.


    msg_size = strlen(msg);

    skb_out = nlmsg_new(msg_size, 0);
    if (!skb_out) {
        printk(KERN_ERR "Failed to allocate new skb\n");
        return;
    } 
// Calculates the size of the outgoing message.
// Allocates a new socket buffer for the outgoing message. If allocation fails, it logs an error and exits the function.


    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);  
    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
    strncpy(nlmsg_data(nlh), msg, msg_size);
// Puts the message into the newly created socket buffer using nlmsg_put.
// Sets the destination group to 0, indicating it's not intended for a multicast group.
// Copies the message into the data part of the Netlink message header.

    res = nlmsg_unicast(nl_sk, skb_out, pid);

    if (res < 0) {
        printk(KERN_INFO "Error while sending.\n");
    }
// Sends the message using nlmsg_unicast, which unicast the message back to the process identified by pid.
// Checks if the sending was successful and logs an error if not.

}

static int __init hello_init(void) {
    struct netlink_kernel_cfg cfg = {
        .input = nl_recv_msg,
    };

    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
    // &init_net: This specifies the network namespace in which the Netlink socket should be created. By using init_net, you are indicating that the socket should be associated with the initial (or default) network namespace. This is the global network namespace where the kernel starts and operates by default unless explicitly changed by user actions or specific processes that create or move into new namespaces.
    if (!nl_sk) {
        printk(KERN_ALERT "Error creating socket.\n");
        return -2;
    }

    return 0;

// Configures the Netlink socket with the nl_recv_msg as the function to handle incoming messages.
// Attempts to create the Netlink socket and logs an error if it fails.
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "exiting hello module\n");
    netlink_kernel_release(nl_sk);
}
// Called when the module is removed. It logs a message and releases the Netlink socket.


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");