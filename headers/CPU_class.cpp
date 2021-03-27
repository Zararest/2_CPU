#include "CPU_class.h"

CPU_class::CPU_class(int size_of_stack, int size_of_machine_code){

        stack = stack_create(size_of_stack, sizeof(double), 1);
        assert(stack != NULL);

        func_stack = stack_create(SIZE_FUNC_STACK, sizeof(double), 1);
        assert(func_stack != NULL);

        machine_code = (double*) calloc(size_of_machine_code, sizeof(double));
        memory = (unsigned char*) calloc(MEMORY_SIZE, sizeof(unsigned char));

        byte_segment = (char*) calloc(3, sizeof(char));
        word_segment = (short int*) calloc(4, sizeof(short int));
        double_word_segment = (int*) calloc(5, sizeof(int));
        segment_private = (double*) calloc(2, sizeof(double));
    }


int CPU_class::get_reg_data(double reg_number_double){

    int reg_len = (((int)reg_number_double) / 10) % 10;
    int reg_number = ((int)reg_number_double) % 10;

            switch (reg_len){

            case byte_len:
                return (int)byte_segment[reg_number];
                break;

            case word_len:
                return (int)word_segment[reg_number];
                break;

            case double_word_len:
                return (int)double_word_segment[reg_number];
                break;

            case private_len:
                return (int)segment_private[reg_number];
                break;
            }
}

double* CPU_class::machine_code_access(){

        return machine_code;
    }

void CPU_class::increase_pointer(int increment){

        command_pointer = command_pointer + increment;
    }

int CPU_class::return_command(int pointer_modification){

        return (int)machine_code[command_pointer + pointer_modification];
    }

double CPU_class::return_command_double(int pointer_modification){

        return machine_code[command_pointer + pointer_modification];
    }

double* CPU_class::element_access(int pointer_modification){

        return &machine_code[command_pointer + pointer_modification];
    }

void CPU_class::add_to_memory(int memory_pointer, void* elem, int size_of_elem){

        memcpy(memory + memory_pointer, elem, size_of_elem);
    }

void CPU_class::push_stack(double data){

        assert(push(stack, data) == 0);
    }

void CPU_class::push_func_stack(double data){

        assert(push(func_stack, data) == 0);
    }

double CPU_class::pop_stack(){

        return *(double*)pop(stack);
    }

double CPU_class::pop_func_stack(){

        return *(double*)pop(func_stack);
    }

void CPU_class::dump_memory(){

        int i = 0;

        printf("DUMP\n");
        for (i = 0; i < 40; i++){

            printf("|%i|", memory[i]);
        }
        printf("\n---\n");
    }

void CPU_class::class_clean(){

        stack_destruct(stack);
        free(machine_code);
        free(memory);
        free(byte_segment);
        free(word_segment);
        free(double_word_segment);
        free(segment_private);
    }

void CPU_class::processor(int num_of_comands){//это надо сунуть в класс

    int reg_len = 0, reg_number = 0;
    char symbol = 0;
    unsigned char* memory_adress = NULL;
    double fir_num = 0, sec_num = 0;

    while ( command_pointer < num_of_comands){

        switch (  return_command(0) ){
    //---------
        case CPU_CALL:

             push_func_stack( (double)( command_pointer + 2) );
             command_pointer =  return_command(1) + 2;
            break;

        case CPU_RET:

             command_pointer =  pop_func_stack();
            break;

        case CPU_MOV_RD:

            reg_len = ( return_command(1) / 10) % 10;
            reg_number =  return_command(1) % 10;

            switch (reg_len){

            case byte_len:
                 byte_segment[reg_number] = (char) return_command(2);
                break;

            case word_len:
                 word_segment[reg_number] = (short int) return_command(2);
                break;

            case double_word_len:
                 double_word_segment[reg_number] = (int) return_command(2);
                break;

            case private_len:
                 segment_private[reg_number] =  return_command_double(2);
                break;
            }

             increase_pointer(3);
            break;

        case CPU_MOV_RV:

            reg_len = ( return_command(1) / 10) % 10;
            reg_number =  return_command(1) % 10;
            memory_adress = memory_adress =  memory +  return_command(2) +  get_reg_data( return_command(3));

            switch (reg_len){

            case byte_len:
                 byte_segment[reg_number] = *((char*)(memory_adress));
                break;

            case word_len:
                 word_segment[reg_number] = *((short int*)(memory_adress));
                break;

            case double_word_len:
                 double_word_segment[reg_number] = *((int*)(memory_adress));
                break;

            case private_len:
                 segment_private[reg_number] = *((double*)(memory_adress));
                break;
            }

             increase_pointer(4);
            break;

        case CPU_MOV_VR:

            reg_len = ( return_command(3) / 10) % 10;
            reg_number =  return_command(3) % 10;
            memory_adress =  memory +  return_command(1) +  get_reg_data( return_command(2));

            switch (reg_len){

            case byte_len:
                *((char*)(memory_adress)) =  byte_segment[reg_number];
                break;

            case word_len:
                *((short int*)(memory_adress)) =  word_segment[reg_number];
                break;

            case double_word_len:
                *((int*)(memory_adress)) =  double_word_segment[reg_number];
                break;

            case private_len:
                *((double*)(memory_adress)) =  segment_private[reg_number];
                break;
            }

             increase_pointer(4);
            break;

        case CPU_PUSH:

            reg_len = ( return_command(1) / 10) % 10;
            reg_number =  return_command(1) % 10;

            switch (reg_len){

            case byte_len:
                fir_num = (double) byte_segment[reg_number];
                break;

            case word_len:
                fir_num = (double) word_segment[reg_number];
                break;

            case double_word_len:
                fir_num = (double) double_word_segment[reg_number];
                break;

            case private_len:
                fir_num = (double) segment_private[reg_number];
                break;
            }

             push_stack(fir_num);
             increase_pointer(2);
            break;

        case CPU_IN:

            scanf("%lf", &fir_num);
            reg_len = ( return_command(1) / 10) % 10;
            reg_number =  return_command(1) % 10;

            switch (reg_len){

            case byte_len:
                 byte_segment[reg_number] = (char) fir_num;
                break;

            case word_len:
                 word_segment[reg_number] = (short int) fir_num;
                break;

            case double_word_len:
                 double_word_segment[reg_number] = (int) fir_num;
                break;

            case private_len:
                 segment_private[reg_number] = (double) fir_num;
                break;
            }

             increase_pointer(2);
            break;

        case CPU_GET:

            symbol = getchar();
            reg_len = ( return_command(1) / 10) % 10;
            reg_number =  return_command(1) % 10;

            switch (reg_len){

            case byte_len:
                 byte_segment[reg_number] = (char) symbol;
                break;

            case word_len:
                 word_segment[reg_number] = (short int) symbol;
                break;

            case double_word_len:
                 double_word_segment[reg_number] = (int) symbol;
                break;

            case private_len:
                 segment_private[reg_number] = (double) symbol;
                break;
            }

             increase_pointer(2);
            break;

        case NOP:

             increase_pointer(1);
            break;

        case CPU_ADD:

            sec_num =  pop_stack();
            fir_num =  pop_stack();
             push_stack(fir_num + sec_num);
             increase_pointer(1);
            break;

        case CPU_SUB:

            sec_num =  pop_stack();
            fir_num =  pop_stack();
             push_stack(fir_num - sec_num);
             increase_pointer(1);
            break;

        case CPU_DIV:

            sec_num =  pop_stack();
            fir_num =  pop_stack();
             push_stack(fir_num / sec_num);
             increase_pointer(1);
            break;

        case CPU_MUL:

            sec_num =  pop_stack();
            fir_num =  pop_stack();
             push_stack(fir_num * sec_num);
             increase_pointer(1);
            break;

        case CPU_FSQRT:

            fir_num =  pop_stack();
             push_stack(sqrt(fir_num));
             increase_pointer(1);
            break;

        case CPU_JL:

            if ( segment_private[0] < 0){

                 command_pointer =  return_command(1);
            } else{

                 increase_pointer(2);
            }
            break;

        case CPU_JG:

            if ( segment_private[0] > 0){

                 command_pointer =  return_command(1);
            } else{

                 increase_pointer(2);
            }
            break;

        case CPU_JE:

            if ( segment_private[0] == 0){

                 command_pointer =  return_command(1);
            } else{

                 increase_pointer(2);
            }
            break;

        case CPU_JN:

             command_pointer =  return_command(1);
            break;

        case CPU_FUNC_JMP:

             command_pointer =  return_command(1);
            break;

        case CPU_CMP:

            sec_num =  pop_stack();
            fir_num =  pop_stack();

             segment_private[0] = sec_num - fir_num;
             increase_pointer(1);
            break;

        case CPU_POP:

            fir_num =  pop_stack();
            reg_len = ( return_command(1) / 10) % 10;
            reg_number =  return_command(1) % 10;

            switch (reg_len){

            case byte_len:
                 byte_segment[reg_number] = (char)fir_num;
                break;

            case word_len:
                 word_segment[reg_number] = (short int)fir_num;
                break;

            case double_word_len:
                 double_word_segment[reg_number] = (int)fir_num;
                break;

            case private_len:
                 segment_private[reg_number] = fir_num;
                break;
            }

             increase_pointer(2);
            break;

        case CPU_OUT:

            printf("out: %lf\n",  pop_stack());
             increase_pointer(1);
            break;

        case CPU_OUT_CHR:

            printf("%c", (char) pop_stack());
             increase_pointer(1);
            break;

        case CPU_HLT:

            exit(0);
            break;

        case END:

             command_pointer = num_of_comands;
            break;
        }

    //--------

    }
}

CPU_class::~CPU_class(){

        printf("destructor was called\n");
        /*stack_destruct(stack);
        free(machine_code);
        free(memory);
        free(byte_segment);
        free(word_segment);
        free(double_word_segment);
        free(segment_private);*/
    }