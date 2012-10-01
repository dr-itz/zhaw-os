#include <linux/module.h>

static int __init dummy_init(void)
{
	printk(KERN_INFO "Dummy is loading, ready to do nothing\n");
    return 0;
}

static void __exit dummy_exit(void)
{
	printk(KERN_INFO "Dummy is unloading, time to buzz off\n");
}

module_init(dummy_init);
module_exit(dummy_exit);

MODULE_AUTHOR("DrItz");
MODULE_DESCRIPTION("Dumber than a dummy");
MODULE_LICENSE("GPL");
