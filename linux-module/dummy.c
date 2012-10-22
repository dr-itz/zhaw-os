#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/uaccess.h>

static int memory_major = 60;
static char *memory_buffer;

static int memory_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int memory_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t memory_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	copy_to_user(buf, memory_buffer, 1);
	if (*f_pos == 0) {
		(*f_pos)++;
		return 1;
	}
	return 0;
}

static ssize_t memory_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	const char *tmp = buf + count - 1;
	copy_from_user(memory_buffer, tmp, 1);
	return 1;
}

static struct file_operations memory_fops = {
	.read		= memory_read,
	.write		= memory_write,
	.open	  	= memory_open,
	.release	= memory_release
};

static int __init dummy_init(void)
{
	int ret;

	printk(KERN_INFO "Dummy is loading\n");

	memory_buffer = kmalloc(1, GFP_KERNEL);
	if (!memory_buffer)
		return -ENOMEM;

	memset(memory_buffer, 0, 1);

	ret = register_chrdev(memory_major, "dummy", &memory_fops);
	if (ret < 0)
		goto fail;

	printk(KERN_INFO "Dummy initialized\n");
	return 0;

fail:
	printk(KERN_INFO "dummy: cannot obtain major number %d\n", memory_major);
	kfree(memory_buffer);
	return ret;
}

static void __exit dummy_exit(void)
{
	unregister_chrdev(memory_major, "dummy");
	kfree(memory_buffer);

	printk(KERN_INFO "Dummy is unloading, time to buzz off\n");
}

module_init(dummy_init);
module_exit(dummy_exit);

MODULE_AUTHOR("DrItz");
MODULE_DESCRIPTION("Dumber than a dummy");
MODULE_LICENSE("GPL");
