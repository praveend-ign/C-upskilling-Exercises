/*! program to demonstrate the communication
 *  between two processes using unamed pipes
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE		64

int main(void)
{
    int data_processed;
    int fd_pipes[2];
    const char data_buf[] = "inter process communication using pipe function";
    char rcvd_buf[BUFSIZE + 1];
    pid_t fork_result;

    memset(rcvd_buf, '\0', sizeof(rcvd_buf));

    if(pipe(fd_pipes) == 0) {
	/*! creates child process */
	fork_result = fork();
	if(fork_result == -1) {
		printf("unable to fork\n");
		return -1;
	}
	if(fork_result == 0) {
	/*! child process */
		data_processed = read(fd_pipes[0], rcvd_buf, BUFSIZE);
		printf("read %d bytes: %s\n", data_processed, rcvd_buf);
		close(fd_pipes[0]);
	} else {
	/*! parent process */
		data_processed = write(fd_pipes[1], data_buf, strlen(data_buf));
		printf("Wrote %d bytes\n", data_processed);
		close(fd_pipes[1]);
	}
    }
    return 0;
}
