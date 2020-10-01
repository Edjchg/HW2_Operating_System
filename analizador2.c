#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/ptrace.h>
#include "user_.h"
#include <linux/types.h>
//Modo kernel--------------

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/wait.h>

//--------------------------

#define MAXCHAR 1000

int analiza(int argc, char * argv[]);
void print_call(int call);

int main(int argc, char * argv[] ){
	analiza(argc, argv);
	return 0;
}

int analiza(int argc, char * argv[]){
 int status; 
 pid_t pid;
 struct user_regs_struct regs;
 int counter = 0;
 int in_call =0;
 char name[20];
 switch(pid = fork()){
   case -1: 
   	;
     //perror("fork");
     //exit(1);
   case 0: /* in the child process */
     ptrace(PTRACE_TRACEME, 0, NULL, NULL);
     execvp(argv[1], argv+1);
   default: /* in the parent process */
     wait(&status);
     while(status == 1407){
       ptrace(PTRACE_GETREGS, pid, NULL, &regs);
       if(!in_call){
       	 //Descomentar en compilacion de kernel.
         //printk("La llamada que hizo el subproceso es: %lli \n", regs.orig_rax);
         write(1, "Se ha detectado una llamada\n", 28);
         in_call=1;
         counter ++;
       }
       else
         in_call = 0; 
     ptrace(PTRACE_SYSCALL, pid, NULL, NULL); 
     wait(&status); 
     }
   }
   //printf("Total Number of System Calls=%d\n", counter);
   return 0; 


}


