/*! program to write data using
 *  shared memory ipc mechanism
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SHM_KEY 0x1234

struct shmseg {
   int flag;
   int value;
};

int main(int argc, char *argv[]) {
   int shmid;
   struct shmseg *shmp;
   int data;
   int running = 1;
   
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   
   /*! Attach to the segment to get a pointer to it.*/
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
   
   /* Transfer data to shared memory */
   printf("waiting for consumer to be ready\n");
   while(running) {
	while(shmp->flag == 1) {
		sleep(1);
	}	
   	printf("Enter any value to send data (-1 to exit):\n");
	scanf("%d", &data);
   	shmp->value = data;
      	shmp->flag = 1;
      	/*printf("Writing Process: Shared Memory Write: Wrote %d value\n", shmp->value);*/
	if(data == -1)
		running = 0;
   }

   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
   printf("Writing Process: Complete\n");
   return 0;
}
