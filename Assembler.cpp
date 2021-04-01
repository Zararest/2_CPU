#include "headers/commands.h"
#include "headers/table_class.h"
#include "headers/array_class.h"
#include "headers/log.h"

CREATE_LOG("asm_log.txt");

#define COMMAND_WITH_NO_PARAM(command_number) machine_code.add_command(0, command_number);\
                                              machine_code.increase_pointer(1);\
                                              not_a_command = 0;\

#define COMMAND_JUMP(command_number) machine_code.add_command(0, command_number);\
                                     machine_code.increase_pointer(1);\
                                     word = strtok(NULL, delim);\
                                     MY_ASSERT(word != NULL, COMMAND_IS_NULL);\
                                     table_of_jmps.add_new_obj(word, machine_code.element_access(0));\
                                     machine_code.increase_pointer(1);\
                                     not_a_command = 0;

#define COMMAND_WITH_REG_PARAM(command_number) machine_code.add_command(0, command_number);\
                                               machine_code.increase_pointer(1);\
                                               word = strtok(NULL, delim);\
                                               MY_ASSERT(word != NULL, COMMAND_IS_NULL);\
                                               MY_ASSERT(find_register(word) != -1, WRONG_REG_NAME);\
                                               machine_code.add_command(0, find_register(word));\
                                               machine_code.increase_pointer(1);\
                                               not_a_command = 0;

int length(char* line){

    int i = 0;
    while (line[i] != '\0'){

        i++;
    }
    return i;
}

int find_register(char* word) {

    if ( (length(word) == 3) && (word[1] == '_') ) {

        if ( (word[0] == 'B') && (word[2] >= 'A') && (word[2] <= 'C') ) {
            
            if ((word[2] - 'A') <= NUMBER_B_REGISTERS){
                return PUBL_B_A + (word[2] - 'A');
            } else{
                return -1;
            }
        }

        if ( (word[0] == 'W') && (word[2] >= 'A') && (word[2] <= 'D') ) {

            if ((word[2] - 'A') <= NUMBER_W_REGISTERS){
                return PUBL_W_A + (word[2] - 'A');
            } else{
                return -1;
            }
        }
    
        if ( (word[0] == 'D') && (word[2] >= 'A') && (word[2] <= 'E') ) {

            if ((word[2] - 'A') <= NUMBER_W_REGISTERS){
                return PUBL_DW_A + (word[2] - 'A');
            } else{
                return -1;
            }
        }

        if (word[0] == 'P') {

            if (word[2] == 'F') {

                return PRIV_F;
            }

            if (word[2] == 'R') {

                return PRIV_R;
            }
        }

    } else {

        return -1;
    }
    return -1;
}

char* fill_buffer(char name_of_input_file[MAXLEN], int* word_counter) {

    int i = 0;
    struct stat statistika;
    stat(name_of_input_file, &statistika);

    char* buffer = (char*) calloc(statistika.st_size + 1, sizeof(char));
    MY_ASSERT(buffer != NULL, MEMORY_IS_NULL);

    FILE* p_input = fopen(name_of_input_file, "r");
    MY_ASSERT(p_input != NULL, FILE_IS_NULL);

    char symbol = fgetc(p_input);

    while (symbol != EOF) {

        if ((symbol != '\n') && (symbol != '\t') && (symbol != '\r')) {

            if (symbol == ' ') {
                (*word_counter)++;
            }

            buffer[i] = symbol;
            i++;
        }
        else {

            buffer[i] = ' ';
            i++;
            (*word_counter)++;
        }

        symbol = fgetc(p_input);
    }
    (*word_counter)++;

    return buffer;
}

void name_of_link(char* tmp){

    int i = 0, len = length(tmp);

    MY_ASSERT(tmp[len - 1] == ':', WRONG_LINK);
    tmp[len - 1] = '\0';
}

char* name_of_modif(char* word){

    int i = 0;

    while ( (word[i] != ']') && (i < 7) ){

        i++;
    }

    MY_ASSERT(i != 7, WRONG_MODIFICATOR);
    word[i] = '\0';
    return word;
}




double* assembler(char name_of_input_file[MAXLEN], int* num_of_comands) {

    setlocale( LC_ALL, "Russian");

    int not_a_command = 0, word_has_been_already_been_read = 0, data_pointer = 0, var_was_def = 0;
    double* prev_func_jmp = 0;
    char* buffer = fill_buffer(name_of_input_file, num_of_comands);
    MY_ASSERT(buffer != NULL, FILL_BUFFER_TROUBLE);
    char delim[4] = " ";
    char* word = strtok(buffer, delim);
    char* name_of_var = NULL;

    array_of_commands machine_code((*num_of_comands) + 2);

    table_of_matches table_of_jmps;
    table_of_matches table_of_vars;
    table_of_matches table_of_func;

    while (NULL != word) {

        not_a_command = 1;
        
        if (strcmp(word, "function") == 0){

            word = strtok(NULL, delim);
            MY_ASSERT(word != NULL, COMMAND_IS_NULL);
            table_of_func.add_defin_of_obj(word, (double)machine_code.pointer);

            machine_code.add_command(0, CPU_FUNC_JMP);
            prev_func_jmp = machine_code.element_access(1);
            machine_code.increase_pointer(2);

            not_a_command = 0;
            ADD_TO_LOG("function", machine_code.pointer);
        }

        if (strcmp(word, "RET") == 0){

            machine_code.add_command(0, CPU_RET);
            machine_code.increase_pointer(1);

            *(prev_func_jmp) = (double)machine_code.pointer;

            not_a_command = 0;
            ADD_TO_LOG("RET", machine_code.pointer);
        }

        if (strcmp(word, "CALL") == 0){

            machine_code.add_command(0, CPU_CALL);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            MY_ASSERT(word != NULL, COMMAND_IS_NULL);
            table_of_func.add_new_obj(word, machine_code.element_access(0));
            machine_code.increase_pointer(1);

            not_a_command = 0;
            ADD_TO_LOG("CALL", machine_code.pointer);
        }

        if (word[0] == '@'){

            name_of_link(word);

            assert(table_of_jmps.number_of_redefinition_of_obj(word) == 0);
            table_of_jmps.add_defin_of_obj(word + 1, (double)machine_code.pointer);

            not_a_command = 0;
            ADD_TO_LOG("linc_dif", machine_code.pointer);
        }

        if (strcmp(word, "MOV") == 0) {

            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);

            if (find_register(word) != -1){

                machine_code.add_command(0, find_register(word));
                machine_code.increase_pointer(1);

                word = strtok(NULL, delim);
                MY_ASSERT(word != NULL, COMMAND_IS_NULL);
                if ( ( (word[0] >= '0') && (word[0] <= '9') ) || ((word[1] >= '0') && (word[1] <= '9')) ) {

                    machine_code.add_command(0,  strtod(word, NULL));
                    machine_code.add_command(-2, CPU_MOV_RD);
                    machine_code.increase_pointer(1);
                } else {

                    table_of_vars.add_new_obj(word, machine_code.element_access(0));
                    machine_code.add_command(-2, CPU_MOV_RV);
                    machine_code.increase_pointer(1);

                    if (word[length(word) + 1] == '['){

                        word = strtok(NULL, delim);
                        MY_ASSERT(word != NULL, COMMAND_IS_NULL);
                        word = name_of_modif(word + 1);
                        MY_ASSERT(find_register(word) != -1, WRONG_REG_NAME);

                        machine_code.add_command(0, find_register(word));
                        machine_code.increase_pointer(1);
                    } else{

                        machine_code.add_command(0, 0);
                        machine_code.increase_pointer(1);
                    }

                }
            } else {

                machine_code.add_command(-1, CPU_MOV_VR);
                table_of_vars.add_new_obj(word, machine_code.element_access(0));
                machine_code.increase_pointer(1);

                if (word[length(word) + 1] == '['){

                    word = strtok(NULL, delim);
                    MY_ASSERT(word != NULL, COMMAND_IS_NULL);
                    word = name_of_modif(word + 1);
                    MY_ASSERT(find_register(word) != -1, WRONG_MODIFICATOR);

                    machine_code.add_command(0, find_register(word));
                    machine_code.increase_pointer(1);
                } else{

                    machine_code.add_command(0, 0);
                    machine_code.increase_pointer(1);
                }

                word = strtok(NULL, delim);
                MY_ASSERT(find_register(word) != -1, WRONG_MODIFICATOR);

                machine_code.add_command(0, find_register(word));
                machine_code.increase_pointer(1);

            }

            not_a_command = 0;
            ADD_TO_LOG("MOV", machine_code.pointer);
        }

        if (strcmp(word, "PUSH") == 0){

            COMMAND_WITH_REG_PARAM(CPU_PUSH);
            ADD_TO_LOG("PUSH", machine_code.pointer);
        }

        if (strcmp(word, "POP") == 0){

            COMMAND_WITH_REG_PARAM(CPU_POP);
            ADD_TO_LOG("POP", machine_code.pointer);
        }

        if (strcmp(word, "IN") == 0){

            COMMAND_WITH_REG_PARAM(CPU_IN);
            ADD_TO_LOG("IN", machine_code.pointer);
        }

        if (strcmp(word, "GET") == 0){

            COMMAND_WITH_REG_PARAM(CPU_GET);
            ADD_TO_LOG("GET", machine_code.pointer);
        }

        if (strcmp(word, "ADD") == 0){

            COMMAND_WITH_NO_PARAM(CPU_ADD);
            ADD_TO_LOG("ADD", machine_code.pointer);
        }

        if (strcmp(word, "SUB") == 0){

            COMMAND_WITH_NO_PARAM(CPU_SUB);
            ADD_TO_LOG("SUB", machine_code.pointer);
        }

        if (strcmp(word, "DIV") == 0){

            COMMAND_WITH_NO_PARAM(CPU_DIV);
            ADD_TO_LOG("DIV", machine_code.pointer);
        }

        if (strcmp(word, "MUL") == 0){

            COMMAND_WITH_NO_PARAM(CPU_MUL);
            ADD_TO_LOG("MUL", machine_code.pointer);
        }

        if (strcmp(word, "CMP") == 0){

            COMMAND_WITH_NO_PARAM(CPU_CMP);
            ADD_TO_LOG("CMP", machine_code.pointer);
        }

        if (strcmp(word, "OUT") == 0){

            COMMAND_WITH_NO_PARAM(CPU_OUT);
            ADD_TO_LOG("OUT", machine_code.pointer);
        }

        if (strcmp(word, "OUT_CHR") == 0){

            COMMAND_WITH_NO_PARAM(CPU_OUT_CHR);
            ADD_TO_LOG("OUT_CHAR", machine_code.pointer);
        }

        if (strcmp(word, "HLT") == 0){

            COMMAND_WITH_NO_PARAM(CPU_HLT);
            ADD_TO_LOG("HLT", machine_code.pointer);
        }

        if (strcmp(word, "NOP") == 0){

            COMMAND_WITH_NO_PARAM(NOP);
            ADD_TO_LOG("NOP", machine_code.pointer);
        }

        if (strcmp(word, "END") == 0){

            COMMAND_WITH_NO_PARAM(END);
            ADD_TO_LOG("END", machine_code.pointer);
        }

        if (strcmp(word, "FSQRT") == 0){

            COMMAND_WITH_NO_PARAM(CPU_FSQRT);
            ADD_TO_LOG("FSQRT", machine_code.pointer);
        }

        if (strcmp(word, "JL") == 0){

            COMMAND_JUMP(CPU_JL);
            ADD_TO_LOG("JL", machine_code.pointer);
        }

        if (strcmp(word, "JG") == 0){

            COMMAND_JUMP(CPU_JG);
            ADD_TO_LOG("JG", machine_code.pointer);
        }

        if (strcmp(word, "JE") == 0){

            COMMAND_JUMP(CPU_JE);
            ADD_TO_LOG("JE", machine_code.pointer);
        }

        if (strcmp(word, "JN") == 0){

            COMMAND_JUMP(CPU_JN);
            ADD_TO_LOG("JN", machine_code.pointer);
        }

        if (not_a_command == 1){

            name_of_var = word;

            word = strtok(NULL, delim);
            MY_ASSERT(word != NULL, COMMAND_IS_NULL);
            var_was_def = 0;

            if (strcmp(word, "DB") == 0){ 

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);
                data_pointer += 1;
            }

            if (strcmp(word, "DW") == 0){

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);
                data_pointer += 2;
            }

            if (strcmp(word, "DD") == 0){

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);
                data_pointer += 4;
            }

            if (strcmp(word, "DMAS") == 0) {

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);

                word = strtok(NULL, delim);
                MY_ASSERT(word != NULL, COMMAND_IS_NULL);
                MY_ASSERT(strtod(word, NULL) != 0, WRONG_DEF_OF_MAS);
                data_pointer += strtod(word, NULL);
            }

            MY_ASSERT(var_was_def != 0, WRONG_COMMAND);
            ADD_TO_LOG("var dif", machine_code.pointer);
        }

            word = strtok(NULL, delim);
    }

    table_of_jmps.match_arrays();
    table_of_vars.match_arrays();
    table_of_func.match_arrays();

    free(buffer);
    return machine_code.return_array_of_commands();
}


int main() {
    
    char name_of_input_file[MAXLEN] = "input.txt";
    int num_of_comands = 0;
    double* machine_code = assembler(name_of_input_file, &num_of_comands);

    FILE* output_file = fopen("machine_commands.bin", "wb");
    MY_ASSERT(output_file != NULL, FILE_IS_NULL);

    fwrite(&num_of_comands, sizeof(int), 1, output_file);
    MY_ASSERT(fwrite(machine_code, sizeof(double), num_of_comands, output_file) == num_of_comands, BINARY_FILE_TROUBLE);

    free(machine_code);
    fclose(output_file);

    CLOSE_LOG;
    return 0;
}
