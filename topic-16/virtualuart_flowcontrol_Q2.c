/*! program to send and receive data 
 *  with flow control mechanism i.e.
 *  RTS/CTS signals to virtual uart device
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_DATA_SIZE		64
#define VIRT_UARTDEV            "/dev/ttyAB0"

#define TRUE		1
#define FALSE		0

/*! for transmitting one byte data and if
 * baudrate is 9600 bps then the delay 
 * required in microseconds
 */ 
#define DELAY_9600BAUD_ONEBYTE			833

/*! for transmitting 48 bytes data and if
 * baudrate is 9600 bps then the delay 
 * required in microseconds
 */ 
#define DELAY_9600BAUD_FORTYEIGHTBYTE		40000

/*! for transmitting one byte data and if
 * baudrate is 115200 bps then the delay 
 * required in microseconds
 */ 
#define DELAY_115200BAUD_ONEBYTE		69	

/*! for transmitting 48 bytes data and if
 * baudrate is 115200 bps then the delay 
 * required in microseconds
 */ 
#define DELAY_115200BAUD_FORTYEIGHTBYTE		3333


char vuart_txbuf[MAX_DATA_SIZE];
char vuart_rxbuf[MAX_DATA_SIZE];

/*! function for raising rts signal and
 *  check the cts from the receiver
 */
int flow_control_rts(int fd)
{
	int rts_signal;
	int rts_response = 0;
	int bytes_transferred;

	rts_signal = 1;
	usleep(DELAY_115200BAUD_ONEBYTE);
	bytes_transferred = write(fd, &rts_signal, 1);
	if(bytes_transferred < 0)
		perror("rts-signal");
	if(bytes_transferred == 1) {
		usleep(DELAY_115200BAUD_ONEBYTE);
		bytes_transferred = read(fd, &rts_response, 1);
		if(bytes_transferred < 0)
			perror("rts_response");
		if((bytes_transferred > 0) && (rts_response == 1)) {
			return TRUE;
		}
	}
	return FALSE;
}

/*! function for asserting cts signal if
 *  rts signal is received from the 
 *  transmitter
 */
int flow_control_cts(int fd)
{
	int cts_signal = 0;
	int cts_resp;
	int bytes_transferred;

	usleep(DELAY_115200BAUD_ONEBYTE);
	bytes_transferred = read(fd, &cts_signal, 1);
	if((bytes_transferred > 0) && (cts_signal == 1)) {
		cts_resp = 1;
		usleep(DELAY_115200BAUD_ONEBYTE);
		bytes_transferred = write(fd, &cts_resp, 1);
		if(bytes_transferred < 0)
			perror("cts_resp");
		if(bytes_transferred == 1)
			return TRUE;
	} else if(bytes_transferred < 0) {
		perror("cts_signal");
	} else {
		printf("invalid: cts_signal = %d\n", cts_signal);
	}
	return FALSE;
}

/*! function to transmit data to
 *  virtual uart device
 */
void transmit_data(int fd, char *input_data)
{
        int len;
        int bytes_written;

        len = strlen(input_data);
	usleep(DELAY_115200BAUD_FORTYEIGHTBYTE);
        bytes_written = write(fd, input_data, len);
	if(bytes_written < 0)
		perror("transmit_data");
        printf("number of bytes written to virtual uart"
                        "device = %d\n", bytes_written);
}

/*! function to receive data from
 *  the virtual uart device
 */
void receive_data(int fd, char *output_buf)
{
        int bytes_read;

	usleep(DELAY_115200BAUD_FORTYEIGHTBYTE);
        bytes_read = read(fd, output_buf, MAX_DATA_SIZE);
	if(bytes_read < 0)
		perror("receive_data");
        printf("bytes read from virtual uart device = %d\n",
                        bytes_read);
	if(bytes_read > 0)
		printf("rcvd data = %s\n", output_buf);
}

int main(void)
{
	pid_t pid;
        int wstatus;

	memset(vuart_txbuf, 0, MAX_DATA_SIZE);
	memset(vuart_rxbuf, 0, MAX_DATA_SIZE);
        pid = fork();
        if(pid == 0) {
        /*! child process */
		int rts_ok;
		int fd;
		
		strcpy(vuart_txbuf, "virtual uart data transmission with flow control");
		fd = open(VIRT_UARTDEV, O_RDWR);
        	if(fd == -1) {
                	perror("open for transmit");
                	return -1;
        	}
		rts_ok = flow_control_rts(fd);
		if(rts_ok == TRUE) {
			transmit_data(fd, vuart_txbuf);
		} else {
			printf("rts signal not received\n");
		}
		close(fd);
	} else {
		/*! parent process */
		int cts_signal = 0;
		int fd;

		fd = open(VIRT_UARTDEV, O_RDWR);
                if(fd == -1) {
                        perror("open for receive");
                } else {
			cts_signal = flow_control_cts(fd);
			if(cts_signal == TRUE) {
				receive_data(fd, vuart_rxbuf);
			} else {
				printf("cts transmit failed\n");
			}
		}
		close(fd);
	}
	/*! wait for any child process to finish */
        waitpid(-1, &wstatus, 0);
	return 0;
}
