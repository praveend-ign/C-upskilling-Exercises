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
#include <signal.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define MAX_BUF_SIZE		256

static int trans_flag;
static unsigned char circBuf[MAX_BUF_SIZE];
static int readIndex;
static char buf[32];

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
 *  in multiple of spi transfers. each
 *  spi message contains two transfers i.e.
 *  16-bit command and 32-bit payload
 */
static void do_transfer(int fd)
{
    int i, ret;
    unsigned int tx;
    unsigned int rx;
    unsigned short cmd_buff;
    int len;

    /*! read temperature */
    cmd_buff = 0x01;
    rx = 0;
    ret = write(fd, &cmd_buff, sizeof(cmd_buff));
    if(ret < 0) {
	perror("write");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    trans_flag = 0;
    ret = read(fd, &rx, sizeof(rx));
    if(ret < 0) {
	perror("read");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    trans_flag = 0;

    for(i=0;i<sizeof(rx);i++) {
	    circBuf[i] = (rx & (0xFF << i)) >> i;
	    readIndex++;
	    if(readIndex == MAX_BUF_SIZE)
		    readIndex = 0;
    }

    printf("temperature value = %x\n", rx);
    printf("\n");

/*! read humidity */
    cmd_buff = 0x02;
    rx = 0;
    ret = write(fd, &cmd_buff, sizeof(cmd_buff));
    if(ret < 0) {
	perror("write");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    trans_flag = 0;
    ret = read(fd, &rx, sizeof(rx));
    if(ret < 0) {
	perror("read");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    trans_flag = 0;
    for(i=0;i<sizeof(rx);i++) {
	    circBuf[i] = (rx & (0xFF << i)) >> i;
	    readIndex++;
	    if(readIndex == MAX_BUF_SIZE)
		    readIndex = 0;
    }

    printf(" humidity value = %x\n", rx);
    printf("\n");

 /*! read pressure */
    cmd_buff = 0x03;
    rx = 0;
    ret = write(fd, &cmd_buff, sizeof(cmd_buff));
    if(ret < 0) {
	perror("write");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    trans_flag = 0;
    ret = read(fd, &rx, sizeof(rx));
    if(ret < 0) {
	perror("read");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    trans_flag = 0;
    for(i=0;i<sizeof(rx);i++) {
	    circBuf[i] = (rx & (0xFF << i)) >> i;
	    readIndex++;
	    if(readIndex == MAX_BUF_SIZE)
		    readIndex = 0;
    }

    printf(" pressure value  = %x\n", rx);
    printf("\n");
 
   /*! write configuration */
    cmd_buff = 0x04;
   /*! arbitrary configuration value */
    tx = 0x3418;
    memcpy(buf, &cmd_buff, sizeof(cmd_buff));
    memcpy(buf + sizeof(cmd_buff), &tx, sizeof(tx));
    len = sizeof(cmd_buff) + sizeof(tx);
    ret = write(fd, buf, len);
    if(ret < 0) {
	perror("write");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    /*! write config command along with data is
     *  sent successfully
     */ 
    trans_flag = 0;


  /*! reset device */
    cmd_buff = 0x5;
    len = sizeof(cmd_buff);
    ret = write(fd, &cmd_buff, len);
    if(ret < 0) {
	perror("write");
	return;
    }
    while(!trans_flag) {
	/*! 100 msec delay before checking data */
	usleep(100000);
    }
    /*! write config command along with data is
     *  sent successfully
     */ 
    trans_flag = 0;

}

/*! signal handler function for I/O
 *  possible signal from virtual spi
 *  device
 */
void spi_sigIO_rxhandler(int signum)
{
	printf("signal %d received\n", signum);
    /*! set the transaction flag */
	trans_flag = 1;
}

/*! function to enable signal IO
 *  using fcntl() system call to open file
 *  descriptor
 */
int register_signalIO(int fd)
{
        int flags;

        /*! Set owner process that is to receive "I/O possible" signal */
        if(fcntl(fd, F_SETOWN, getpid()) == -1) {
                perror("fcntl F_SETOWN");
                return -1;
        }
        flags = fcntl(fd, F_GETFL);
        /*! Enable "I/O possible" signaling */
        if(fcntl(fd, F_SETFL, flags | O_ASYNC) == -1) {
                perror("fcntl F_SETFL");
                return -1;
        }
        return 0;
}

int main(int argc, char *argv[])
{
     char *device;
     int fd;
     int error;
     int sig, retval;
     struct sigaction sig_act;

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

    /*! register signal handler for I/O
     *  possible signal for this process
     */ 
     sig = SIGIO;
     sig_act.sa_handler = spi_sigIO_rxhandler;
     sigemptyset(&sig_act.sa_mask);
     sig_act.sa_flags = SA_RESTART;
     retval = sigaction(sig, &sig_act, 0);
     if(retval < 0) {
            perror("sigaction error");
            return -1;
     }

     /*! enable SIGIO for receiving data */
     retval = register_signalIO(fd);
     if(retval < 0)
           printf("unable to register sigIO\n");

     do_transfer(fd);
     close(fd);
     return 0;
}
