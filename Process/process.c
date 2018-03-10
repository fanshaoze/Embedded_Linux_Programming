#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
int main(){
	printf("My pid = %jd\n",(intmax_t)getpid());
	printf("Parent's pid = %jd\n",(intmax_t)getppid());
	return 0;
} 