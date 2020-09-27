#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h> /* for ptrace() */
#include <sys/user.h> /* for struct user_regs_struct */
/* This program runs the 2nd argument argv[1] in a child process 
 * and count the number of system calls made by the child process.
 	gcc -o prueba2 prueba2.c -> compilar
 	./prueba2 ./prueba -> ejecutar, ese archivo ./prueba es un ejecutable de cualquier codigo en C.
 */
#define MAXCHAR 1000
void get_name(char* source, char* result);
int search_call(int call, char* returned_name);
int main ( int argc, char * argv[] )
{
 int status; 
 pid_t pid;
 struct user_regs_struct regs;
 int counter = 0;
 int in_call =0;
 char name[20];
 switch(pid = fork()){
   case -1: 
     perror("fork");
     exit(1);
   case 0: /* in the child process */
     ptrace(PTRACE_TRACEME, 0, NULL, NULL);
     execvp(argv[1], argv+1);
   default: /* in the parent process */
     wait(&status);
     while(status == 1407){
       ptrace(PTRACE_GETREGS, pid, NULL, &regs);
       if(!in_call){
         //printf("SystemCall %ld called with %ld, %ld,     %ld\n",regs.orig_rax, regs.rbx, regs.rcx, regs.rdx);
         search_call(regs.orig_rax, name);
         printf("El ejecutable analizado realizó la llamda %s\n", name);
         strcpy(name, "                   ");
         in_call=1;
         counter ++;
       }
       else
         in_call = 0; 
     ptrace(PTRACE_SYSCALL, pid, NULL, NULL); 
     wait(&status); 
     }
   }
   printf("Total Number of System Calls=%d\n", counter);
   return 0; 
}
/*#######################################################################################################################################
La funcion search_call recibe como parámetro el identificador de la llamada al sistema y el nombre de la variable donde será copiado el nombre de dicha variable. El parámetro returned_name se pasa por referencia.
Esta función lee todo el archivo unistd_64.h hasta encontrar la llamada que es requerida, retornando el nombre de la llamda por referencia.
*/
int search_call(int call, char* returned_name){
	FILE *fp;
    char str[MAXCHAR];
    char* filename = "/usr/include/x86_64-linux-gnu/asm/unistd_64.h";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    call += 3;
    int number_calls = 0;
    while (fgets(str, MAXCHAR, fp) != NULL){
    	
    	if(number_calls == call){
    		//printf("%s\n", str);
    		//printf("Nombre vacio: %s\n", returned_name);
    		get_name(str, returned_name);
    		//printf("Nombre 2: %s tamaño de %li\n", returned_name, strlen(returned_name));
    	}
    	number_calls++;
    }
    fclose(fp);
    return 0;
}
/*#######################################################################################################################################
La funcion get_name recibe como parámetro una línea de string, y la variable donde será copiado el nombre de la llamada al sistema.
Esta función analiza una línea que corresponde a una cadena de chars, y extrae el nombre de la llamada al sistema que se está solicitando.
*/
void get_name(char* source, char* result){
	int index = 13;
	int index_result = 0;
	while(source[index] != 32){ //32 -> espacio
		*(result + index_result) = *(source + index);
		//printf("%c\n", result[index_result]);
		index++;
		index_result++;
	}
	
}
//#######################################################################################################################################
