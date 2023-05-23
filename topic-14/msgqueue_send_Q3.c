/*! program to send data using message
 *  queue ipc mechanism
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

#define MAX_TEXT 	512
#define BUFSIZE		72	

struct msgqueue_st {
	long int msg_type;
	char text[MAX_TEXT];
};

int main(int argc, char *argv[])
{
	int running = 1;
	struct msgqueue_st data;
	int msgid;
	char buffer[BUFSIZE];
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
	printf("sender side: msg id = 0x%x\n", msgid);
	while(running) {
		printf("Enter some text: ");
		fgets(buffer, BUFSIZE, stdin);
		data.msg_type = 1;
		strcpy(data.text, buffer);
		if (msgsnd(msgid, (void *)&data, BUFSIZE, 0) == -1) {
			printf("msgsnd failed\n");
			running = 0;
		}
		if (strncmp(buffer, "end", 3) == 0) {
			running = 0;
		}
	}
	if(msgctl(msgid, IPC_RMID, 0) == -1) {
		printf("msgctl(IPC_RMID) failed\n");
	}
	return 0;
}
