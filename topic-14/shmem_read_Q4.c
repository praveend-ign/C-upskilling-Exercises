/*! program to read data using
 *  shared memory ipc mechanism
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define SHM_KEY 0x1234

struct shmseg {
   int flag;
   int value;
};

int main(void) {
   int shmid;
   struct shmseg *shmp;
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
 
   /* Transfer data from shared memory to stdout*/
   while (running) {
      if (shmp->flag == 1) {
         printf("received data: %d\n", shmp->value);
	 shmp->flag = 0;
	 if(shmp->value == -1)
		 running = 0;
      }
      sleep(1);
   }
   printf("Reading Process: Reading Done, Detaching Shared Memory\n");
   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }
   printf("Reading Process: Complete\n");
   return 0;
}
