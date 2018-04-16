#ifdef HAVE_CONFIG_H  
#include <config.h>  
#endif     
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <errno.h>     
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/fs.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>



void* thr_fn(void *arg)
{
    printf("new thread\n");
    return((void*)0);
    //stop_thread();
}

int thread_eque(pthread_t thread1,pthread_t thread2){
	int ret;
	ret = pthread_equal(thread1,thread2);
	if(ret){
		printf("%lu %lu thread equal\n",thread1,thread2);
		return -1;
	}
	else{
		printf("%lu %lu thread diff\n",thread1,thread2);
		return 0;
	}

}
int stop_thread(pthread_t thread){
	int unused;
	int ret;
	ret = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,&unused);
	if(ret){
		errno = ret;
		perror("pthread_setcancelstate");
		printf("pthread_setcancelstate fail\n");
		return -1;
	}
	else{
		printf("pthread_setcancelstate success\n");
	}
	ret = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,&unused);
	if(ret){
		errno = ret;
		perror("pthread_setcanceltype");\
		printf("pthread_setcanceltype fail\n");
		return -1;
	}
	else{
		printf("pthread_setcanceltype success\n");
	}
	printf("the thread will be stopped is %lu\n",thread);
	ret = pthread_cancel(thread);//thread do another time???
	if(ret){
		errno = ret;
		perror("pthread_cancel");
		printf("pthread_cancel fail\n");
		return -1;
	}
	else{
		printf("pthread_cancel success\n");
	}


	return 0; 
}

pthread_t create_thread(pthread_t thread){
	
	int ret;
	ret = pthread_create(&thread,NULL,thr_fn,NULL);
	printf("%d\n", ret);
	if(ret){
		errno = ret;
		perror("pthread_create");
		printf("pthread error");
		return -1;
	}
	else{
		printf("%lu create thread success\n",thread);
		//return 0;
	}
	return thread;
}

int main(){
	pthread_t thread =1;
	thread = create_thread(thread);
	thread_eque(pthread_self(),thread);
	stop_thread(thread);
	return 0;
}