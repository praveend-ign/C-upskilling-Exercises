/*! program to send to virtual uart device
 *  and receive data in an interrupt-driven
 *  method and storing the data in circular
 *  buffer
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_DATA_SIZE		64
#define VIRT_UARTDEV            "/dev/ttyAB0"

#define		SIZE_OF_BUFFER		    8

/*! circular buffer data structure */
static char circularBuffer[SIZE_OF_BUFFER][MAX_DATA_SIZE];
int readIndex =	0;
int printIndex = 0;

static int tx_flag;
static int rx_flag; 

/*! function to transmit data to
 *  virtual uart device
 */
void transmit_data(int fd, char *input_data)
{
        int len;
        int bytes_written;

        len = strlen(input_data);
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

        bytes_read = read(fd, output_buf, MAX_DATA_SIZE);
        if(bytes_read < 0)
                perror("receive_data");
        if(bytes_read > 0) {
		printf("received %d bytes of data\n", bytes_read);
	}
}

/*! function to print the contents
 *  of circular buffer if any received data
 *  is stored into it
 */
void print_circbuffer(void)
{
	if((printIndex < readIndex) || (printIndex < SIZE_OF_BUFFER)) {
		printf("circular buffer contents = %s\n", circularBuffer[printIndex]);
		printIndex++;
		if(printIndex >= SIZE_OF_BUFFER)
			printIndex = 0;
	}
}

/*! SIGIO signal handler function for transmit 
 * complete signal from virtual uart device
 */
void vuart_sigIO_txhandler(int signum)
{
    printf("signal %d received\n", signum);
    tx_flag = 1;
}

/*! SIGIO signal handler function for 
 * data received signal from virtual uart 
 * device
 */
void vuart_sigIO_rxhandler(int signum)
{
    printf("signal %d received\n", signum);
    rx_flag = 1;
}

/*! reentrant function to enable signal IO
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

int main(void)
{
	pid_t pid;
        int wstatus;

        pid = fork();
        if(pid == 0) {
        /*! child process */
		int fd;
		int sig, retval;
		char *string;
		struct sigaction sig_act;

		sig = SIGIO;
    		sig_act.sa_handler = vuart_sigIO_txhandler;
    		sigemptyset(&sig_act.sa_mask);
    		sig_act.sa_flags = SA_RESTART;
    		retval = sigaction(sig, &sig_act, 0);
    		if(retval < 0) {
        		perror("sigaction error");
        		return -1;
    		}
		fd = open(VIRT_UARTDEV, O_WRONLY);
                if(fd == -1) {
                        perror("open for transmit");
                        return -1;
                }
		/*! enable SIGIO for write transactions */
		retval = register_signalIO(fd);
		if(retval < 0)
			printf("unable to register sigIO\n");
		string = (char *)malloc(MAX_DATA_SIZE);
		if(string == NULL) {
			printf("unable to alloc memory\n");
			return -1;
		}
		memset(string, 0, MAX_DATA_SIZE);
		retval = 0;
		strcpy(string, "sending initial text to virtual uart device");
		transmit_data(fd, string);
		while(1) {
			usleep(100000);
			if(tx_flag == 1) {
				tx_flag = 0;
				sprintf(string, "sending a text along with count %d", retval); 
				transmit_data(fd, string);
				retval++;
			}
		}
		close(fd);
	} else {
	/*! parent process */
		int fd;
		int sig, retval;
		struct sigaction sig_act;

                sig = SIGIO;
                sig_act.sa_handler = vuart_sigIO_rxhandler;
                sigemptyset(&sig_act.sa_mask);
                sig_act.sa_flags = SA_RESTART;
                retval = sigaction(sig, &sig_act, 0);
                if(retval < 0) {
                        perror("sigaction error");
                } else {
			fd = open(VIRT_UARTDEV, O_RDONLY);
                	if(fd == -1) {
                        	perror("open for receive");
               	 	} else {
				retval = register_signalIO(fd);
                		if(retval < 0)
                        		printf("parent:unable to register sigIO\n");
				while(1) {
					usleep(100000);
					if(rx_flag == 1) {
						rx_flag = 0;
						receive_data(fd, circularBuffer[readIndex]);
					        readIndex++;
						if(readIndex == SIZE_OF_BUFFER)
							readIndex = 0;
						print_circbuffer();
					}
				}
			}
		}
		close(fd);
	}
	/*! wait for any child process to finish */
	waitpid(-1, &wstatus, 0);
	return 0;
}
