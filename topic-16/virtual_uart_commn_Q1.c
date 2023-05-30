/*! program to send and receive a string
 * to a virtual uart device
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
#define VIRT_UARTDEV		"/dev/ttyAB0"

/*! function which encrypts or
 *  decrypts the given string using
 *  xor cipher method
 */
void encryptDecrypt(char *inpString)
{
    int i, len;
    char xorKey;

    if(inpString == NULL) {
	printf("input string is NULL\n");
	return;
    }
    /*! Define XOR key
     * Any character value will work
     */
    xorKey = 'P';
 
    len = strlen(inpString);
 
    /*! perform XOR operation of key
     * with every character in string
     */
    for (i = 0; i < len; i++)
    {
        inpString[i] = inpString[i] ^ xorKey;
        printf("%c",inpString[i]);
    }
    printf("\n");
}

/*! function to send data to
 *  virtual uart device
 */
void send_data(char *input_data)
{
	int fd;
	int len;
	int bytes_written;

	fd = open(VIRT_UARTDEV, /*O_ASYNC |*/ O_WRONLY);
	if(fd == -1) {
		perror("open write only");
		return;
	}
	len = strlen(input_data);
	bytes_written = write(fd, input_data, len);
	printf("number of bytes written to virtual uart"
			"device = %d\n", bytes_written);
	close(fd);
}

/*! function to receive data from
 *  the virtual uart device
 */
char *receive_data(void)
{
	int fd;
	int bytes_read;
	char *read_buf;

	fd = open(VIRT_UARTDEV, /*O_ASYNC |*/ O_RDONLY);
        if(fd == -1) {
                perror("open read only");
                return NULL;
        }
	read_buf = (char *)malloc(MAX_DATA_SIZE);
	if(read_buf == NULL) {
		printf("unable to alloc read_buf mem\n");
		return NULL;
	}
	bytes_read = read(fd, read_buf, MAX_DATA_SIZE);
	printf("bytes read from virtual uart device = %d\n",
			bytes_read);
	close(fd);
	return read_buf;
}

int main(void)
{
	pid_t pid;
	int wstatus;

	pid = fork();
	if(pid == 0) {
	/*! child process */
		char *string;
		string = (char *)malloc(MAX_DATA_SIZE);
		if(string == NULL) {
			printf("unable to alloc memory\n");
			return -1;
		}
		printf("Enter any string to be sent to virtual uart"
			" device:\n");
		scanf("%s", string);
		encryptDecrypt(string);
		send_data(string);
		free(string);
	} else {
		char *rcvd_string;
	/*! parent process */
		rcvd_string = receive_data();
		encryptDecrypt(rcvd_string);
		if(rcvd_string != NULL)
			free(rcvd_string);
	}
	/*! wait for any child process to finish */
	waitpid(-1, &wstatus, 0);
	return 0;
}
