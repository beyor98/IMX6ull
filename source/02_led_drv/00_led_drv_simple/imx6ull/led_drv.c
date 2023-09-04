#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/kobject.h>
#include <linux/slab.h>
#include <linux/irq.h>

static struct class *led_class;



static int led_open(struct inode *inode, struct file *file)
{
	
	return 0;
}

static ssize_t led_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	
	return 0;
}

static const struct file_operations led_fops = {
	.open = led_open,
	.write = led_write,
	.owner = THIS_MODULE,
};

static int __init led_init(void)
{
	int major;
	major = register_chrdev(0, "myled", &led_fops);

	led_class = class_create(THIS_MODULE, "myled");
	return 0;
}


static void __exit led_exit(void)
{
	class_destroy(led_class);
	unregister_chrdev(major, "myled");
	return 0;
}


module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE(GPL);

