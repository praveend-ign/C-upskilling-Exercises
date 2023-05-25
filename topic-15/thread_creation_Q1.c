/*! program to create four threads and
 * pass different arguments to threads
 * and print the return values of the 
 * thread functions. finally,join the
 * threads to free the thread resources
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *threadfunc_one(void *arg);
void *threadfunc_two(void *arg);
void *threadfunc_three(void *arg);
void *threadfunc_four(void *arg);
int threadone_retvalue;
int threadtwo_retvalue;
int threadthree_retvalue;
int threadfour_retvalue;

int main(void) {
	int res;
	pthread_t thread_one, thread_two, thread_three, thread_four;
	void *threadone_result;
        void *threadtwo_result;
       	void *threadthree_result;
	void *threadfour_result;
	int data_arg1, data_arg2, data_arg3, data_arg4;

	data_arg1 = 11; 
	res = pthread_create(&thread_one, NULL, threadfunc_one, (void *)&data_arg1);
	if (res != 0) {
		perror("Thread creation failed");
		return -1;
	}
	data_arg2 = 22; 
	res = pthread_create(&thread_two, NULL, threadfunc_two, (void *)&data_arg2);
	if (res != 0) {
		perror("Thread creation failed");
		return -1;
	}
	data_arg3 = 33; 
	res = pthread_create(&thread_three, NULL, threadfunc_three, (void *)&data_arg3);
	if (res != 0) {
		perror("Thread creation failed");
		return -1;
	}
	data_arg4 = 44; 
	res = pthread_create(&thread_four, NULL, threadfunc_four, (void *)&data_arg4);
	if (res != 0) {
		perror("Thread creation failed");
		return -1;
	}

	printf("Waiting for threads to finish...\n");
	res = pthread_join(thread_one, &threadone_result);
	if (res != 0) {
		perror("Thread join failed");
		return -1;
	}
	printf("Thread one joined, it returned %d\n", *(int *)threadone_result);
	res = pthread_join(thread_two, &threadtwo_result);
	if (res != 0) {
		perror("Thread join failed");
		return -1;
	}
	printf("Thread two joined, it returned %d\n", *(int *)threadtwo_result);
	res = pthread_join(thread_three, &threadthree_result);
	if (res != 0) {
		perror("Thread join failed");
		return -1;
	}
	printf("Thread three joined, it returned %d\n", *(int *)threadthree_result);
	res = pthread_join(thread_four, &threadfour_result);
	if (res != 0) {
		perror("Thread join failed");
		return -1;
	}
	printf("Thread four joined, it returned %d\n", *(int *)threadfour_result);
	return 0;
}

/*! first thread function */ 
void *threadfunc_one(void *arg) {
	threadone_retvalue = 67;
	printf("threadfunc one is running. Argument was %d\n", *(int *)arg);
	printf("thread id = %ld\n", pthread_self());
	pthread_exit(&threadone_retvalue);
}

/*! second thread function */
void *threadfunc_two(void *arg) {

	threadtwo_retvalue = 89;
	printf("threadfunc two is running. Argument was %d\n", *(int *)arg);
	printf("thread id = %ld\n", pthread_self());
	pthread_exit(&threadtwo_retvalue);
}

/*! third thread function */
void *threadfunc_three(void *arg) {

	threadthree_retvalue = 34;
	printf("threadfunc three is running. Argument was %d\n", *(int *)arg);
	printf("thread id = %ld\n", pthread_self());
	pthread_exit((void *)&threadthree_retvalue);
}

/*! fourth thread function */
void *threadfunc_four(void *arg) {

	threadfour_retvalue = 12;
	printf("threadfunc four is running. Argument was %d\n", *(int *)arg);
	printf("thread id = %ld\n", pthread_self());
	pthread_exit(&threadfour_retvalue);
}
