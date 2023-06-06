/*! program to open any i2c adapter using
 *  i2c-dev interface kernel driver and
 *  communicate with a virtual i2c device
 *  through the above i2c adapter
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/*! virtual i2c client device */ 
#define LED_DRIVER_I2C_ADDR	0x20

int main(void)
{
	int i2c_adapt_fd;
	int i2c_client_addr;

	/*! open the i2c master controller */
	i2c_adapt_fd = open("/dev/i2c-14", O_RDWR); 
	if(i2c_adapt_fd < 0) {
		perror("i2c-14 adapter open");
		exit(1);
	}

	i2c_client_addr = LED_DRIVER_I2C_ADDR;
	/*! specify i2c client address to communicate with */ 
	if(ioctl(i2c_adapt_fd, I2C_SLAVE, i2c_client_addr) < 0) {
	      perror("ioctl I2C_SLAVE");
	      close(i2c_adapt_fd);
	      exit(2);
	}

	close(i2c_adapt_fd);
	return 0;
}

