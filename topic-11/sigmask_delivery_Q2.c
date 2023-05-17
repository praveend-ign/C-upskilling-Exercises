/*! program to demonstrate the signal masks and
 * signal delivery using sigaddset() and sigprocmask()
 * to block or unblock any particular signal 
 */
#include <stdio.h>
#include <signal.h>

/*! function for compute intensive task in inifinite loop
 */
void busy_work(void)
{
    double var = 0;

    while(1) {
	var = (var + 7453.21)*(1298.64)/1000;
	var -= 521.3;
    }
}

int main(void)
{
    sigset_t sig_obj;
    int retval;

    sigemptyset(&sig_obj);
    retval = sigaddset(&sig_obj, SIGINT);
    if(retval) {
	printf("sigaddset error\n");
    }
    retval = sigprocmask(SIG_UNBLOCK, &sig_obj, NULL);
    if(retval) {
	printf("sigprocmask error\n");
    }
    busy_work();
    return 0;
}
