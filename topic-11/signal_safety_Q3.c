/*! program to note the inconsistency due to
 * non re-entrant signal handler functions
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define ARRAY_SIZE	100

char array[ARRAY_SIZE];

/*! this function is non re-entrant as
 * it access the global variable and could 
 * be incorrectly read/write
 */ 
void unsafe_handler(int signum)
{
    int i;

    for(i=0;i<ARRAY_SIZE;i++) {    
    	printf("%x\n", array[i]);
    }
}

/*! function is re-entrant as write() system call
 * can be called safely in the signal handlers
 */
void safe_handler(int signum)
{
    int bytes_written;

    /*! write to standard output */
    bytes_written = write(1, array, ARRAY_SIZE);

}

int main(void)
{
    int i;
 
    /*! initialize the global array with some value */
    for(i=0;i<ARRAY_SIZE;i++) {
    	array[i] = (0x61+i);
    }
    signal(SIGINT, unsafe_handler);
    signal(SIGTERM, safe_handler);

    i = 0;
    /*! modify last element of global array */
    while(1) {
	array[ARRAY_SIZE-1] = (0x61+i);
	i++;
	if(i > 26)
		i = 0;
    }
    return 0;
}
