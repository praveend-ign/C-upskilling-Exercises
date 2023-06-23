/*! program to do transmit and
 *  receive data from the user
 *  application to dummy spi slave
 *  device using spidev interface.
 *  The data is in the format of a
 *  16-bit command followed by a 32-bit
 *  payload. The command can be one of the
 *  following: 0x0001 (read temperature),
 *  0x0002 (read humidity), 
 *  0x0003 (read pressure),
 *  0x0004 (write configuration), and 
 *  0x0005 (reset device)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/*! function which sends ioctl
 *  commands to configure virtual
 *  spi slave device
 */
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

/*! function which sends spi message
 *  in multiple of spi trnasfers. each
 *  spi message contains two transfers i.e.
 *  16-bit command and 32-bit payload
 */
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
 
   /*! write configuration */
    cmd_buff = 0x4;
  /*! arbitrary configuration value */
    tx = 0x4512;
    rx = 0;
    struct spi_ioc_transfer wrconfig_tr[2] = {
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

    ret = ioctl(fd, SPI_IOC_MESSAGE(2), &wrconfig_tr);
    if(ret < 1) {
	perror("ioctl spi message");
	return;
    }

  /*! reset device */
    cmd_buff = 0x5;
    tx = 0;
    rx = 0;
    struct spi_ioc_transfer resetcmd_tr[2] = {
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

    ret = ioctl(fd, SPI_IOC_MESSAGE(2), &resetcmd_tr);
    if(ret < 1) {
	perror("ioctl spi message");
	return;
    }

}

int main(int argc, char *argv[])
{
     char *device;
     int fd;
     int error;

     if(argc == 1) {
	printf("provide spislave device name\n");
	return -1;
     }
     device = argv[1];
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
