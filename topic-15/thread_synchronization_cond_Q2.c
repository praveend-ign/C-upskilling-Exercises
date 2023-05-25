#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>

pthread_mutex_t lock;
int count;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void *increment_thread(void *arg) {
	while(count < 10) {
		count++;
		printf("increment thread: count = %d\n", count);
	}
	pthread_mutex_lock(&lock);
	pthread_cond_signal(&cond2);
	pthread_cond_wait(&cond1,&lock);
	pthread_mutex_unlock(&lock);
	printf("inc reached here\n");
	pthread_exit(NULL);
}

void *decrement_thread(void *arg) {
	pthread_mutex_lock(&lock);
	pthread_cond_signal(&cond1);
	pthread_cond_wait(&cond2,&lock);
	pthread_mutex_unlock(&lock);
	while(count > 0) {
		printf("decrement thread: count = %d\n", count);
		count--;
	}
	pthread_exit(NULL);
}

int main(void) {
	pthread_t thread_id,thread_id1;
	int ret;
	void *res;

	count = 0;
	ret = pthread_mutex_init(&lock, NULL);
	if(ret != 0) {
		perror("pthread mutex init");
		return -1;
	}
	ret = pthread_create(&thread_id,NULL,increment_thread,NULL);
	if(ret != 0) {
		perror("pthread create");
		return -1;
	}
	ret = pthread_create(&thread_id1,NULL,decrement_thread,NULL);
	if(ret != 0) {
		perror("pthread 1 create");
		return -1;
	}
	printf("Created threads\n");
	ret = pthread_join(thread_id,&res);
	if(ret != 0)
		perror("thread 1 join");
	printf("thread joined\n");
	ret = pthread_join(thread_id1,&res);
	if(ret != 0)
		perror("thread 2 join");
	printf("threads joined\n");
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_mutex_destroy(&lock);
	return 0;
}

