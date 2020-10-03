#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/ptrace.h>
#include "user_.h"
#include <stdio.h>
#include <linux/types.h>
//Modo kernel--------------
#include <stdlib.h>
#include <linux/kernel.h>
//#include <linux/syscalls.h>
#include <linux/wait.h>
#include <linux/unistd.h>
#include "call_array.h"
//--------------------------
#include "syscall_array_mag.h"
#include "syscall_array_mag.c"
#define MAXCHAR 1000
#define MAX_CALLS 500


//int call_printer(struct CALL call_table[MAX_CALLS]);
int analiza(int argc, char * argv[]);
void print_call(int call);
char * get_axecutable(char * executable_params);
char** get_params(char * executable_params);


//MAIN
int main(int argc, char * argv[] ){
        if (argv[1] == NULL || argv[2] == NULL) 
    {
      printf("No se proveen los parametros necesarios");
      return -1;
    }
 FILE *fptr = fopen(argv[1],"r");
 if (fptr == NULL)
 {
   printf("El ejecutable no existe");
 }
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

     
      char ** args = get_params(argv[1]);
      char * exe = get_axecutable(argv[1]);
      execvp(exe, args);
   default: /* in the parent process */
     wait(&status);
     while(status == 1407){
       ptrace(PTRACE_GETREGS, pid, NULL, &regs);
       if(!in_call){
       	 //Descomentar en compilacion de kernel.
         //printk("La llamada que hizo el subproceso es: %lli \n", regs.orig_rax);
         if (*argv[2] == '1'){
         	const char *llamada = getcall(regs.orig_rax);
         	write(1, "Se ha detectado una llamada ", 28);
         	write(1, llamada, sizeof(llamada));
         	write(1, "\n", 1);
         }else if(*argv[2] == '2'){
         	increase_call_value(call_table, regs.orig_rax);
         }
         
         
         	
         
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
   if(*argv[2] == '2'){
   		print_values(call_table);
   }
   
   //call_printer(call_table);
   //printf("Total Number of System Calls=%d\n", counter);
   return 0; 


}
char * get_axecutable(char * executable_params){
  
  char * to_return  = malloc(sizeof(char)*100);
  int i = 0;
  while(i!=100){
  to_return[i] = '\0';
  i++;}
  i=0;
  while(executable_params[i]!= ',' && i!= strlen(executable_params)){
    to_return[i] = executable_params[i];
    i++;
  }
  return to_return;
}
char** get_params(char * executable_params){
  char ** params = malloc(sizeof(char*)*10);
  int i = 0;
  while(i!=10){
    params[i]= NULL;
    i++;
  }
  i=0;
  int j = 0;
  int n = 0;
  params[j] = malloc(100);
  while(i < strlen(executable_params)){
    if(executable_params[i] == ','){
      params[j][n] = '\0';
      n=0;
      j++;
      params[j] =malloc(100);
      i++;
      continue;
    }
    params[j][n] = executable_params[i];
    i++;
    n++;
  }
return params;
}



