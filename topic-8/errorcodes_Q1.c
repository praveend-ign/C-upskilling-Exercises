#include <stdio.h>
#include <errno.h>
#include <string.h>

FILE *fptr;

int open_file(char *file_name)
{
    if(file_name != NULL) {
    	fptr = fopen(file_name, "r");
	if(fptr == NULL) {
	/* return negative error number */
		return -errno;
	}
    } else {
	 fptr = NULL;
         printf("file name is NULL\n");
	 return -ENOENT;
    }
    return 0;
}

int main(void)
{
    char file_str[48];
    int rv;

    printf("Enter file name:\n");
    scanf("%s", file_str);
/* file_str contains file path name along with NULL character */
    rv = open_file(file_str);
    if(rv) {
	perror("file open error");
    } else {
        printf("file opened successfully\n");
	fclose(fptr);
    }
    return 0;
}
