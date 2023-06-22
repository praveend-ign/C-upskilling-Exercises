#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>


static int spi_device_setup(int fd)
{
    int mode, speed;
    int wr_retval, rd_retval, i;
    int bits = 0;

    /*! spi mode: mode 0
     */
    mode = SPI_MODE_0;
    wr_retval = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    rd_retval = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if((wr_retval < 0) || (rd_retval < 0)) {
	perror("ioctl: set spi mode");
	return -1;
    }
    
    /*! Clock max speed in HZ
     */
    speed = 8000000; 
    wr_retval = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    rd_retval = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if((wr_retval < 0) || (rd_retval < 0)) {
	perror("ioctl: set max speed");
	return -1;
    }
    /*! setting SPI to MSB first.
     *  Here, 0 means - not to use LSB first.
     *  In order to use LSB first, argument should be > 0
     */
    i = 0;
    wr_retval = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &i);
    rd_retval = ioctl(fd, SPI_IOC_RD_LSB_FIRST, &i);
    if((wr_retval < 0) || (rd_retval < 0)) {
	perror("ioctl: set MSB first");
	return -1;
    }
    /*! setting SPI to 8 bits per word
     */
    bits = 8;
    wr_retval = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    rd_retval = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if((wr_retval < 0) || (rd_retval < 0)) {
	perror("ioctl: set bits per word");
	return -1;
    }
    return 0;
}

static void do_transfer(int fd)
{
    int ret;
    unsigned int tx;
    unsigned int rx;
    unsigned short cmd_buff;

    /*! read temperature */
    cmd_buff = 0x1;
    tx = 0;
    rx = 0;
    struct spi_ioc_transfer temp_tr[2] = {
	    [0] = {
		    .tx_buf = (unsigned long)&cmd_buff,
		    .len = 1,
		/*! we need CS to change */
		    .cs_change = 1,
		/*! wait after this transfer */    
		    .delay_usecs = 50,
		    .bits_per_word = 8,
	    },

	    [1] = {
		    .tx_buf = (unsigned long)&tx,
		    .rx_buf = (unsigned long)&rx,
		    .len = sizeof(tx),
		    .bits_per_word = 8,
	    }
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(2), &temp_tr);
    if(ret < 1) {
	perror("ioctl spi message");
	return;
    }

    printf("temperature value = %x\n", rx);
    printf("\n");

/*! read humidity */
    cmd_buff = 0x2;
    tx = 0;
    rx = 0;
    struct spi_ioc_transfer humi_tr[2] = {
	    [0] = {
		    .tx_buf = (unsigned long)&cmd_buff,
		    .len = 1,
		/*! we need CS to change */
		    .cs_change = 1,
		/*! wait after this transfer */    
		    .delay_usecs = 50,
		    .bits_per_word = 8,
	    },

	    [1] = {
		    .tx_buf = (unsigned long)&tx,
		    .rx_buf = (unsigned long)&rx,
		    .len = sizeof(tx),
		    .bits_per_word = 8,
	    }
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(2), &humi_tr);
    if(ret < 1) {
	perror("ioctl spi message");
	return;
    }

    printf(" humidity value = %x\n", rx);
    printf("\n");

 /*! read pressure */
    cmd_buff = 0x3;
    tx = 0;
    rx = 0;
    struct spi_ioc_transfer presr_tr[2] = {
	    [0] = {
		    .tx_buf = (unsigned long)&cmd_buff,
		    .len = 1,
		/*! we need CS to change */
		    .cs_change = 1,
		/*! wait after this transfer */    
		    .delay_usecs = 50,
		    .bits_per_word = 8,
	    },

	    [1] = {
		    .tx_buf = (unsigned long)&tx,
		    .rx_buf = (unsigned long)&rx,
		    .len = sizeof(tx),
		    .bits_per_word = 8,
	    }
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(2), &presr_tr);
    if(ret < 1) {
	perror("ioctl spi message");
	return;
    }

    printf(" pressure value  = %x\n", rx);
    printf("\n");
}

int main(void)
{
     char *device = "/dev/spidev0.0";
     int fd;
     int error;

     fd = open(device, O_RDWR);
     if(fd < 0) {
	perror("open spidev");
	return -1;
     }

     error = spi_device_setup(fd);
     if(error)
	     return -1;
     
     do_transfer(fd);
     close(fd);
     return 0;
}
