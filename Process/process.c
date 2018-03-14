#ifdef HAVE_CONFIG_H  
#include <config.h>  
#endif     
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <errno.h>     
#include <sys/wait.h>
#include <sys/types.h>
void out(){
  printf("atexit() succeeded\n");
}
int main(int argc, char *argv[])
{  
  if(atexit(out)){
    fprintf(stderr, "atexit() failed\n");
  }
  int status;

   //以NULL结尾的字符串数组的指针，适合包含v的exec函数参数 

    // char *arg[] = {"ls", "-a", NULL};  
     
    // /*** 创建子进程并调用函数execl 
    // * execl 中希望接收以逗号分隔的参数列表，并以NULL指针为结束标志 
    // */  
    // if( fork() == 0 )  
    // {  
    //  // in clild   
    //     printf( "1------------execl------------\n" );  
    //     if( execl( "/bin/ls", "ls","-l", NULL ) == -1 )  
    //     {  
    //         perror( "execl error ");  
    //         exit(1);  
    //     }  
    // }
    pid_t pid;
    pid = wait(&status);
    pid = fork();
    if(pid>0){
      printf("I am the parent of pid = %d\n",getpid());  
    }
    else if(!pid){
      printf("I am the child! pid = %d\n",getpid());
      printf( "1------------execl------------\n" );  
      if( execl( "/bin/ls", "ls","-l", NULL ) == -1 )  
      {  
          perror( "execl error ");  
          exit(1);  
      } 
    }
    else if(pid == -1){
      perror("fork");
    }
    if(WIFEXITED(status)){
    	printf("Normal termination with exit status = %d\n",WEXITSTATUS(status));
    }
    if(WIFSIGNALED(status)){
    	printf("Killed by signal = %d%s\n",
    	WTERMSIG(status),WCOREDUMP(status)?"(dump core)":"");
    }
    if(WIFSTOPPED(status)){
    	printf("Stopped by signal = %d\n",WSTOPSIG(status));
    }
    if(WIFCONTINUED(status)){
    	printf("Continued\n");
    }
    return 0;
}