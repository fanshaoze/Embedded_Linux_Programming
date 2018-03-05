#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd;
    fd = open("test.txt",O_RDONLY);
    if (fd == -1)
    {
         printf("open file error\n");
    }
    else
    {
        printf("open file success\n");
    }
    return 0;
}
