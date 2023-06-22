#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include "chardev.h"

#define MAX_DEV			1
#define DEVICE_NAME		"chrdev"
#define DEVICE_CLASS_NAME	"chrdevclass"
#define MAX_DATA_SIZE		128

struct char_device_data {
    struct cdev cdev;
};

static int dev_major;
static char *kbuf;

static const struct file_operations chardev_fops = {
    .owner      	= THIS_MODULE,
    .open       	= chardev_open,
    .release    	= chardev_release,
    .unlocked_ioctl 	= chardev_ioctl,
    .read       	= chardev_read,
    .write       	= chardev_write
};

static struct char_device_data chardev_data[MAX_DEV];
static struct class *chardev_class = NULL;

static int __init chardrv_init(void)
{
    int err, i;
    dev_t dev;

    /*! allocate chardev region and assign Major number */
    err = alloc_chrdev_region(&dev, 0, MAX_DEV, DEVICE_NAME);
    if(err < 0) {
	printk("unable to alloc_chrdev_region\n");
	return -1;
    }
    dev_major = MAJOR(dev);

    /*! create sysfs class */
    chardev_class = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
    if(IS_ERR(chardev_class)) {
	printk("unable to class_create\n");
	return PTR_ERR(chardev_class);
    }

    /*! Create necessary number of the devices */
    for (i = 0; i < MAX_DEV; i++) {
        cdev_init(&chardev_data[i].cdev, &chardev_fops);
        chardev_data[i].cdev.owner = THIS_MODULE;

        cdev_add(&chardev_data[i].cdev, MKDEV(dev_major, i), 1);

        /*! create device node /dev/DEVICE_NAMEi, where i equal to the Minor number
	 */
        device_create(chardev_class, NULL, MKDEV(dev_major, i), NULL, DEVICE_NAME"%d", i);
    }
    return 0;
}

static void __exit chardev_destroy(void)
{
    int i;

    for (i = 0; i < MAX_DEV; i++) {
        device_destroy(chardev_class, MKDEV(dev_major, i));
	cdev_del(&chardev_data[i].cdev);
    }

    class_unregister(chardev_class);
    class_destroy(chardev_class);

    unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

static int chardev_open(struct inode *inode, struct file *file)
{
    printk("CHARDEV: Device open\n");
    kbuf = kmalloc(MAX_DATA_SIZE, GFP_KERNEL);
    if(kbuf == NULL) {
	printk("CHARDEV: unable to kmalloc\n");
    }
    return 0;
}

static int chardev_release(struct inode *inode, struct file *file)
{
    printk("CHARDEV: Device close\n");
    kfree(kbuf);
    kbuf = NULL;
    return 0;
}

static long chardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("CHARDEV: Device ioctl\n");
    return 0;
}

static ssize_t chardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    ssize_t retval;

    printk("CHARDEV: Device read\n");
    if(kbuf == NULL)
	    return 0;
    if(count > MAX_DATA_SIZE)
	   count = MAX_DATA_SIZE;

    retval = copy_to_user(buf, kbuf, count);
    if(retval != 0) {
	printk("unable to copy_to_user\n");
        return -EFAULT;
    }

    return count;
}

static ssize_t chardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    printk("CHARDEV: Device write\n");
    if(kbuf == NULL)
	    return 0;
    if(count > MAX_DATA_SIZE)
	    count = MAX_DATA_SIZE;

    if(copy_from_user(kbuf, buf, count)) {
	printk("unable to copy_from_user\n");
    	return -EFAULT;
    }

    return count;
}

module_init(chardrv_init);
module_exit(chardev_destroy);
MODULE_AUTHOR("pdesh");
MODULE_DESCRIPTION("demo of character device driver");
MODULE_LICENSE("GPL");

