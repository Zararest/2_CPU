#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "stack_class.h"
#include "commands.h"

const int MEMORY_SIZE = 500;
const int SIZE_FUNC_STACK = 10;

class CPU_class{

public:

    double* machine_code = NULL;
    unsigned char* memory = NULL;
    my_stack* stack = NULL;
    my_stack* func_stack = NULL;
    int command_pointer = 0;

    char* byte_segment = NULL;
    short int* word_segment = NULL;
    int* double_word_segment = NULL;
    double* segment_private = NULL;

    CPU_class(int, int);

    ~CPU_class();

    void processor(int);

    double* machine_code_access();

    void increase_pointer(int);

    int return_command(int);

    double return_command_double(int);

    double* element_access(int);

    void add_to_memory(int, void*, int);

    void push_stack(double);

    double pop_stack();

    void push_func_stack(double);

    double pop_func_stack();

    int get_reg_data(double);

    void dump_memory();

    void class_clean();
 
};
