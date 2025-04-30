#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xe4c970fb, "module_layout" },
	{ 0x41107908, "netlink_kernel_release" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xacd51b29, "__netlink_kernel_create" },
	{ 0xf4ed5a7b, "init_net" },
	{ 0x79664ae7, "netlink_unicast" },
	{ 0xeeefc1f3, "__nlmsg_put" },
	{ 0x9f4b4bc0, "__alloc_skb" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "48C1FD9AC0EB4266E98512F");
