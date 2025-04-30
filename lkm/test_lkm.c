#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init test_lkm_init(void) {
    printk("Inserting our first Linux Kernel Module\n");
    return 0;
}

static void __exit test_lkm_exit(void) {
    printk("Removing our first Linux Kernel Module\n");
}

module_init(test_lkm_init);
module_exit(test_lkm_exit);

MODULE_LICENSE("MIT");
MODULE_DESCRIPTION("Test LKM");
MODULE_AUTHOR("ashu");
