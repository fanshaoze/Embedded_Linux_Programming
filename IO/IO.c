#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main(){
	FILE *stream;
	int fd;

	stream = fopen("test.txt","a+");
	flockfile(stream);
	if(!stream){
		printf("error\n");
	}
	else{
		printf("right\n");
	}
	fputs("the\n",stream);
	// if(fputs("the\n",stream) == EOF){
	// 	printf("fputs error\n");
	// }
	funlockfile(stream);
	fclose(stream);
	fd = open("test.txt",O_RDONLY);
	if (fd == -1){
		printf("error\n");
	}
	else{
		printf("right\n");
	}
	stream = fdopen(fd,"r");
	if(!stream){
		printf("error\n");
	}
	else{
		printf("right\n");
	}
	int c = 0;
	int t = 0;
	//c = fgetc(stream);
	if(c == EOF)
		printf("end\n");
	else
		printf("c = %c\n",(char)c);
    char str[100];
	char *s;
	s = str;
	c = fgetc(stream);
	//s = "";
	while(c != EOF){
		*s ++=  c;
		c = fgetc(stream);
	}
	*s = '\0';
	printf(str);

}

