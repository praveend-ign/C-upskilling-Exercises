#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include "chardev.h"


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
static struct mutex cdevdata_mutex;

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

    /*! in our case only one device is required */
    for (i = 0; i < MAX_DEV; i++) {
        cdev_init(&chardev_data[i].cdev, &chardev_fops);
        chardev_data[i].cdev.owner = THIS_MODULE;

        cdev_add(&chardev_data[i].cdev, MKDEV(dev_major, i), 1);

        /*! create device node /dev/<DEVICE_NAME> 
	 */
        device_create(chardev_class, NULL, MKDEV(dev_major, i), NULL, DEVICE_NAME);
    }
    mutex_init(&cdevdata_mutex);
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
    mutex_destroy(&cdevdata_mutex);
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
    long retval;
    int mode, speed, lsb_first;
    int bits_per_word;

    printk("CHARDEV: Device ioctl\n");
    switch(cmd) {
	case SPI_IOC_WR_MODE:
		get_user(mode, (int __user *)arg);
		/*! only mode 0 supported as of now */
		if(mode == 0)
			retval = 0;
		else
			retval = -1;
		break;
	case SPI_IOC_RD_MODE:
                /*! only mode 0 supported as of now */
		retval = put_user(mode, (int __user *)arg);
		break;
	case SPI_IOC_WR_MAX_SPEED_HZ:
		get_user(speed, (int __user *)arg);
		/*! speed of 8000000 HZ is supported */
		if(speed == 8000000)
			retval = 0;
		else
			retval = -1;
		break;
	case SPI_IOC_RD_MAX_SPEED_HZ:
                /*! speed of 8000000 HZ is supported */
		retval = put_user(speed, (int __user *)arg);
               	break;
	case SPI_IOC_WR_LSB_FIRST:
		get_user(lsb_first, (int __user *)arg);
		/*! LSB first is zero, i.e. MSB is first */
		if(lsb_first == 0)
			retval = 0;
		else
			retval = -1;
		break;
	case SPI_IOC_RD_LSB_FIRST:
                /*! LSB first is zero, i.e. MSB is first */
		retval = put_user(lsb_first, (int __user *)arg);
                break;
	case SPI_IOC_WR_BITS_PER_WORD:
		get_user(bits_per_word, (int __user *)arg);
		/*! 8 bits per word is supported */
		if(bits_per_word == 8)
			retval = 0;
		else 
			retval = -1;
		break;
	case SPI_IOC_RD_BITS_PER_WORD:
		bits_per_word = *(int *)arg;
                /*! 8 bits per word is supported */
		retval = put_user(bits_per_word, (int __user *)arg);
                break;
	default:
		retval = -1;
		break;

    }
    return retval;
}

static ssize_t chardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    uint32 minor;
    uint16 command;
    int len;

    printk("CHARDEV: Device read\n");
    if(kbuf == NULL)
	    return 0;
    if(count > MAX_DATA_SIZE)
	    count = MAX_DATA_SIZE;
    
    minor = iminor(file_inode(file));
    if(minor >= MAX_DEV) {
	printk("invalid minor number\n");
	return -ENODEV;
    }
    if(mutex_lock_killable(&cdevdata_mutex))
	    return -EINTR;
    command = chardev_data[minor].command; 
    if(command == READ_TEMPERATURE) {
	/*! temperature arbitrary value is 32 degrees celsius */
	    chardev_data[minor].payload = 0x20;
    } else if(command == READ_HUMIDITY) {
	/*! relative humidity value of 46 percent */
	    chardev_data[minor].payload = 46;
    } else if(command == READ_PRESSURE) {
	/*! pressure sensor value of 31 bar */
	    chardev_data[minor].payload = 31;
    } else {
	/*! not read command */
	chardev_data[minor].payload = 0;
	return 0;
    }
    len = sizeof(chardev_data[minor].payload);
    if(copy_to_user(buf, &chardev_data[minor].payload, len)) {
	printk("unable to copy_to_user\n");
	return -EIO;
    }
    mutex_unlock(&cdevdata_mutex);
    return len;
}

static ssize_t chardev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    uint32 minor;

    printk("CHARDEV: Device write\n");
    if(kbuf == NULL)
	    return 0;
    if(count > MAX_DATA_SIZE)
	    count = MAX_DATA_SIZE;

    if(copy_from_user(kbuf, buf, count)) {
	printk("unable to copy_from_user\n");
    	return -EFAULT;
    }
    minor = iminor(file_inode(file));
    if(minor >= MAX_DEV) {
	printk("invalid minor number\n");
	return -ENODEV;
    }
    if(mutex_lock_killable(&cdevdata_mutex))
	    return -EINTR;
    chardev_data[minor].command = *(uint16 *)kbuf;
    if(chardev_data[minor].command == WRITE_CONFIG) {
	kbuf = kbuf + sizeof(chardev_data[minor].command);
	chardev_data[minor].payload = *(uint32 *)kbuf;
	printk("write configuration value = %x\n", chardev_data[minor].payload);
    } else if(chardev_data[minor].command == RESET_DEVICE) {
	printk("reset device command received\n");
    }
    mutex_unlock(&cdevdata_mutex);
    return count;
}

module_init(chardrv_init);
module_exit(chardev_destroy);
MODULE_AUTHOR("pdesh");
MODULE_DESCRIPTION("demo of character device driver");
MODULE_LICENSE("GPL");

