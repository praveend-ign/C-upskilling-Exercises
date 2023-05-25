/*! program to use thread synchronisation
 *  mechanism to make a function thread-safe
 *  so that multiple threads can call the
 *  function without corrupting the resource
 *  accessed
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t transaction_lock;
int balance = 1000;

/*! function is defined to be 
 *  thread-safe as balance variable
 *  is accessed using mutex protection lock
 */ 
void deposit(int amount)
{
    pthread_mutex_lock(&transaction_lock);
    balance += amount;
    pthread_mutex_unlock(&transaction_lock);
    printf("new balance = %d\n", balance);
}

/*! thread function for transaction
 */
void *transaction_one(void *arg)
{
	int i;

	for(i=0;i<5;i++)
		deposit(100);

	pthread_exit(NULL);
}

/*! thread function for another
 *  transaction
 */
void *transaction_two(void *arg)
{
	int i;

	for(i=0;i<5;i++)
		deposit(200);

	pthread_exit(NULL);
}

int main(void)
{
    int ret;
    pthread_t thread_one, thread_two;

    ret = pthread_mutex_init(&transaction_lock, NULL);
    if(ret != 0) {
          perror("pthread mutex init");
          return -1;
    }
    ret = pthread_create(&thread_one, NULL, transaction_one, NULL);
    if(ret != 0) {
        perror("producer thread");
        exit(EXIT_FAILURE);
    }
    ret = pthread_create(&thread_two, NULL, transaction_two, NULL);
    if(ret != 0) {
        perror("consumer thread");
        exit(EXIT_FAILURE);
    }

    printf("waiting for threads to finish\n");
    ret = pthread_join(thread_one, NULL);
    if(ret != 0)
        perror("producer thread join");
    ret = pthread_join(thread_two, NULL);
    if(ret != 0)
        perror("consumer thread join");
    printf("final balance = %d\n", balance);
    return 0;
}

