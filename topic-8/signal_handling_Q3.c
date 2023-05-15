#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signum)
{
    printf("signal %d received\n", signum);
    exit(1);
}

int main(void)
{
    int sig;
    int rv;
    struct sigaction sig_act;
    int *ptr = NULL;
    int div = 21;

    //sig = (SIGINT | SIGSEGV | SIGFPE | SIGTERM);
    sig = SIGINT;
    sig_act.sa_handler = signal_handler;
    sigemptyset(&sig_act.sa_mask);
    sig_act.sa_flags = 0;
    rv = sigaction(sig, &sig_act, 0);
    if(rv < 0) {
	perror("sigaction error");
	return -1;
    }
    rv = 0;
    while(1) {
/* after some time, dereference NULL ptr to generate
 * segmentation fault signal
 */	    
	rv++;
	if(rv > 20) {
		 *ptr = 87;
		//div = div/0;
	}
	printf("hello world\n");
	sleep(2);
    }
    return 0;
}
