/*! program to receive data using
 *  message queue ipc mechanism
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

#define BUFSIZE		72

struct msgqueue_st {
	long int msg_type;
	char text[BUFSIZE];
};

int main(int argc, char *argv[])
{
	int running = 1;
	int msgid;
	struct msgqueue_st data;
	long int msg_to_receive = 1;
	key_t key;

	if(argc < 2) {
		printf("provide key to msgget function\n");
		return 0;
	}
/*! base 10 conversion i.e. decimal */
	key = strtol(argv[1], NULL, 10);
	
/*! To distinguish success/failure after call */
	errno = 0;
	if ((errno == ERANGE) || (errno == EINVAL) ||
			(errno != 0 && key == 0)) {
               perror("strtol");
               return -1;
        }
	printf("key = %d\n", key);
	msgid = msgget(key, 0666 | IPC_CREAT);
	if (msgid == -1) {
		printf("msgget failed with error: %d\n", errno);
		return -1;
	}
	printf("rcv side: msg id = 0x%x\n", msgid);
	while(running) {
		if (msgrcv(msgid, (void *)&data, BUFSIZE,
			msg_to_receive, 0) == -1) {
			printf("msgrcv failed with error: %d\n", errno);
			running = 0;
		} else {
			printf("data received: %s\n", data.text);
		}
		if (strncmp(data.text, "end", 3) == 0) {
			running = 0;
		}
	}
	if (msgctl(msgid, IPC_RMID, 0) == -1) {
		printf("msgctl(IPC_RMID) failed\n");
		return -1;
	}
	return 0;
}
