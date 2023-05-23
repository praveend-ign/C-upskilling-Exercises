/*! program to write a message via named pipe
 *  i.e. mkfifo() api 
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE	48
#define TEN_MEG 	(1024 * 1024 * 10)
#define ONE_KILO	1024 

int main(int argc, char *argv[])
{
	int pipe_fd;
	int res;
	int open_mode = O_WRONLY;
	int bytes_sent = 0;
	char buffer[BUFFER_SIZE + 1];

	if(argc < 2) {
		printf("provide fifo name as an argument\n");
		return -1;
	}
	res = mkfifo(argv[1], 0777);
	if (res != 0) {
		printf("Could not create fifo %s\n", argv[1]);
		return -1;
	}
	printf("Process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(argv[1], O_WRONLY);
	printf("Process %d result %d\n", getpid(), pipe_fd);

	if (pipe_fd != -1) {
		while(bytes_sent < TEN_MEG) {
			sprintf(buffer, "writing %d KB buffer of 10 MB", bytes_sent/ONE_KILO);
			res = write(pipe_fd, buffer, BUFFER_SIZE);
			if (res == -1) {
				printf("Write error on pipe\n");
				return -1;
			}
			bytes_sent += res;
		}
		(void)close(pipe_fd);
		unlink(argv[1]);
	}
	else {
		return -1;
	}
	printf("Process %d finished\n", getpid());
	return 0;
}
