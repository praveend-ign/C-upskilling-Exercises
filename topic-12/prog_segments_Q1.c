/*! program to understand different segments
 *  present in the executable program i.e.
 *  text, data, bss, stack and heap. Also,
 *  we learn about how a program or code is
 *  stored in different segments 
 */
#include <stdio.h>
#include <stdlib.h>

#define MEM_ALLOC_SIZE    64

int global_var;
static int stat_var;
const int c_glob_var = 0x988;

/*! define some arbitrary function 1 */
void call_func_1(int s_local_var)
{
     int func1_var;

     func1_var = (s_local_var*52);
     printf("func1_var = %d\n", func1_var);
}

/*! define some arbitrary function 2 */
int call_func_2(int func_arg_1, char *string)
{
     int fn2_var;

     if(string != NULL) {
	     printf("%s\n", string);
	     fn2_var = 0;
     } else {
	fn2_var = 693;
     }
     func_arg_1 += 430;
     return (fn2_var + func_arg_1);
}

int main(void)
{
    int local_var = 0;
    static int s_local_var;
    char *str = "Hello programmers";
    int *ptr;
    int retval;

    global_var = 431;
    stat_var += c_glob_var;
    local_var = (global_var)*615;
    s_local_var += c_glob_var;

    call_func_1(s_local_var);
    retval = call_func_2(local_var, str);
    ptr = malloc(MEM_ALLOC_SIZE*sizeof(int));
    if(ptr == NULL) {
	printf("unable to allocate memory\n");
    }
    free(ptr);
    return 0; 
}
