#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/signal.h>
#include <linux/mutex.h>
#include <linux/mm.h>
#include <linux/timer.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/proc_fs.h>
#include <linux/poll.h>
#include <linux/capi.h>
#include <linux/kernelcapi.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/moduleparam.h>

#include "button_drv.h"

static struct file_operations button_opr = {
	.open = button_open,
	.read = button_read,
};


static int button_open(struct inode *inode, struct file *file)
{
	
	return 0;
}

static int button_read(struct file *file, char __user *buf, size_t, loff_t *)
{

	return 0;
}


int button_drv_init(void)
{
	
}

int button_drv_exit(void)
{
	
}



module_init(button_drv_init);
module_exit(button_drv_exit);
MODULE_LICENSE("GPL");

