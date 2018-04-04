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
	//struct sched_param sp = {.sched_priority = 1};
	sp.sched_priority = 3;
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
int nice_operate(){
	int ret;
	
	errno = 0;
	printf("nice value is %d\n",nice(0));
	ret = nice(10);
	if(ret = -1 && errno != 0){
		perror("nice");
		return -1;
	}
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
		return -1;
	}
	else{
		printf("nice value is %d\n", nice(0));
	}
	return 0;

}
int schedyield(){
	if(sched_yield()){
		perror("sched_yield");
	}
	else{
		printf("sched yield success\n");
	}
	return 0;

}
int get_priority_range(){
	int max,min;
	min = sched_get_priority_min(SCHED_RR);
	if(min == -1){
		perror("sched_get_priority_min");
		printf("not get min\n");
		return -1;
	}
	max = sched_get_priority_max(SCHED_RR);
	if(max == -1){
		perror("sched_get_priority_max");
		printf("not get max\n");
		return -1;
	}
	printf("SCHED_RR priority range is %d to %d\n",min,max);
	return 0;
}
int get_interval(){
	struct timespec tp;
	int ret;
	ret = sched_rr_get_interval(0,&tp);
	if(ret == -1){
		perror("sched_rr_get_interval");
		return -1;
	}
	else{
		printf("Our time quantum is %.2lf milliseconds\n",(tp.tv_sec*1000.0f)+(tp.tv_nsec/1000000.0f));
	}
	return 0;
}
int get_source_limit(){
	struct rlimit rlim;
	int ret;
	ret = getrlimit(RLIMIT_CORE,&rlim);
	if(ret == -1){
		perror("getrlimit");
		printf("get source limit error\n");
		return -1;
	}
	else{
		printf("RLIMIT_CORE limit:soft=%ld hard=%ld\n",rlim.rlim_cur,rlim.rlim_max );
	}
	return 0;
}
int set_source_limit(){
	struct rlimit rlim;
	int ret;
	rlim.rlim_cur = 32*1024*1024;
	rlim.rlim_max = RLIM_INFINITY;
	ret = setrlimit(RLIMIT_CORE,&rlim);
	if(ret == -1){
		perror("setrlimit");
		printf("set source limit error\n");
		return -1;
	}
	else{
		printf("set source limit success\n");
		return -0;
	}
}
int main(){
	
	nice_operate();
	//affinity();
	schedule();
	//atention:set schedule first,then the set schedule param
	get_schedule_param();
	set_schedule_param();
	get_priority_range();
	get_interval();
	get_source_limit();
	set_source_limit();
	schedyield();
	
}