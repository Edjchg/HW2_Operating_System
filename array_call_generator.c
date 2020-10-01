//
// Created by kenneth on 30/9/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_call_generator.h"
#include <unistd.h>
#include <sys/ptrace.h> /* for ptrace() */
#include <sys/user.h> /* for struct user_regs_struct */
#include "call_array.h"
/*#######################################################################################################################################
La funcion search_call recibe como parámetro el identificador de la llamada al sistema y el nombre de la variable donde será copiado el nombre de dicha variable. El parámetro returned_name se pasa por referencia.
Esta función lee todo el archivo unistd_64.h hasta encontrar la llamada que es requerida, retornando el nombre de la llamda por referencia.
*/
int search_call(int call, char* returned_name){
    FILE *fp;
    char str[1024];
    char* filename = "/usr/include/x86_64-linux-gnu/asm/unistd_64.h";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return -1;
    }
    call += 3;
    int number_calls = 0;
    while (fgets(str, 1024, fp) != NULL){
        if(number_calls>700){
            return -1;
        }
        if(number_calls == call){
            get_name(str, returned_name);
            printf("%s \n",str);
            fclose(fp);
            return 1;
        }
        number_calls++;
    }
    fclose(fp);
    return -1;
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
        index++;
        index_result++;
    }

}
void reset_str(char * string,int size){
    while ( (size = size-1)!=0 ){
        string[size] = '\0';
    }
}
void create_array_file(){
    FILE *fp;
    char str[1024];
    char* filename = "../call_array.h";
    fp = fopen(filename, "wr");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return -1;
    }
    int i =0;
    fwrite("#ifndef HW2_OPERATING_SYSTEM_CALL_ARRAY_H \n",strlen("#ifndef HW2_OPERATING_SYSTEM_CALL_ARRAY_H \n"), 1, fp);
    fwrite("##define HW2_OPERATING_SYSTEM_CALL_ARRAY_H \n", strlen("#define HW2_OPERATING_SYSTEM_CALL_ARRAY_H \n"), 1, fp);
    fwrite("char syscalls[] = { \n",strlen("char syscalls[] = { \n"), 1, fp);
    while (i!= 436){
        if ((i%6)==0 && i!=0  )
        {
            write(fp,"\n",1);
        }
        reset_str(str,1024);
        str[0] = '"';
        str[1]= '\0';
        fwrite(str, strlen(str), 1, fp);
        search_call(i,str);
        fwrite(str, strlen(str), 1, fp);
        str[0] = '"';
        str[1]= '\0';
        fwrite(str, strlen(str), 1, fp);
        if (i!=445)
        {
            fwrite(",",strlen(","), 1, fp);
        }
        i++;
    }
    fwrite("};\n  #endif",strlen("}; \n  #endif"), 1, fp);
    printf("FIN");
    close(fp);
}

int main ( int argc, char * argv[] )
{
    printf("%s,%s",getcall(0),getcall(435));
create_array_file();
}

