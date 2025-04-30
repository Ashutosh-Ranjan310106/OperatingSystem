#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <net/sock.h>

// Define a Netlink protocol ID
#define NETLINK_USER 31

struct sock *nl_sk = NULL;

static void nl_recv_msg(struct sk_buff *skb) {
    struct nlmsghdr *nlh;
    char *msg;

    // Retrieve the Netlink message header
    nlh = (struct nlmsghdr*)skb->data;
    msg = NLMSG_DATA(nlh);

    printk(KERN_INFO "Kernel received message: %s\n", msg);

    // Prepare a response message
    char *response = "Message received by kernel!";
    struct sk_buff *skb_out;
    int msg_size = strlen(response);
    int res;

    // Allocate memory for the response message
    skb_out = nlmsg_new(msg_size, 0);
    if (!skb_out) {
        printk(KERN_ERR "Failed to allocate skb for response\n");
        return;
    }

    // Fill the Netlink message header
    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    strcpy(NLMSG_DATA(nlh), response);

    // Send the response back to user-space
    res = nlmsg_unicast(nl_sk, skb_out, nlh->nlmsg_pid);
    if (res < 0)
        printk(KERN_INFO "Error while sending response to user\n");
}

static int __init nl_init(void) {
    struct netlink_kernel_cfg cfg = {
        .input = nl_recv_msg,
    };

    // Create a Netlink socket using the correct function call
    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
    if (!nl_sk) {
        printk(KERN_ALERT "Error creating Netlink socket\n");
        return -1;
    }
    printk(KERN_INFO "Netlink socket created\n");
    return 0;
}

static void __exit nl_exit(void) {
    // Cleanup and remove Netlink socket
    netlink_kernel_release(nl_sk);
    printk(KERN_INFO "Netlink socket released\n");
}

module_init(nl_init);
module_exit(nl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Netlink module");
