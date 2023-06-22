#ifndef CHARDEV_H
#define CHARDEV_H

static int chardev_open(struct inode *inode, struct file *file);
static int chardev_release(struct inode *inode, struct file *file);
static long chardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t chardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t chardev_write(struct file *file, const char __user *buf,
		 size_t count, loff_t *offset);
#endif
