//
// Created by kenneth on 1/10/20.
//
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/string.h>
#include "syscall_array_mag.h"
#include "call_array.h"

void init_call_array(struct CALL * head){
    int i  = 0;
    while (i!= UPPER_LIMIT ){
        head[i].name = getcall(i);
        head[i].counter = 0;
        i++;
    }
    i = LOW_LIMIT;
    while ( i != 436){
        head[i - (424 -334) +1].name = getcall(i);
        head[i - (424 -334) +1].counter = 0;
        i++;
    }
    head[i - (424 -334) +1].counter = -1;
}
void increase_call_value(struct CALL * head,int call_num){
    if (call_num >=436 || (call_num<424 && call_num>=UPPER_LIMIT ))
    {
    write(1, "Call not supported", 19);
    }
    if(call_num>=424){
          head[ call_num - (424 -334) +1].counter++;
     }
     head[call_num].counter++;
}
int get_int_len(int number){
    int  i = 1;
    while (number >= 10)
    {
        i++;
        number/= 10;
    }

    return i;
}
void convert_int(char * str_target,int number){
    int i, rem, len = 0, n;
 
    n = number;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = number % 10;
        number = number / 10;
        str_target[len - (i + 1)] = rem + '0';
    }
    str_target[len] = '\0';
}
void print_call_name(char * call_name){
    char space[] ={'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\0'};
     int i = 0;
     int len = strlen(call_name);
     while(i!= len){
         space[i+1] = call_name[i];
         i++;
     }
         write(1, space, strlen(space));

}
void print_call_num(int num){
    char target[20];
    convert_int(target,num);
    char space[] ={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','\0'};
    int len = strlen(target);
    int i = 0;
    while(i!= len){
         space[i] = target[i];
         i++;
     }
    write(1, space, strlen(space));
}
void print_values(struct CALL * head){
int i = 0;
    write(1, "+--------------------+--------------------+\n", 44);
    write(1, "|                  Calls                  |\n", 44);
    write(1, "+--------------------+--------------------+\n", 44);
    write(1, "| Name               | Counter            |\n", 44);
    write(1, "+--------------------+--------------------+\n", 44);
while (head[i].counter!=-1)
{
    if (head[i].counter!=0)
    {
        print_call_name(head[i].name);

        print_call_num(head[i].counter);
        write(1, "\n", 1);
        write(1, "+--------------------+--------------------+\n", 44);
    }
    i++;

}

}
// int main(int argc, char * argv[] ){
// struct CALL call_table[500];
// init_call_array(call_table);
// increase_call_value(call_table,0);
// increase_call_value(call_table,0);
// increase_call_value(call_table,0);
// increase_call_value(call_table,5);
// increase_call_value(call_table,5);
// increase_call_value(call_table,5);
// increase_call_value(call_table,435);
// increase_call_value(call_table,435);
// increase_call_value(call_table,435);
// print_values(call_table);
// 	return 0;
// }
//gcc syscall_array_mag.c