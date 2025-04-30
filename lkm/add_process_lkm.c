#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "add_process_lkm"

static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);
// why static is used here?

static struct proc_ops proc_op_0 = {
    .proc_read = proc_read,
};
// this struct has the properties we want to change to change in the process

/*This function is called when the module is loaded*/

static int proc_init(void) {
    proc_create(PROC_NAME, 0, NULL, &proc_op_0);
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

    return 0;
}

/*This function is called when the module is removed */
static void proc_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n" , PROC_NAME);

}

//cat /proc/add_process lkm 
static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;

    if(completed) {
        completed = 0;
        return 0;
    }

    completed = 1;

    rv = sprint(buffer, "A process has been added to the Pseudo File System. \n");

    copy_to_user(usr_buf, buffer, rv);

    return rv;

}

/* Macros for registering module entry and exit points*/
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("MIT");
MODULE_DESCRIPTION("LKM to add process to pseudo file system /proc ");
MODULE_AUTHOR("Lakshay");