#ifndef CHARDEV_H
#define CHARDEV_H

#define MAX_DEV			1
#define DEVICE_NAME		"virtspi0.0"
#define DEVICE_CLASS_NAME	"chrdevclass"
#define MAX_DATA_SIZE		128

#define READ_TEMPERATURE	0x1
#define READ_HUMIDITY		0x2
#define READ_PRESSURE		0x3
#define WRITE_CONFIG		0x4
#define RESET_DEVICE		0x5

#define SPI_IOC_WR_MODE			_IOW('s', 1, int)
#define SPI_IOC_RD_MODE			_IOR('s', 2, int)
#define SPI_IOC_WR_MAX_SPEED_HZ		_IOW('s', 3, int)
#define SPI_IOC_RD_MAX_SPEED_HZ		_IOR('s', 4, int)
#define SPI_IOC_WR_LSB_FIRST		_IOW('s', 5, int)
#define SPI_IOC_RD_LSB_FIRST		_IOR('s', 6, int)
#define SPI_IOC_WR_BITS_PER_WORD	_IOW('s', 7, int)
#define SPI_IOC_RD_BITS_PER_WORD	_IOR('s', 8, int)

struct char_device_data {
    struct cdev cdev;
    unsigned short command;
    unsigned int payload;
};

typedef unsigned char	uint8;
typedef unsigned short  uint16;
typedef unsigned int	uint32;

static int chardev_open(struct inode *inode, struct file *file);
static int chardev_release(struct inode *inode, struct file *file);
static long chardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t chardev_read(struct file *file, char __user *buf, size_t count, loff_t *offset);
static ssize_t chardev_write(struct file *file, const char __user *buf,
		 size_t count, loff_t *offset);
#endif
