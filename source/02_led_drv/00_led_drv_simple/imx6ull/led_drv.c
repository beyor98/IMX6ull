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

int major;
static struct class *led_class;

/* registers */
// IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 地址：0x02290000 + 0x14
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;

// GPIO5_GDIR 地址：0x020AC004
static volatile unsigned int *GPIO5_GDIR;

//GPIO5_DR 地址：0x020AC000
static volatile unsigned int *GPIO5_DR;

static int led_open(struct inode *inode, struct file *file)
{
	*IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 &= ~0xf;
	*IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 |= 0x5;

	*GPIO5_GDIR |= (1<<3);

	return 0;
}

static ssize_t led_write(struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
	char status;
	int err;
	
	err = copy_from_user(&status, user_buf, 1);
	
	/* to set gpio register: out 1/0 */
	if (status)
	{
		/* set gpio to let led on */
		*GPIO5_DR &= ~(1<<3);
	}
	else
	{
		/* set gpio to let led off */
		*GPIO5_DR |= (1<<3);
	}
	
	return 0;
}

static const struct file_operations led_fops = {
	.open = led_open,
	.write = led_write,
	.owner = THIS_MODULE,
};

static int __init led_init(void)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	major = register_chrdev(0, "100ask_led", &led_fops);

	/* ioremap */
	// IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 地址：0x02290000 + 0x14
	IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x02290000 + 0x14, 4);
	
	// GPIO5_GDIR 地址：0x020AC004
	GPIO5_GDIR = ioremap(0x020AC004, 4);
	
	//GPIO5_DR 地址：0x020AC000
	GPIO5_DR  = ioremap(0x020AC000, 4);

	led_class = class_create(THIS_MODULE, "myled");
	device_create(led_class, NULL, MKDEV(major, 0), NULL, "myled"); /* /dev/myled */
	return 0;
}


static void __exit led_exit(void)
{	
	iounmap(IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3);
	iounmap(GPIO5_GDIR);
	iounmap(GPIO5_DR);
	
	device_destroy(led_class, MKDEV(major, 0));
	class_destroy(led_class);
	
	unregister_chrdev(major, "100ask_led");
}


module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
