#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include "led_opr.h"

/* 1. 确定主设备号                                                                 */
static int major = 0;
static struct class *led_class;
struct led_operations *p_led_opr;

#define LED_NUM 2

#define MIN(a, b) (a < b ? a : b)

/* 3. 实现对应的open/read/write等函数，填入file_operations结构体                   */
static ssize_t led_drv_write (struct file *file, const char __user *buf, size_t size, loff_t *offset)
{
	int err;
	char status;
	struct inode *inode = file_inode(file);	//通过fd获取inode fd>>"/dev/led"
	int minor = iminor(inode);		//从而获取次设备号  "/dev/led">>次设备号
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	err = copy_from_user(&status, buf, 1);
	
	p_led_opr->ctl(minor, status);	//次设备号
	return 0;
}

static int led_drv_open (struct inode *node, struct file *file)
{
	int minor = iminor(node);	//库函数获取次设备号 "/dev/led">>次设备号
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

	p_led_opr->init(minor);	//次设备号
	return 0;
}


/* 2. 定义自己的file_operations结构体                                              */
static struct file_operations led_drv = {
	.owner	 = THIS_MODULE,
	.open    = led_drv_open,
	.write   = led_drv_write,
};

/* 4. 把file_operations结构体告诉内核：注册驱动程序                                */
/* 5. 谁来注册驱动程序啊？得有一个入口函数：安装驱动程序时，就会去调用这个入口函数 */
static int __init led_init(void)
{
	int err;
	int i;
	
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	major = register_chrdev(0, "100ask_led", &led_drv);  /* /dev/led */

	led_class = class_create(THIS_MODULE, "100ask_led_class");
	err = PTR_ERR(led_class);
	if (IS_ERR(led_class)) {
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "100ask_led");
		return -1;
	}

	for(i = 0; i < LED_NUM; i++)
		device_create(led_class, NULL, MKDEV(major, i), NULL, "100ask_led%d", i); /* /dev/led */

	p_led_opr = get_board_led_opr();
	return 0;
}

/* 6. 有入口函数就应该有出口函数：卸载驱动程序时，就会去调用这个出口函数           */
static void __exit led_exit(void)
{
	int i;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	
	for(i = 0; i < LED_NUM; i++)
	device_destroy(led_class, MKDEV(major, i)); /* /dev/led */
	
	class_destroy(led_class);
	unregister_chrdev(major, "100ask_led");
}


/* 7. 其他完善：提供设备信息，自动创建设备节点                                     */

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");


