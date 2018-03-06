#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main()
{
    int fd;
    ssize_t ret;
    unsigned long var;
    char buf[20];
    char *buff = buf;
    //extern int errno;
    int len = 20;
    char *p1 = "This is a c test code";
    int i = 0;
    fd = open("test.txt",O_RDONLY);
    if (fd == -1)
    {
         printf("open file error\n");
    }
    else
    {
        printf("%d open file success\n",fd);
    }
    ret = read(fd,buff,len);
    while (len >0 && ret !=0)
    {
    	printf("ret  %d\n",ret);
    	printf("buf  %s\n",buff);
    	if(ret == -1)
    	{
    		printf("wrong");
    		if(errno == EINTR)
    			continue;
    		perror("read");
    		break;
    	}
    	len -= ret;
    	buff += ret;
    	ret = read(fd,buff,len);
    }
    printf("buf  %s\n",buf);
    buff = &var;
    pread (fd, buff, 3,2);
    *(buff+3) = "\0";
    printf("var  %s\n",&var);
    pwrite (fd, p1, 3, 0);
    int xd;
    xd = creat("test2.txt",0666);
    if (xd == -1)
    {
         printf("create file error\n");
    }
    else
    {
        printf("%d create file success\n",xd);
    }
    for(i = 0;i<21;i++)
    {
        	printf("%d  \n",(strlen(p1)-len));
         	int n;
         	n=write(xd, p1+len, (strlen(p1)-len));
         	printf("n = %d\n",n);
         	if(n== 0 || n == -1)   //if((n=write(fp, p1+len, 3)) == 0)
        {                                                 //strlen(p1) = 21
             printf("n = %d \n", n);
             break;
        }
        len+=n;
    }

    if (close (fd) == -1)
	perror ("close");
    else{
        printf("close success\n");
    }
    return 0;
}
