/*! program to read message via named pipe
 * i.e. mkfifo() api
 */ 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE	48 

int main(int argc, char *argv[])
{
	int pipe_fd;
	int res;
	int open_mode = O_RDONLY;
	char buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;

	if(argc < 2) {
                printf("provide fifo name as an argument\n");
                return -1;
        }
	memset(buffer, '\0', sizeof(buffer));
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	pipe_fd = open(argv[1], open_mode);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) {
		printf("received messages from another program:\n");
		do {
			res = read(pipe_fd, buffer, BUFFER_SIZE);
			printf("%s\n", buffer);
			bytes_read += res;
		} while (res > 0);
		(void)close(pipe_fd);
	}
	else {
		printf("unable to open named pipe: %s\n", argv[1]);  
		return -1;
	}
	printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
	return 0;
}

