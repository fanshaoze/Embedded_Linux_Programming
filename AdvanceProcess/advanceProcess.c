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
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

// void affinity(){
// 	cpu_set_t set;
// 	int ret;
// 	int i;
// 	CPU_ZERO(&set);
// 	ret = sched_getaddinity(0,sizeof(cpu_set_t),&set);
// 	if(ret == -1){
// 		perror("sched_getaddinity");
// 	}
// 	for(i = 0;i<CPU_SETSIZE;i++){
// 		int cpu;
// 		cpu = CPU_ISSET(i,&set);
// 		printf("cpu=%i is %s\n",i,cpu?"set" : "unset");
// 	}
// 	return ;
// }
int schedule(){
	int policy;
	struct sched_param sp = {.sched_priority = 1};
	int ret;
	policy = sched_getscheduler(0);
	switch(policy){
		case SCHED_OTHER:
			printf("policy is normal\n");
			break;
		case SCHED_RR:
			printf("policy is round-robin\n");
			break;
		case SCHED_FIFO:
			printf("policy is first-in ,first-out\n");
			break;
		case -1:
			perror("sched_getscheduler");
			break;
		default:
			fprintf(stderr, "unknown policy\n");
	}
	ret = sched_setscheduler(0,SCHED_RR,&sp);
	if(ret == -1){
		perror("sched_setscheduler");
		return -1;
	}
	else{
		printf("set scheduler success\n");
		return 0;
	}

}
int get_schedule_param(){
	int policy;
	struct sched_param sp ;
	int ret;
	ret = sched_getparam(0,&sp);
	if(ret == -1){
		perror("sched_getparam");
		return -1;
	}
	else{
		printf("sched_getparam success\n");
		printf("our priority is %d\n", sp.sched_priority);
	}
	return 0;

}
int set_schedule_param(){
	int policy;
	struct sched_param sp ;
	int ret;
	
	sp.sched_priority = 1;
	ret = sched_setparam(0,&sp);
	if(ret == -1){
		perror("sched_setparam");
		return -1;
	}
	else{
		printf("sched_setparam success\n");
		printf("our priority is %d\n", sp.sched_priority);
	}
	return 0;

}
int main(){
	
	int ret;
	
	errno = 0;
	printf("nice value is %d\n",nice(0));
	ret = nice(10);
	if(ret = -1 && errno != 0)
		perror("nice");
	else
		printf("nice value now is %d\n",nice(0));
	ret = getpriority(PRIO_PROCESS,0);
	printf("nice value is %d\n", ret);
	nice(1);
	ret = getpriority(PRIO_PROCESS,0);
	printf("nice value increased is %d\n", ret);
	ret = setpriority(PRIO_PGRP,0,10);
	if(ret == -1){
		perror("setpriority");
	}
	else{
		printf("nice value is %d\n", nice(0));
	}
	//affinity();
	set_schedule_param();
	//schedule();
	get_schedule_param();
	if(sched_yield()){
		perror("sched_yield");
	}
	else{
		printf("sched success\n");
	}
}