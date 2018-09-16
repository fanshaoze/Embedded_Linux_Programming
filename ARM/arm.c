#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>

struct treasure_map
{
    int a;
    int b;
};

int test_calloc(){
	int *x,*y;
	y = calloc(50,sizeof(int));
	if(!y){
		perror("calloc");
		return -1;
	}
	else{
		printf("calloc success\n");
		return 0;
	}
}

int test_malloc(){
    struct treasure_map *map;
    map = malloc(sizeof(struct treasure_map));
    if(!map){
        perror("malloc");
        return -1;
    }
    else{
        printf("malloc success\n");
        return 0;
    }
}
int test_realloc(){
    int *x,*y;
	y = calloc(50,sizeof(int));
	x = realloc(y,25*sizeof(int));
	if(!x){
		perror("realloc");
		return -1;
	}
	else{
		printf("ralloc success\n");
		return 0;
	}
}

void print_chars(int n,char c){
	int i;
	for(i = 0;i<n;i++){
		char *s;
		int j;
		s = calloc(i+2,1);
		if(!s){
			perror("calloc");
			break;
		}
		for(j = 0;j<i+1;j++){
			s[j] = c;
		}
		printf("%s\n", s);
		free(s);
	}
	
}
int test_mmap(){
	return 0;
}
int test_posix(){
	char *buf;
	int ret;
	ret = posix_memalign(&buf,256,1024);
	if(ret){
		fprintf(stderr, "posix_memalign: %s\n",strerror(ret));
		return -1;
	}
	else{
		printf("posix_memalign success\n");
		free(buf);
		return 0;
	}
}
int test_break(){
	printf("the current break point is %p\n", sbrk(0));
	return 0;
}
int test_mallopt(){
	int ret = 0;
	ret = mallopt(M_MMAP_THRESHOLD, 64* 1024);
	if(!ret){
		fprintf(stderr, "mallopt,M_MMAP_THRESHOLD,err\n");
	}
	else{
		printf("mallopt,M_MMAP_THRESHOLD success,%lf,\n",M_MMAP_THRESHOLD);
		return 0;
	}
	return 0;
}
int test_usable_size(){
	size_t len = 21;
	size_t size;
	char *buf;

	buf = malloc(len);
	if(!buf){
		perror("malloc");
		return -1;
	}
	size = malloc_usable_size(buf);
	printf("%d\n", size);
	return 0;
}
int test_mallinfo(){
	struct mallinfo m;
	m = mallinfo();
	printf("free chunk: %d\n", m.ordblks);
	return 0;
}
int main()
{
    test_malloc();
    test_calloc();
    test_realloc();
    print_chars(3,'x');
    test_posix();
    test_break();
    test_mmap();
    test_mallopt();
    test_usable_size();
    test_mallinfo();
    return 0;
}

