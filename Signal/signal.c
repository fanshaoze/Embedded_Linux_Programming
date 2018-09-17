#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void sigint_handler(int signo){
	printf("Caught SIGNAL!\n");
	exit(EXIT_SUCCESS);

}
static void signal_handler(int signo){
	printf("Caught %s\n",sys_siglist[signo]);
	psignal(signo,"Interrup");
	printf("Caught %s\n",sys_siglist[signo]);
	psignal(signo,"Interrupt");
}
int main(){
	signal_handler(2);
	// if(signal(SIGINT,sigint_handler) == SIG_ERR){
	// 	fprintf(stderr, "Cannot handle SIGINT\n");
	// 	exit(EXIT_FAILURE);
	// }
	// for (;;){
	// 	printf("get sigint\n");
	// 	pause();
	// }
	
	return 0;
}