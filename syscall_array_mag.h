//
// Created by kenneth on 1/10/20.
//

#ifndef HW2_OPERATING_SYSTEM_LIKED_LIST_H
#define HW2_OPERATING_SYSTEM_LIKED_LIST_H
struct CALL {
    const char *name;
    int counter;
};
void init_call_array(struct CALL * head);
void increase_call_value(struct CALL * head,int call_num);
void convert_int(char * str_target,int number);
char digit_to_char(int digit);
void print_values(struct CALL * head);
void print_call_name(char * call_name);
void print_call_num(int num);
int  UPPER_LIMIT = 355;
int LOW_LIMIT = 424;

#endif //HW2_OPERATING_SYSTEM_LIKED_LIST_H
