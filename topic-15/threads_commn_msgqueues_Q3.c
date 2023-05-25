/*! program to demonstrate the two threads
 *  communication using message queues
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MAX_SIZE                10
#define RANDOM_INT_RANGE        2000
#define MSGQUEUE_NAME		"/MQ_PROD_CONS_THREAD"
#define QUEUE_PERMISSIONS 	0660
#define MAX_MESSAGES 		10
#define MAX_MSG_SIZE 		64

mqd_t prod_mq, cons_mq;

/*! function to produce data to message queue
 */ 
void *producer_fn(void *arg)
{
     int i;
     int retval;
     int random_data[MAX_SIZE];
     struct mq_attr attr;

     srand(getpid());
     for (i = 0; i < MAX_SIZE; i++) {
     	random_data[i] = rand() % RANDOM_INT_RANGE;
	printf(":%d ", random_data[i]);
     }
     mq_getattr(cons_mq, &attr);
     retval = mq_send(prod_mq, (char *)random_data, attr.mq_msgsize, 0);
     if(retval != 0)
	     perror("producer mq_send");

     printf("\n");
     pthread_exit(random_data);
}

/*! function to consume data from the
 * message queue
 */
void *consumer_fn(void *arg)
{
     int i, retval;
     int recvd_data[MAX_SIZE];
     int msg_prio = 0;
     struct mq_attr attr;

     mq_getattr(cons_mq, &attr);
     retval = mq_receive(cons_mq, (char *)recvd_data, attr.mq_msgsize, &msg_prio);
     if(retval < 0) {
	     perror("consumer mq_receive");
     } else {
	     printf("received data from producer:\n");
	     for(i=0;i<MAX_SIZE;i++)
	     	printf("\t%d",recvd_data[i]);
    }
     printf("\n");
     pthread_exit(NULL);
}

int main(void)
{
    int ret;
    void *thread_result;    
    pthread_t thread_one, thread_two;
    struct mq_attr attr;
    
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    cons_mq = mq_open(MSGQUEUE_NAME, O_RDONLY | O_CREAT,
		    QUEUE_PERMISSIONS, &attr);
    if(cons_mq < 0) {
	perror("consumer: mq_open");
	exit(EXIT_FAILURE);
    }

    /*! create message queue with same name as that of
     *  the consumer
     */
    prod_mq = mq_open(MSGQUEUE_NAME, O_WRONLY);
    if(prod_mq < 0) {
	perror("producer: mq_open");
	exit(EXIT_FAILURE);
    }
    
    ret = pthread_create(&thread_one, NULL, producer_fn, NULL);
    if(ret != 0) {
	perror("producer thread");
	exit(EXIT_FAILURE);
    } 
    ret = pthread_create(&thread_two, NULL, consumer_fn, NULL);
    if(ret != 0) {
        perror("consumer thread");
        exit(EXIT_FAILURE);
    }

    printf("waiting for threads to finish\n");
    ret = pthread_join(thread_one, &thread_result);
    if(ret != 0)
	perror("producer thread joined");
    ret = pthread_join(thread_two, NULL);
    if(ret != 0)
        perror("consumer thread joined");
    mq_close(prod_mq);
    mq_close(cons_mq);
    mq_unlink((char *)thread_result);
    return 0;
}
