#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define MUTEX_KEY 		0x521
#define EMPTY_COUNT_KEY		0x123
#define FILL_COUNT_KEY		0x678

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};



#define MAX_SIZE		10
#define RANDOM_INT_RANGE	5000

int random_data[MAX_SIZE];
union semun mutex_union;
union semun emptycount_u;
union semun fillcount_u;
int array_index;
int array_print_index;

int create_semaphore(int key, union semun sem_un)
{
    int sem_id;

    sem_id = semget(key, 1, 0666 | IPC_CREAT);
    if(sem_id < 0)
    {
        perror("semget");
	return -1;
    }
    if(semctl(sem_id, 0, SETVAL, sem_un) < 0)
    {
        perror("semctl");
	return -1;
    }
    return sem_id;
}

int main()
{
    int pid, proc_pid;
    int mutex_id;
    int empty_count, fill_count;
    int i, j;

    array_index = 0;
    array_print_index = 0;
   /*! binary semaphore for exclusive access to
    * the resource i.e. random_data. 
    * value of 1 indicates unlocked
    */
    mutex_union.val = 1;
    mutex_id = create_semaphore(MUTEX_KEY, mutex_union);
    if(mutex_id < 0) {
	return -1;
    }
    /*! empty_count is counting semaphore initialized to 
     *  maximum array size of data i.e.
     *  all the array elements of random_data are available initially 
     */
    emptycount_u.val = MAX_SIZE;
    empty_count = create_semaphore(EMPTY_COUNT_KEY, emptycount_u);
    if(empty_count < 0) {
	return -1;
    }

    /*! counting semaphore initialized to 0
     *  value of 0 indicates zero array elements of random_data  
     *  available initially
     */
    fillcount_u.val = 0;
    fill_count = create_semaphore(FILL_COUNT_KEY, fillcount_u);
    if(fill_count < 0) {
	return -1;
    }

    pid =  fork();
    srand(pid);
    if(pid < 0)
    {
        perror("fork");
	return -1;
    }
    else if(pid)
    {
    /*! parent process */
	proc_pid = fork(); 
	if(proc_pid < 0)
    	{
        	perror("second fork");
        	return -1;
    	}
	else if(proc_pid == 0)
	{
		struct sembuf p = { 0, -1, 0};
		struct sembuf v = { 0, 1, 0};
		/*! second child process */
		int i;
		printf("data written:\n");
		
        	for(i = 0; i < MAX_SIZE; ++i)
        	{
			p.sem_op = -1;
			if(semop(empty_count, &p, 1) < 0)
            		{
                		perror("semop p 1");
				return -1;
            		}
			p.sem_op = -1;
	   		if(semop(mutex_id, &p, 1) < 0)
            		{
                		perror("semop p 2");
				return -1;
            		}
			j = array_index;
			array_index++;
			if(array_index == MAX_SIZE)
				array_index = 0;
			v.sem_op = 1;
			if(semop(mutex_id, &v, 1) < 0)
            		{
                		perror("semop v 3");
				return -1;
            		}
            		random_data[j] = rand() % RANDOM_INT_RANGE;
			printf(":%d ", random_data[i]);
			v.sem_op = 1;
			if(semop(fill_count, &v, 1) < 0)
            		{
                		perror("semop v 4");
				return -1;
            		}
            		//sleep(1);
        	}
	}
    }
    else
    {
    /*! first child process */
	struct sembuf p = { 0, -1, 0};
	struct sembuf v = { 0, 1, 0};
        int i;
	printf("data read from another child process:\n");
	
        for(i = 0; i < MAX_SIZE; ++i)
        {
	    p.sem_op = -1;
	    if(semop(fill_count, &p, 1) < 0)
            {
                perror("semop p 5");
                return -1;
            }
	    p.sem_op = -1;
	    if(semop(mutex_id, &p, 1) < 0)
            {
                perror("semop p");
                return -1;
            }
            printf("\t%d", random_data[array_print_index]);
	    array_print_index++;
	    if(array_print_index == MAX_SIZE)
		    array_print_index = 0;
	    v.sem_op = 1;
	    if(semop(mutex_id, &v, 1) < 0)
            {
                perror("semop v");
                return -1;
            } 
	    v.sem_op = 1;
	    if(semop(empty_count, &v, 1) < 0)
            {
                perror("semop v 6");
                return -1;
            }
            //sleep(1);
        }
	
    }
    
    if(semctl(mutex_id, 0, IPC_RMID, mutex_union) == -1)
	   printf("failed to delete mutex semaphore\n");
    
    if(semctl(empty_count, 0, IPC_RMID, emptycount_u) == -1)
	   printf("failed to delete empty count semaphore\n");

    if(semctl(fill_count, 0, IPC_RMID, fillcount_u) == -1)
	   printf("failed to delete buffer full count semaphore\n");
    
    printf("\n");
    return 0;
}
