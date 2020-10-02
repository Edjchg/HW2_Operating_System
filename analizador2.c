#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/ptrace.h>
#include "user_.h"
#include <linux/types.h>
//Modo kernel--------------
#include <linux/kernel.h>
//#include <linux/syscalls.h>
#include <linux/wait.h>
#include "call_array.h"
//--------------------------
#include "syscall_array_mag.h"
#include "syscall_array_mag.c"
#define MAXCHAR 1000
#define MAX_CALLS 500


int call_printer(struct CALL call_table[MAX_CALLS]);
int analiza(int argc, char * argv[]);
void print_call(int call);

int main(int argc, char * argv[] ){
	analiza(argc, argv);
	return 0;
}

int analiza(int argc, char * argv[]){
struct CALL call_table[MAX_CALLS];
init_call_array(call_table);
 int status; 
 //pid_t pid;
 int pid;
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
         const char *llamada = getcall(regs.orig_rax);
         write(1, "Se ha detectado una llamada ", 28);
         write(1, llamada, sizeof(llamada));
         write(1, "\n", 1);
         increase_call_value(call_table, regs.orig_rax);
         //call_table[regs.orig_rax].name = llamada;
         //call_table[regs.orig_rax].counter++;
         in_call=1;
         counter ++;
       }
       else
         in_call = 0; 
     
     ptrace(PTRACE_SYSCALL, pid, NULL, NULL); 
     wait(&status); 
     }
   }
   print_values(call_table);
   //call_printer(call_table);
   //printf("Total Number of System Calls=%d\n", counter);
   return 0; 


}
/*
int call_printer(struct CALL call_tables[MAX_CALLS]){
    int index = 0;
    write(1, "+--------------------+--------------------+\n", 44);
    write(1, "|                  Calls                  |\n", 44);
    write(1, "+--------------------+--------------------+\n", 44);
    write(1, "| Name               | Counter            |\n", 44);
    write(1, "+--------------------+--------------------+\n", 44);
    while(index <= MAX_CALLS){
        if(call_tables[index].counter > 0 & sizeof(call_tables[index].name) != 0){
            write(1, "|", 1);
            write(1, call_tables[index].name, sizeof(call_tables[index].name));
            write(1, "                1", 21);
            write(1, "|\n", 2);
            write(1, "+--------------------+--------------------+\n", 44);
        }
        ++index;   
    }
}
*/


