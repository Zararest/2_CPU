#include "headers/commands.h"
#include "headers/table_class.h"
#include "headers/array_class.h"

int length(char* line){

    int i = 0;
    printf("in len i = %i\n", i);
    while (line[i] != '\0'){

        i++;
    }

    return i;
}

int find_register(char* word) {

    printf("dafuq\n");
    printf("len = %i\n", length(word));
    if ( (length(word) == 3) && (word[1] == '_') ) {

        if ( (word[0] == 'B') && (word[2] >= 'A') && (word[2] <= 'C') ) {

            return PUBL_B_A + (word[2] - 'A');
        }

        if ( (word[0] == 'W') && (word[2] >= 'A') && (word[2] <= 'D') ) {

            return PUBL_W_A + (word[2] - 'A');
        }

        if ( (word[0] == 'D') && (word[2] >= 'A') && (word[2] <= 'E') ) {

            return PUBL_DW_A + (word[2] - 'A');

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
    if (buffer == NULL) {

        printf("troubles with memory\n");
        return NULL;
    }

    FILE* p_input = fopen(name_of_input_file, "r");
    if (p_input == NULL) {
        return NULL;
    }

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

    if (tmp[len - 1] == ':'){

        tmp[len - 1] = '\0';
    } else{

        printf("this [%s] isn't a link\n", tmp);
        exit(2);
    }

}

char* name_of_modif(char* word){

    int i = 0;

    while ( (word[i] != ']') && (i < 7) ){

        i++;
    }

    if (i == 7){

        printf("incorrect modif\n");
        exit(10);
    } else{

        word[i] = '\0';
        return word;
    }
}




double* assembler(char name_of_input_file[MAXLEN], int* num_of_comands) {

    setlocale( LC_ALL, "Russian");

    int not_a_command = 0, word_has_been_already_been_read = 0, data_pointer = 0, var_was_def = 0;
    double* prev_func_jmp = 0;
    char* buffer = fill_buffer(name_of_input_file, num_of_comands);
    assert(buffer != NULL);
    char delim[4] = " ";
    char* word = strtok(buffer, delim);
    char* name_of_var = NULL;

    array_of_commands machine_code((*num_of_comands) + 2);

    table_of_matches table_of_jmps;
    table_of_matches table_of_vars;
    table_of_matches table_of_func;

    while (NULL != word) {

        not_a_command = 1;
        printf("command pointer = %i\n", machine_code.pointer);
        if (strcmp(word, "function") == 0){

            word = strtok(NULL, delim);

            table_of_func.add_defin_of_obj(word, (double)machine_code.pointer);

            machine_code.add_command(0, CPU_FUNC_JMP);
            prev_func_jmp = machine_code.element_access(1);
            machine_code.increase_pointer(2);

            not_a_command = 0;
        }

        if (strcmp(word, "RET") == 0){

            machine_code.add_command(0, CPU_RET);
            machine_code.increase_pointer(1);

            *(prev_func_jmp) = (double)machine_code.pointer;

            not_a_command = 0;
        }

        if (strcmp(word, "CALL") == 0){

            machine_code.add_command(0, CPU_CALL);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            table_of_func.add_new_obj(word, machine_code.element_access(0));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (word[0] == '@'){

            name_of_link(word);

            assert(table_of_jmps.number_of_redefinition_of_obj(word) == 0);
            table_of_jmps.add_defin_of_obj(word + 1, (double)machine_code.pointer);

            not_a_command = 0;
        }

        if (strcmp(word, "MOV") == 0) {

            not_a_command = 0;
            printf("still here\n");
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);

            if (find_register(word) != -1){

                machine_code.add_command(0, find_register(word));
                machine_code.increase_pointer(1);

                word = strtok(NULL, delim);
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
                        word = name_of_modif(word + 1);
                        assert(find_register(word) != -1);

                        machine_code.add_command(0, find_register(word));// !!!!!!!!!!!!!!! ������������ ������ ����� ��������
                        machine_code.increase_pointer(1);// !!!!!!!!!!!!!!
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
                    word = name_of_modif(word + 1);
                    assert(find_register(word) != -1);

                    machine_code.add_command(0, find_register(word));// !!!!!!!!!!!!!!! ������������ ������ ����� ��������
                    machine_code.increase_pointer(1);// !!!!!!!!!!!!!!
                } else{

                    machine_code.add_command(0, 0);
                    machine_code.increase_pointer(1);
                }

                word = strtok(NULL, delim);
                //printf("not here and find register = %i\n", find_register(word));
                assert(find_register(word) != -1);

                machine_code.add_command(0, find_register(word));
                machine_code.increase_pointer(1);

            }

        }

        if (strcmp(word, "PUSH") == 0){

            machine_code.add_command(0, CPU_PUSH);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            assert(find_register(word) != -1);
            machine_code.add_command(0, find_register(word));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "POP") == 0){

            machine_code.add_command(0, CPU_POP);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            assert(find_register(word) != -1);
            machine_code.add_command(0, find_register(word));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "IN") == 0){

            machine_code.add_command(0, CPU_IN);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            assert(find_register(word) != -1);
            machine_code.add_command(0, find_register(word));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "GET") == 0){

            machine_code.add_command(0, CPU_GET);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            assert(find_register(word) != -1);
            machine_code.add_command(0, find_register(word));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "ADD") == 0){

            machine_code.add_command(0, CPU_ADD);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "SUB") == 0){

            machine_code.add_command(0, CPU_SUB);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "DIV") == 0){

            machine_code.add_command(0, CPU_DIV);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "MUL") == 0){

            machine_code.add_command(0, CPU_MUL);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "CMP") == 0){

            machine_code.add_command(0, CPU_CMP);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "OUT") == 0){

            machine_code.add_command(0, CPU_OUT);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "OUT_CHR") == 0){

            machine_code.add_command(0, CPU_OUT_CHR);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "HLT") == 0){

            machine_code.add_command(0, CPU_HLT);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "NOP") == 0){

            machine_code.add_command(0, NOP);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "END") == 0){

            machine_code.add_command(0, END);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "FSQRT") == 0){

            machine_code.add_command(0, CPU_FSQRT);
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "JL") == 0){

            machine_code.add_command(0, CPU_JL);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            table_of_jmps.add_new_obj(word, machine_code.element_access(0));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "JG") == 0){

            machine_code.add_command(0, CPU_JG);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            table_of_jmps.add_new_obj(word, machine_code.element_access(0));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "JE") == 0){

            machine_code.add_command(0, CPU_JE);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            table_of_jmps.add_new_obj(word, machine_code.element_access(0));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (strcmp(word, "JN") == 0){

            machine_code.add_command(0, CPU_JN);
            machine_code.increase_pointer(1);

            word = strtok(NULL, delim);
            table_of_jmps.add_new_obj(word, machine_code.element_access(0));
            machine_code.increase_pointer(1);

            not_a_command = 0;
        }

        if (not_a_command == 1){

            printf("here word = %s\n", word);
            name_of_var = word;

            word = strtok(NULL, delim);
            var_was_def = 0;

            if (strcmp(word, "DB") == 0){ //byte

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);
                data_pointer += 1;
            }

            if (strcmp(word, "DW") == 0){ //word 2 bytes

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);
                data_pointer += 2;
            }

            if (strcmp(word, "DD") == 0){ //double word 4 bytes

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);
                data_pointer += 4;
            }

            if (strcmp(word, "DMAS") == 0) {//������ �������� ������� ������ 0

                var_was_def = 1;

                table_of_vars.add_defin_of_obj(name_of_var, data_pointer);

                word = strtok(NULL, delim);
                assert(strtod(word, NULL) != 0);
                data_pointer += strtod(word, NULL);
            }

            if (var_was_def == 0){

                printf("strange command [%s]??\n", word);
                exit(3);
            }
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
    assert(output_file != NULL);

    fwrite(&num_of_comands, sizeof(int), 1, output_file);
    fwrite(machine_code, sizeof(double), num_of_comands, output_file);

    free(machine_code);
    fclose(output_file);

    printf("returned 0\n");
    return 0;
}
