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
void out(){
  printf("atexit() succeeded\n");
}
int CreateGuardProcess(){
  pid_t pid;
  int i;
  pid = fork();
  if(pid == -1){
    return -1;
  }
  else if(pid != 0)
    exit(EXIT_SUCCESS);
  
  if(setsid() == -1){
    return -1;
  }
  if(chdir("/") == -1){
    return -1;
  }
  //NR_OPEN is not right,look for adcanced programming page 376
  //for(i = 0;i<NR_OPEN;i++){
  for(i = 0;i<1024;i++){
    close(i);
  }
  open("/dev/null",O_RDWR);
  dup(0);
  dup(0);
  return 0;
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
    pid_t sid;
    pid_t pgid;
    pid = wait(&status);
    system("ls -al");
    pid = fork();
    if(pid>0){
      printf("I am the parent of pid = %d\n",getpid());  
    }
    else if(!pid){
      printf("I am the child! pid = %d\n",getpid());
      sid = setsid();
      if(sid == -1){
        perror("setsid");
        return -1;
      }
      else{
        printf("sid %d\n", sid);
      }
      pgid = getpgid(0);
      if(pgid == -1){
        perror("getpgid");
      }
      else{
        printf("my process group id %d\n", pgid);
      }
      printf( "1------------execl------------\n" );  

      // if( execl( "/bin/ls", "ls","-l", NULL ) == -1 )  
      // {  
      //     perror( "execl error ");  
      //     exit(1);  
      // } 
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
    printf("getuid %d\n",getuid());
    printf("getgid %d\n",getgid());

    printf("geteuid %d\n",geteuid());
    printf("getegid %d\n",getegid());
    return 0;
}




// void out(){
//   printf("atexit() succeeded\n");
// }
// int main(int argc, char *argv[])
// {  
//   if(atexit(out)){
//     fprintf(stderr, "atexit() failed\n");
//   }

//    //以NULL结尾的字符串数组的指针，适合包含v的exec函数参数 

//     // char *arg[] = {"ls", "-a", NULL};  
     
//     // /*** 创建子进程并调用函数execl 
//     // * execl 中希望接收以逗号分隔的参数列表，并以NULL指针为结束标志 
//     // */  
//     // if( fork() == 0 )  
//     // {  
//     //  // in clild   
//     //     printf( "1------------execl------------\n" );  
//     //     if( execl( "/bin/ls", "ls","-l", NULL ) == -1 )  
//     //     {  
//     //         perror( "execl error ");  
//     //         exit(1);  
//     //     }  
//     // }
//     pid_t pid;
//     pid = fork();
//     if(pid>0){
//       int status = 0;
//       pid_t pidw;
//       pidw = waitpid(pid,&status,WNOHANG);
//       if(pidw == -1){
//         printf("???\n");
//         perror("waitpid");
//       }
//       else{
//         printf("pidw = %d\n",pid);
//         if(WIFEXITED(status));
//           printf("Normal termination with exit status=%d\n"
//             ,WEXITSTATUS(status));
//         if(WIFSIGNALED(status))
//           printf("Killed by signal = %D%S\n",
//             WTERMSIG(status),WCOREDUMP(status) ?"(dumped core)":"");
//       } 
//       printf("I am the parent of pid = %d\n",getpid()); 
//       //sleep(3);
//       //pid = getpid();
//       //printf("%s\n",);

//     }
//     else if(!pid){
//       printf("I am the child! pid = %d\n",getpid());


//       printf( "1------------execl------------\n" );  
//       // if( execl( "/bin/ls", "ls","-l", NULL ) == -1 )  
//       // {  
//       //     perror( "execl error ");  
//       //     exit(1);  
//       // } 

      

//     }
    
    
//     else if(pid == -1){
//       perror("fork");
//     }



    
// }