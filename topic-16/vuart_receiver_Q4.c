/*! program to receive data from virtual
 *  uart device which consists of header,
 *  payload and checksum (calculated using
 *  a CRC-16 algorithm
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

typedef unsigned short   uint16_t;

#define POLY 			0x8408
#define VUART_DEV		"/dev/ttyAB0"
#define MAX_DATA_SIZE		128

char read_buf[MAX_DATA_SIZE];
static int fd;

/*! function to calculate crc from
 *  the 16 bit generator polynomial
 */
uint16_t crc16(char *data_p, uint16_t length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8; 
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | ((data >> 8) & 0xff);

      return (crc);
}

/*! function to check for any errors
 *  using crc-16 algorithm
 */ 
void process_data(int num_bytes)
{
	uint16_t remainder;

	/*! received data with crc code is again
	 *  performed crc calculation to check the 
	 *  crc value
	 */ 
	remainder = crc16(read_buf, num_bytes);
	if(remainder == 0) {
		printf("no error detected\n");
	} else {
		printf("error detected in transmission\n");
	}
}

/*! signal handler function to close virtual
 *  uart device
 */
void sig_handler(int sig)
{
	printf("received signal closing fd\n");
	if(fd > 0)
		close(fd);
}

int main(void)
{
    int bytes_read;
    struct sigaction act;

    fd = open(VUART_DEV, O_RDONLY);
    if(fd < 0) {
	perror("virtual uart open readonly");
	return -1;
    }

    /*! register signal handler to close virtual
     *  uart device if the program is aborted
     */ 
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    while(1) {
    	bytes_read = read(fd, read_buf, MAX_DATA_SIZE);
	if(bytes_read > 0) {
		process_data(bytes_read);
	} else if(bytes_read < 0) {
		perror("read failed");
		break;
	}
	/*! read data again after 100 msec duration */
	usleep(100000);
    }

    close(fd);
    return 0;
}
